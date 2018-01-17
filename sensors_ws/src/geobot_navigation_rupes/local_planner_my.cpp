#include "ros/ros.h"
#include "geobot_navigation_rupes/Path.h"
#include <cstdlib>
#include <iostream>
#include <geobot_navigation_rupes/local_planner.h>
#include <geometry_msgs/Twist.h>
#include <tf/tf.h>
#include <tf/LinearMath/Quaternion.h>
#include <std_msgs/String.h>

using namespace std;
double path1;
double path2;
double robot_x;
double robot_y;
double prev_pose_x = 0;
double prev_pose_y = 0;
int flag = 0;
int flag_frequency = 0;

namespace geobot_local_planner_rupes{

LocalPlannerUtil::LocalPlannerUtil()
{


//************************************************************************************* 
// 					PUBLISHERS
//*************************************************************************************//
	velocity_cmdPublisher_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 20); // publish the velocity commands
  	local_pathPublisher_ = nh.advertise<nav_msgs::Path>("local_path", 20); // publish the local_path
  	alternate_pathPublisher_ = nh.advertise<nav_msgs::Path>("alternate_path", 20); // publish the alternate_path
  	gapDirectionPublisher_ = nh.advertise<geobot_navigation::GapDirection>("gap_direction", 20); // publish the alternate_path
  	dummyPublisher = nh.advertise<std_msgs::String>("dummy", 20); // dummy publisher
//*******************************************************************************


//*************************************************************************************
// 					SUBSCRIBERS
//*************************************************************************************//
  	obstacle_proximitySubscriber_ = nh.subscribe("obstacle_proximity",10, &LocalPlannerUtil::acquire_obstacle_proximity, this); // subscribe for the present pose
  	joystickoverideSubscriber_ = nh.subscribe("/joy_teleop/joy",10, &LocalPlannerUtil::joystickoveride,this);
    gap_arraySubscriber_ = nh.subscribe("candidate_gaps",10, &LocalPlannerUtil::acquire_candidate_gaps,this);

//*************************************************************************************


//*************************************************************************************
// 					PARAMETERS
//*************************************************************************************//
	turnaround_threshold = 0.1;
	path_error_deadband = 0.2;
	angular_velocity_turnaround = 0.4;
	maximum_linear_velocity = 1.0;
	maximum_angular_velocity = 1.0;	
	approaching_distance = 1.0;
	side_distance_avoidance_threshold = 0.8; // was 0.8
	side_avoidance_blindband = 0.4; // was 0.4
	obstacle_clearance = 0.7;
	cross_track_error_deadband = 0.01;
	derivative_gain = 0.02; // was 0.01
	proportional_gain = 0.0;
	proportional_heading_gain = 0.0;
	integral_gain = 0.0;
	integral_heading_gain = 0.0;
	steering_gain = 1.0;
	min_delta_time = 0.1;
	error_gain = 1.0;
	cte_gain = 0.2;	
	heading_gain = 0.3; // was 0.7 
	derivative_heading_gain = 0.2; // was 0.1
	trajectory_projection = 1.0;

//************************************************************************************//
	override_by_joystick = false;
	gap_dist_right = 0.0;
	gap_dist_left = 0.0;
	gap_angle_right = 0.0;
	gap_angle_left = 0.0;
	// path2select = ORIGINAL_PATH;
	// onwhich_sideofrobot_is_originalpath = LEFT_SIDE_OF_ROBOT;
	// gap_position2obstacle = GAP_LEFT_SIDE_OF_OBSTACLE;
		
	ROS_INFO("Distance = %f \n",path1);
    	ROS_INFO("Heading in degrees = %f \n",path2);
	run(path1,path2);
	
}




//*************************************************************************************
//					HIGH LEVEL CONTROLLER 
//*************************************************************************************//
bool LocalPlannerUtil::run(double a, double b)
{

	bool goal_reached = false;
	bool returned = false;

	geometry_msgs::PoseStamped start;
	geometry_msgs::PoseStamped finish;

	if(!acquire_robotpose()) // update the robot pose
	{
		ROS_ERROR("An error has occurred in acquiring robot pose");
		return goal_reached;
	}

    	tf::Quaternion start_quat = tf::createQuaternionFromYaw(0);
    	start.pose.position.x = pose.x;  
   	start.pose.position.y = pose.y; 
     
    	start.pose.orientation.x = start_quat.x();
    	start.pose.orientation.y = start_quat.y();
    	start.pose.orientation.z = start_quat.z();
    	start.pose.orientation.w = start_quat.w();

	//call path tracking controller
	goal_reached = path_tracking_controller(a,0);
	local_path.clear();	

	if(goal_reached)
	{
		ROS_INFO("Goal is reached");
		ROS_INFO("Starting return sequence");

	}
	else
	{
		ROS_INFO("Goal unreachable");
		ROS_INFO("Starting return sequence");
	}


	if(!acquire_robotpose()) // update the robot pose
	{
		ROS_ERROR("An error has occurred in acquiring robot pose");
		return returned;
	}

	tf::Quaternion finish_quat = tf::createQuaternionFromYaw(0);
    	finish.pose.position.x = pose.x;  
    	finish.pose.position.y = pose.y; 
     
    	finish.pose.orientation.x = finish_quat.x();
    	finish.pose.orientation.y = finish_quat.y();
    	finish.pose.orientation.z = finish_quat.z();
    	finish.pose.orientation.w = finish_quat.w();

	//call path tracking controller
	returned = path_tracking_controller(a,1);
	local_path.clear();	

	if(returned)
	{
		ROS_INFO("Returned to starting position");

	}
	else
	{
		ROS_INFO("Cannot return to starting position");
	}

	return returned;
}

// Callback for jostick override over false obstacle.
void LocalPlannerUtil::joystickoveride(const sensor_msgs::Joy joy_msg)
{
    if(joy_msg.buttons[6] == 1) // so that debugging can be done if the other trigger is pressed
    {
        override_by_joystick = true;
    }
    else
    {
        override_by_joystick = false;
    }

}
//*************************************************************************************
//*************************************************************************************


//*************************************************************************************
// 					MID LEVEL CONTROLLER
//*************************************************************************************//
void LocalPlannerUtil::acquire_obstacle_proximity(const pointcloud_to_laserscan::ObstacleProximity msg)
{
	// Get the pose for the center of corridor point from lidar data.
	obstacle_proximity_msg = msg;
	left = msg.shortest_distance_to_obstacle_LS;
	right = msg.shortest_distance_to_obstacle_RS;
	front = msg.shortest_distance_to_obstacle_FT;
	if (left > 3)
	{
		left = 3;
	}
	if (right > 3)
	{
		right = 3;
	}
}


bool LocalPlannerUtil::acquire_robotpose()
{
	// Get the current pose of the geobot, w.r.t global and the robot frame.
	tf::StampedTransform odom_base_transform;
	tf::Matrix3x3 mat;
	double roll;
	double pitch;
	double yaw;
	
	try{
	listener.waitForTransform( "odom","base_link", ros::Time(0), ros::Duration(10.0));
	listener.lookupTransform("odom","base_link", ros::Time(0), odom_base_transform);	
	}
	
	catch(tf::TransformException &ex)
	{
		ROS_ERROR("%s",ex.what());
		return false;
	}

	mat.setRotation(odom_base_transform.getRotation());
	mat.getRPY(roll, pitch, yaw);

	pose.x = odom_base_transform.getOrigin().getX();
	pose.y = odom_base_transform.getOrigin().getY();

	robot_x = pose.x;  
	robot_y = pose.y;
	pose.heading = yaw;

	if(flag == 1 && turn_around == true)
	{
		pose.heading = pose.heading - 3.14159;
	}

	pose.x = (pose.x*cos(pose.heading) + pose.y*sin(pose.heading));
	pose.y = (-pose.x*sin(pose.heading) + pose.y*cos(pose.heading));

	return true;
}


double LocalPlannerUtil::path_curvature(double present_heading)
{
	// compute the path curvature and use it to control the linear and angular velocity.
	double lookahead_heading_deviation = 0.0;
	double init_angle = present_heading;
	double angle, diff_angle;	
	
	//angle = atan2(local_path[1] - (pose.y + (local_path[1] - pose.y)/2), local_path[0] - (pose.x + (local_path[0] - pose.x)/2) );
	angle = atan2(end_point.y - start_point.y, end_point.x - start_point.x);
	diff_angle = smallest_diff_angle(angle,  init_angle);
	init_angle = angle;
	lookahead_heading_deviation = lookahead_heading_deviation + abs(diff_angle);
	
	return lookahead_heading_deviation;

}


double LocalPlannerUtil::smallest_diff_angle(double theta2, double theta1)
{
	// create a quaternion for each angle
	// then multiply them with the other which is addition in quaternion
	// convert the result back to angle

	double result;
	tf::Quaternion quat2, quat1;

	quat1.setRPY(0.0, 0.0, theta1);
	quat2.setRPY(0.0, 0.0, theta2);

	return result=quat2.angleShortestPath(quat1);

}


bool LocalPlannerUtil::path_tracking_controller(double total_distance, int mode)
{
	// Path planner and controller function.
	
	geometry_msgs::Twist velocity_command;
	vector<geometry_msgs::PoseStamped> plan;
	nav_msgs::Path localplan2publish, alternateplan2publish;

	int sequence = 0;
	distance_travelled = 0;
	double LR, LL, L3, LR_heading, LL_heading, x1, x2, y1, y2, x_t, offset_direction, path_offset, x_center, y_center, new_traj_heading;
	double LR_x, LR_y, LL_x, LL_y;
	double approaching_velocity,segment_length;
	double previous_cross_track_error = 0.0;
	ros::Time previous_time = ros::Time::now();
	ros::Duration delta_time;
	ros::Duration velocity_delta_time;
	ros::Time velocity_previous_time = ros::Time::now();
	ros::Time velocity_publish_time = ros::Time::now();
	double min_velocity_publish_time = 1.0;
	double delta_cross_track_error = 0.0;
	double derivative_error_term = 0.0;
	double derivative_heading_error_term = 0.0;
	double previous_error_heading = 0.0;
	double delta_error_heading = 0.0;
	std_msgs::String loop_frequency;

	//**********************PID Definitions*************************//
	double proportional_error_term = 0.0;
	double integral_error = 0.0;
	double windup_limit = 1000.0;
	double integral_error_term = 0.0;
	double controller_error_term = 0.0;
	double proportional_heading_error = 0.0;
	double integral_heading = 0.0;
	double integral_heading_error = 0.0;
	double controller_heading_error_term = 0.0;
	//*************************************************************//

	front_plus_current = 0;  
	turn_around = false;
	bool obstacle_on_the_way = false; 
	double steering_angle;

	//**************************************************************//
	flag = mode;
	//ros::Duration(2).sleep();
	ros::Rate loop_rate(10);	

	while (distance_travelled < total_distance  && ros::ok())
	{

	        // Turnaround Sequence
		if (mode == 1 && turn_around == false)
		{
			acquire_robotpose();
			double goal_heading = pose.heading;

			while(((pose.heading + 3.14) < (goal_heading + 6.28 - turnaround_threshold)) && (pose.heading + 3.14< 6.1)) // was 6.0
			{

			velocity_command.linear.x = 0.0;
			velocity_command.linear.y = 0.0;
			velocity_command.linear.z = 0.0;
			velocity_command.angular.x = 0.0;
			velocity_command.angular.y = 0.0;
			velocity_command.angular.z = angular_velocity_turnaround;

			ros::Time time_now = ros::Time::now();
			geometry_msgs::PoseStamped local_plan;

			tf::Quaternion quat = tf::createQuaternionFromYaw(0);
			local_plan.header.seq = 0;
			local_plan.header.stamp = time_now;
			local_plan.header.frame_id = "odom"; 
			local_plan.pose.position.x = pose.x;  
			local_plan.pose.position.y = pose.y;  
			local_plan.pose.orientation.x = quat.x();
			local_plan.pose.orientation.y = quat.y();
			local_plan.pose.orientation.z = quat.z();
			local_plan.pose.orientation.w = quat.w();
	     
			plan.push_back(local_plan);

			localplan2publish.poses = plan;
			localplan2publish.header.seq = sequence++;
			localplan2publish.header.stamp = ros::Time::now();
			localplan2publish.header.frame_id = "odom";

			plan.clear();

			velocity_cmdPublisher_.publish(velocity_command);
			local_pathPublisher_.publish(localplan2publish);
			local_path.clear();
			acquire_robotpose();
			}	

			turn_around = true;
			ROS_INFO("Geobot has completed turn around");
		}
	
	velocity_delta_time = ros::Time::now() - velocity_previous_time;
			
    if(flag_frequency == 0 ||  velocity_delta_time > ros::Duration(min_velocity_publish_time))
    {
    	flag_frequency = 1;
    	loop_frequency.data = "frequency ";
    	dummyPublisher.publish(loop_frequency);
	acquire_robotpose();

	if (mode == 0)
	{
		if (pose.x >= 0)
		front_plus_current = pose.x + 1.0;
		else
		front_plus_current = pose.x - 1.0;

	}
	
	else if (mode == 1)
	{
		front_plus_current = pose.x + 1.0;
	}

	local_path.push_back(front_plus_current);


	if(left < right){
		local_path.push_back(pose.y - ((right-left)/2)); 
	}
	if(right < left){
		local_path.push_back(pose.y + ((left-right)/2)); 
	}


	obstacle_on_the_way = false;

	if (mode == 0)
	{
		if (pose.x >= 0)
		start_point.x = pose.x + (local_path[0] - pose.x)/2 ;
		else
		start_point.x = pose.x - (local_path[0] - pose.x)/2 ;
	}
	
	else if (mode == 1)
	{
		start_point.x = pose.x + (local_path[0] - pose.x)/2 ;
	}
	
	start_point.y = pose.y + (local_path[1] - pose.y)/2;


	end_point.x = local_path[0] ;
	end_point.y = local_path[1] ;


	onwhich_sideofrobot_is_originalpath = original_path2robot(pose.x, pose.y, start_point.x, start_point.y, end_point.x, end_point.y);

	choose_path();

		if(path2select == OFFSET_ORIGINAL_PATH)
		{
			// If there is obstacle, offset the original local path
			// gap_dist_right and other gap parameters are private variable
			obstacle_on_the_way = true;

			LR = gap_dist_right;
			LL = gap_dist_left;

			// transform into global coordinate 
			LR_x = LR*cos(gap_angle_right);
			LR_y = LR*sin(gap_angle_right);
			LL_x = LL*cos(gap_angle_left);
			LL_y = LL*sin(gap_angle_left);

			//x1 = pose.x + LR_x*cos(pose.heading) - LR_y*sin(pose.heading);
			//y1 = pose.y + LR_x*sin(pose.heading) + LR_y*cos(pose.heading);

			//x2 = pose.x + LL_x*cos(pose.heading) - LL_y*sin(pose.heading);
			//y2 = pose.y + LL_x*sin(pose.heading) + LL_y*cos(pose.heading);

			x1 = robot_x + LR_x*cos(pose.heading) - LR_y*sin(pose.heading);
			y1 = robot_y + LR_x*sin(pose.heading) + LR_y*cos(pose.heading);

			x1 = x1*cos(pose.heading) + y1*sin(pose.heading);
			y1 = -x1*sin(pose.heading) + y1*cos(pose.heading);

			x2 = robot_x + LL_x*cos(pose.heading) - LL_y*sin(pose.heading);
			y2 = robot_y + LL_x*sin(pose.heading) + LL_y*cos(pose.heading);

			x2 = x2*cos(pose.heading) + y2*sin(pose.heading);
			y2 = -x2*sin(pose.heading) + y2*cos(pose.heading);
				

			if(gap_position2obstacle == GAP_RIGHT_SIDE_OF_OBSTACLE)
			{
				x_t = compute_cross_track_error(x2, y2, start_point.x, start_point.y, end_point.x, end_point.y);
				offset_direction = atan2(end_point.y - start_point.y, end_point.x - start_point.x) - M_PI/2;
				path_offset = x_t + obstacle_clearance;
			}
			
			else
			{
				x_t = compute_cross_track_error(x1, y1, start_point.x, start_point.y, end_point.x, end_point.y);
				offset_direction = atan2(end_point.y - start_point.y, end_point.x - start_point.x) - M_PI/2;
				path_offset = x_t - obstacle_clearance;
			}

		start_point.x = start_point.x + path_offset*cos(offset_direction);
		start_point.y = start_point.y + path_offset*sin(offset_direction);
		end_point.x = end_point.x + path_offset*cos(offset_direction);
		end_point.y = end_point.y + path_offset*sin(offset_direction);

		}

		else if(path2select == NORMAL_PATH_TO_GAP)
		{
			// If there is obstacle, compute a normal path to gap
			// adjust bendahead
			// gap_dist_right and other gap parameters are private variable

			obstacle_on_the_way = true;

			LR = gap_dist_right;
			LL = gap_dist_left;

			LR_x = LR*cos(gap_angle_right);
			LR_y = LR*sin(gap_angle_right);
			LL_x = LL*cos(gap_angle_left);
			LL_y = LL*sin(gap_angle_left);

			//x1 = pose.x + LR_x*cos(pose.heading) - LR_y*sin(pose.heading);
			//y1 = pose.y + LR_x*sin(pose.heading) + LR_y*cos(pose.heading);
			//x2 = pose.x + LL_x*cos(pose.heading) - LL_y*sin(pose.heading);
			//y2 = pose.y + LL_x*sin(pose.heading) + LL_y*cos(pose.heading);

			x1 = robot_x + LR_x*cos(pose.heading) - LR_y*sin(pose.heading);
			y1 = robot_y + LR_x*sin(pose.heading) + LR_y*cos(pose.heading);
			x1 = x1*cos(pose.heading) + y1*sin(pose.heading);
			y1 = -x1*sin(pose.heading) + y1*sin(pose.heading);

			x2 = robot_x + LL_x*cos(pose.heading) - LL_y*sin(pose.heading);
			y2 = robot_y + LL_x*sin(pose.heading) + LL_y*cos(pose.heading);
			x2 = x2*cos(pose.heading) + y2*sin(pose.heading);
			y2 = -x2*sin(pose.heading) + y2*sin(pose.heading);

			L3 = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));	


			if(gap_position2obstacle == GAP_RIGHT_SIDE_OF_OBSTACLE)
			{
				x_center = x2 + (obstacle_clearance*(x1 - x2))/L3;
				y_center = y2 + (obstacle_clearance*(y1 - y2))/L3;

			}

			else
			{
				x_center = x1 + (obstacle_clearance*(x2 - x1))/L3;
				y_center = y1 + (obstacle_clearance*(y2 - y1))/L3;

			}

			new_traj_heading = atan2(y2 - y1, x2 - x1) - M_PI/2; 

			start_point.x = x_center;
			start_point.y = y_center;
			end_point.x = x_center + trajectory_projection*cos(new_traj_heading);
			end_point.y = y_center + trajectory_projection*sin(new_traj_heading);

		}

		if(path2select == NORMAL_PATH_TO_GAP)
		{
			double angle = atan2(end_point.y - start_point.y, end_point.x - start_point.x);
			double diff_angle = smallest_diff_angle(angle, 0); 
			bendahead = abs(diff_angle);
		}
		
		else
		{
			bendahead = path_curvature(0); 
		}

		linear_velocity_constraint = max((1 - pow((bendahead/(3.14*0.45)),1.5)),0.1); 
		//linear_velocity_constraint = max(velocity_constraint,minimum_velocity_constraint);
		linear_velocity = linear_velocity_constraint*maximum_linear_velocity; 
	
		if (linear_velocity > maximum_linear_velocity){
			linear_velocity = maximum_linear_velocity;
		}

		if (linear_velocity < -maximum_linear_velocity){
			linear_velocity = -maximum_linear_velocity;
		}

		if (distance_travelled > (total_distance - approaching_distance)){
		linear_velocity = 0.5;
		}


		direction = atan((end_point.y - start_point.y)/(end_point.x - start_point.x));
		//direction = atan2(end_point.y - pose.y, end_point.x - pose.x);

		error_heading = direction; //- pose.heading;

		if (error_heading > M_PI)
		{
			error_heading = error_heading - (M_PI*2);
		}

		if (error_heading < -M_PI)
		{
			error_heading = error_heading + (M_PI*2);
		}


		cross_track_error = compute_cross_track_error(pose.x, pose.y, start_point.x, start_point.y, end_point.x, end_point.y);


		if(abs(cross_track_error) <= cross_track_error_deadband)  // This is to avoid oscillation of the robot around the path
		{
			cross_track_error = 0.0;
		}

		// ROS_INFO("PoseX: %f,  PoseY: %f", pose.x, pose.y);
		// ROS_INFO("PoseHeading: %f", pose.heading);
		// ROS_INFO("LocalX: %f, LocalY: %f", local_path[0],local_path[1]);
		// ROS_INFO("Start_X: %f Start_Y: %f", start_point.x,start_point.y);
		// ROS_INFO("End_X: %f   End_Y: %f", end_point.x,end_point.y);

		delta_time = ros::Time::now() - previous_time;
			
        if(delta_time > ros::Duration(min_delta_time))
		{
			previous_time = ros::Time::now();

			delta_cross_track_error = cross_track_error - previous_cross_track_error;
			derivative_error_term = derivative_gain * delta_cross_track_error/delta_time.toSec();

			delta_error_heading = error_heading - previous_error_heading;
			derivative_heading_error_term = derivative_heading_gain * delta_error_heading/delta_time.toSec();
    			
    		// Overall controller
    		controller_error_term = derivative_error_term;
    		controller_heading_error_term = derivative_heading_error_term;

			// Updating previous errors
    		previous_cross_track_error = cross_track_error;
			previous_error_heading = error_heading;
		}
			
		// ROS_INFO("derivative component  %f", derivative_error_term);
		// ROS_INFO("delta time component  %f", delta_time.toSec());
		// ROS_INFO("error difference component  %f", delta_cross_track_error);
		// ROS_INFO("Error Heading: %f", error_heading);
		// ROS_INFO("CTE: %f", cross_track_error);
		// ROS_INFO("Controller Error: %f", controller_error_term);
		// ROS_INFO("Controller Error Heading: %f", controller_heading_error_term);

		steering_angle = heading_gain*error_heading + error_gain*atan2(cte_gain*cross_track_error,linear_velocity) + controller_error_term + controller_heading_error_term;
		angular_velocity = steering_gain * steering_angle;

		if (angular_velocity > maximum_angular_velocity)
		{
			angular_velocity = maximum_angular_velocity;
		}

		if (angular_velocity < -maximum_angular_velocity)
		{
			angular_velocity = -maximum_angular_velocity;
		}


	velocity_previous_time = ros::Time::now();
	
	}

		ROS_INFO("angular_velocity: %f", angular_velocity);
		velocity_command.linear.x = linear_velocity;
		velocity_command.linear.y = 0.0;
		velocity_command.linear.z = 0.0;
		velocity_command.angular.x = 0.0;
		velocity_command.angular.y = 0.0;
		velocity_command.angular.z = angular_velocity;

			
        velocity_cmdPublisher_.publish(velocity_command);

		ros::Time time_now = ros::Time::now();
		geometry_msgs::PoseStamped local_plan;
		tf::Quaternion quat = tf::createQuaternionFromYaw(0);

		local_plan.header.seq = 0;
		local_plan.header.stamp = time_now;
		local_plan.header.frame_id = "odom"; 
		local_plan.pose.position.x = local_path[0];  
		local_plan.pose.position.y = local_path[1]; 
		local_plan.pose.orientation.x = quat.x();
		local_plan.pose.orientation.y = quat.y();
		local_plan.pose.orientation.z = quat.z();
		local_plan.pose.orientation.w = quat.w();
	     
		plan.push_back(local_plan);

		localplan2publish.poses = plan;
		localplan2publish.header.seq = sequence++;
		localplan2publish.header.stamp = ros::Time::now();
		localplan2publish.header.frame_id = "odom";

		plan.clear();
		local_path.clear();

		local_pathPublisher_.publish(localplan2publish);

		//// Here's the alternate path ////
		geometry_msgs::PoseStamped alternate_plan;
		tf::Quaternion alternate_quat = tf::createQuaternionFromYaw(0);

		alternate_plan.header.seq = 0;
		alternate_plan.header.stamp = time_now;
		alternate_plan.header.frame_id = "odom";
          
		alternate_plan.pose.position.x = start_point.x;  
		alternate_plan.pose.position.y = start_point.y;  
	         	     
		alternate_plan.pose.orientation.x = alternate_quat.x();
		alternate_plan.pose.orientation.y = alternate_quat.y();
		alternate_plan.pose.orientation.z = alternate_quat.z();
		alternate_plan.pose.orientation.w = alternate_quat.w();
		plan.push_back(alternate_plan);

		alternate_plan.header.seq = 1;
		alternate_plan.header.stamp = time_now;
		alternate_plan.header.frame_id = "odom";
          
		alternate_plan.pose.position.x = end_point.x; 
		alternate_plan.pose.position.y = end_point.y; 
	         	     
		alternate_plan.pose.orientation.x = alternate_quat.x();
		alternate_plan.pose.orientation.y = alternate_quat.y();
		alternate_plan.pose.orientation.z = alternate_quat.z();
		alternate_plan.pose.orientation.w = alternate_quat.w();
		plan.push_back(alternate_plan);

  		alternateplan2publish.poses = plan;
		alternateplan2publish.header.seq = localplan2publish.header.seq;
		alternateplan2publish.header.stamp = ros::Time::now();
		alternateplan2publish.header.frame_id = "odom";
		alternate_pathPublisher_.publish(alternateplan2publish);
		plan.clear();

	distance_travelled += hypot(robot_x - prev_pose_x , robot_y - prev_pose_y);
	ROS_INFO("Distance travelled = %f \n", distance_travelled);
	
	prev_pose_x = robot_x;
	prev_pose_y = robot_y;

	loop_rate.sleep();

	}

	return true;


    }


int LocalPlannerUtil::original_path2robot(double x0, double y0, double x1, double y1, double x2, double y2)
{
	double Dx, Dy, numerator, denominator, xte;

	Dx = x2 - x1;
	Dy = y2 - y1;

	numerator = Dy*x0 - Dx*y0 - x1*y2 + x2*y1;
	denominator = sqrt(Dx*Dx + Dy*Dy);
	xte = numerator/denominator;

	if(xte >= 0.0)
	{return LEFT_SIDE_OF_ROBOT;}
	else
	{return RIGHT_SIDE_OF_ROBOT;}

}


double LocalPlannerUtil::compute_cross_track_error(double x0, double y0, double x1, double y1, double x2, double y2) 
{
	// compute the cross track error to local path
	double Dx, Dy, numerator, denominator, xte;

	Dx = x2 - x1;
	Dy = y2 - y1;

	numerator = Dy*x0 - Dx*y0 - x1*y2 + x2*y1;
	denominator = sqrt(Dx*Dx + Dy*Dy);
	xte = numerator/denominator;

	return xte;

}
//*************************************************************************************
//*************************************************************************************//


//*************************************************************************************
// 					LOWER LEVEL CONTROLLER
//*************************************************************************************//

// This is to find the best candidate gap and the path to take, with obstacle avoidance
void LocalPlannerUtil::choose_path()
{
	// subcribe to candidate gaps
	// subscribe to obstacle region
	// find best candidate gap
	// determine which path to take

	std::vector<double > best_candidate_gap, candidate_gap_smallest2LS, candidate_gap_smallest2RS;
	
	double closest_localpath_trajectory_heading = atan2(local_path[1] - pose.y, local_path[0] - pose.x);
	double SR_diff_smallest = M_PI*2; // initializing to a large angle
	double SL_diff_smallest = M_PI*2; // initializing to a large angle
	double SR_heading, SL_heading, SR_diff, SL_diff;
	int which_gap_seq = 0;
	int which_gap_seq_LS= 0;
	int which_gap_seq_RS = 0;
	double LR, LL, LR_x, LR_y, LL_x, LL_y, x1, x2, y1, y2;
	geobot_navigation::GapDirection gapDirection;

	if(!candidate_gap_msg.gaps.empty()) // That is, if there are gaps to drive through
	{
		for(int i = 0; i < candidate_gap_msg.gaps.size(); i++)
		{
			LR = candidate_gap_msg.gaps[i].dist_right;
			LL = candidate_gap_msg.gaps[i].dist_left;
			LR_x = LR*cos(candidate_gap_msg.gaps[i].angle_right);
			LR_y = LR*sin(candidate_gap_msg.gaps[i].angle_right);
			LL_x = LL*cos(candidate_gap_msg.gaps[i].angle_left);
			LL_y = LL*sin(candidate_gap_msg.gaps[i].angle_left);

			//x1 = pose.x + LR_x*cos(pose.heading) - LR_y*sin(pose.heading);
			//y1 = pose.y + LR_x*sin(pose.heading) + LR_y*cos(pose.heading);
			x1 = robot_x + LR_x*cos(pose.heading) - LR_y*sin(pose.heading);
			y1 = robot_y + LR_x*sin(pose.heading) + LR_y*cos(pose.heading);
			x1 = x1*cos(pose.heading) + y1*sin(pose.heading);
			y1 = -x1*sin(pose.heading) + y1*cos(pose.heading);

			SR_heading = atan2(y1 - pose.y, x1 - pose.x);
			SR_diff = abs(smallest_diff_angle(closest_localpath_trajectory_heading, SR_heading));

			//x2 = pose.x + LL_x*cos(pose.heading) - LL_y*sin(pose.heading);
			//y2 = pose.y + LL_x*sin(pose.heading) + LL_y*cos(pose.heading);
			x2 = robot_x + LL_x*cos(pose.heading) - LL_y*sin(pose.heading);
			y2 = robot_y + LL_x*sin(pose.heading) + LL_y*cos(pose.heading);
			x2 = x2*cos(pose.heading) + y2*sin(pose.heading);
			y2 = -x2*sin(pose.heading) + y2*cos(pose.heading);

			SL_heading = atan2(y2 - pose.y, x2 - pose.x);
			SL_diff = abs(smallest_diff_angle(closest_localpath_trajectory_heading, SL_heading));

			gapDirection.gap_seq = candidate_gap_msg.gaps[i].header.seq;
			gapDirection.sr_heading  = SR_heading;
			gapDirection.sr_diff  = SR_diff;
			gapDirection.sl_heading = SL_heading;
			gapDirection.sl_diff = SL_diff;

			gapDirectionPublisher_.publish(gapDirection);

			// finding the closest gap ray to the tracked path
			if(SR_diff < SR_diff_smallest)
			{
				SR_diff_smallest = SR_diff;
				candidate_gap_smallest2RS.clear();
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].dist_right);
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].dist_left);
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].angle_right);
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].angle_left);
				which_gap_seq_RS = candidate_gap_msg.gaps[i].header.seq;

			}
			if(SL_diff < SL_diff_smallest)
			{
				SL_diff_smallest = SL_diff;
				candidate_gap_smallest2LS.clear();
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].dist_right);
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].dist_left);
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].angle_right);
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].angle_left);
				which_gap_seq_LS = candidate_gap_msg.gaps[i].header.seq;
			}

			// finding the side of the gap with respect to the obstacle
			if(SL_diff_smallest < SR_diff_smallest)
			{
				gap_dist_right = candidate_gap_smallest2LS[0];
				gap_dist_left = candidate_gap_smallest2LS[1];
				gap_angle_right = candidate_gap_smallest2LS[2];
				gap_angle_left = candidate_gap_smallest2LS[3];
				gap_position2obstacle = GAP_RIGHT_SIDE_OF_OBSTACLE; // left sided gap.
				which_gap_seq = which_gap_seq_LS;
			}
			if(SL_diff_smallest >= SR_diff_smallest)
			{
				gap_dist_right = candidate_gap_smallest2RS[0];
				gap_dist_left = candidate_gap_smallest2RS[1];
				gap_angle_right = candidate_gap_smallest2RS[2];
				gap_angle_left = candidate_gap_smallest2RS[3];
				gap_position2obstacle = GAP_LEFT_SIDE_OF_OBSTACLE; // right sided gap. That is, the robot is right sided
				which_gap_seq = which_gap_seq_RS;
			}
		}
	}
	else
	{
		
		gap_dist_right = 0.0;
		gap_dist_left = 0.0;
		gap_angle_right = 0.0;
		gap_angle_left = 0.0;
		gap_position2obstacle = NO_GAP; // Null
	}


	int obstacle_array[3] = {LEFT_SIDE_OPENED, FRONT_SIDE_OPENED,  RIGHT_SIDE_OPENED}; // L F R

		obstacle_array[0] = obstacle_proximity_msg.left_side_blocked;

		obstacle_array[1] = obstacle_proximity_msg.front_side_blocked;

		obstacle_array[2] = obstacle_proximity_msg.right_side_blocked;


	if(gap_position2obstacle != NO_GAP)
	{
		// selecting which path to take
		if((obstacle_array[0] == LEFT_SIDE_OPENED) &&  (obstacle_array[1] == FRONT_SIDE_OPENED) && (obstacle_array[2] == RIGHT_SIDE_OPENED))
		{
			// keep tracking previous path selected until there is an opening
			if((left > (side_distance_avoidance_threshold + side_avoidance_blindband)) && (right > (side_distance_avoidance_threshold + side_avoidance_blindband)))
			{
				path2select = ORIGINAL_PATH;
			}
		}
		else if((obstacle_array[0] == LEFT_SIDE_OPENED) && (obstacle_array[1] == FRONT_SIDE_BLOCKED) && (obstacle_array[2] == RIGHT_SIDE_OPENED))
		{
			path2select = OFFSET_ORIGINAL_PATH;
		}
		else if((obstacle_array[0] == LEFT_SIDE_BLOCKED) && (obstacle_array[1] == FRONT_SIDE_OPENED) && (obstacle_array[2] == RIGHT_SIDE_OPENED))
		{
			path2select = OFFSET_ORIGINAL_PATH;
			if(onwhich_sideofrobot_is_originalpath == RIGHT_SIDE_OF_ROBOT)
			{path2select = ORIGINAL_PATH;}
		}
		else if((obstacle_array[0] == LEFT_SIDE_OPENED) && (obstacle_array[1] == FRONT_SIDE_OPENED) && (obstacle_array[2] == RIGHT_SIDE_BLOCKED))
		{
			path2select = OFFSET_ORIGINAL_PATH;
			if(onwhich_sideofrobot_is_originalpath == LEFT_SIDE_OF_ROBOT)
			{path2select = ORIGINAL_PATH;}
		}
		else if((obstacle_array[0] == LEFT_SIDE_BLOCKED) && (obstacle_array[1] == FRONT_SIDE_BLOCKED) && (obstacle_array[2] == RIGHT_SIDE_BLOCKED))
		{
			path2select = NORMAL_PATH_TO_GAP;
		}
		else if((obstacle_array[0] == LEFT_SIDE_BLOCKED)&& (obstacle_array[1] == FRONT_SIDE_OPENED) && (obstacle_array[2] == RIGHT_SIDE_BLOCKED))
		{
			path2select = NORMAL_PATH_TO_GAP;
		}
		else if((obstacle_array[0] == LEFT_SIDE_OPENED)&& (obstacle_array[1] == FRONT_SIDE_BLOCKED) && (obstacle_array[2] == RIGHT_SIDE_BLOCKED))
		{
			path2select = NORMAL_PATH_TO_GAP;
			if(gap_position2obstacle == GAP_LEFT_SIDE_OF_OBSTACLE)
			{path2select = OFFSET_ORIGINAL_PATH;}
			else if ((left > (side_distance_avoidance_threshold + side_avoidance_blindband)) && (onwhich_sideofrobot_is_originalpath == LEFT_SIDE_OF_ROBOT))
			{path2select = ORIGINAL_PATH;}
		}
		else if((obstacle_array[0] == LEFT_SIDE_BLOCKED) && (obstacle_array[1] == FRONT_SIDE_BLOCKED) && (obstacle_array[2] == RIGHT_SIDE_OPENED))
		{
			path2select = NORMAL_PATH_TO_GAP;
			if(gap_position2obstacle == GAP_RIGHT_SIDE_OF_OBSTACLE)
			{ path2select = OFFSET_ORIGINAL_PATH;}
			else if ((right > (side_distance_avoidance_threshold + side_avoidance_blindband)) && (onwhich_sideofrobot_is_originalpath == RIGHT_SIDE_OF_ROBOT))
			{path2select = ORIGINAL_PATH;}
		}

	}

	if(override_by_joystick)
	{
		path2select = ORIGINAL_PATH;
		ROS_INFO("OVERRIDE"); 
	}

}


void LocalPlannerUtil::acquire_candidate_gaps(const gap_finding_pkg::GapArray msg)
{

	candidate_gap_msg = msg;
}


}
//*************************************************************************************
//*************************************************************************************//


int main(int argc, char **argv)
{
    ros::init(argc, argv, "geobot_local_planner_node");
    ros::NodeHandle n;

  if (argc != 3)
  {
    ROS_INFO("initializing geobot local planner");
    return 1;
  }

  ros::ServiceClient client = n.serviceClient<geobot_navigation_rupes::Path>("path");
  geobot_navigation_rupes::Path srv;
  srv.request.a = atof(argv[1]);
  srv.request.b = atof(argv[2]);

  if (client.call(srv))
  {
    ROS_INFO("Received path");
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }

  path1 = srv.response.path1;
  path2 = srv.response.path2;
  
  ros::AsyncSpinner spinner(4);
  spinner.start();

  geobot_local_planner_rupes::LocalPlannerUtil LPU;

  ros::waitForShutdown();

  // ros::MultiThreadedSpinner spinner(4);
  // spinner.spin();

}
