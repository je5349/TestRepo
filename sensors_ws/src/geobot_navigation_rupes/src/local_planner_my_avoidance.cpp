#include "ros/ros.h"
#include "geobot_navigation_rupes/Path.h"
#include <cstdlib>
#include <iostream>
#include <geobot_navigation_rupes/local_planner.h>
#include <geometry_msgs/Twist.h>
#include <tf/tf.h>
#include <tf/LinearMath/Quaternion.h>


using namespace std;
long int path1;
long int path2;
double prev_pose_x = 0;
double prev_pose_y = 0;

namespace geobot_local_planner_rupes{

LocalPlannerUtil::LocalPlannerUtil()
{


//*******************************************************************************
// 									PUBLISHERS
//*******************************************************************************
	velocity_cmdPublisher_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 20); // publish the velocity commands
  	local_pathPublisher_ = nh.advertise<nav_msgs::Path>("local_path", 20); // publish the local_path
  	//alternate_pathPublisher_ = nh.advertise<nav_msgs::Path>("alternate_path", 20); // publish the alternate_path
  	//gapDirectionPublisher_ = nh.advertise<geobot_navigation::GapDirection>("gap_direction", 20); // publish the alternate_path
//*******************************************************************************




//*******************************************************************************
// 									SUBSCRIBERS
//*******************************************************************************
  	obstacle_proximitySubscriber_ = nh.subscribe("obstacle_proximity",10, &LocalPlannerUtil::acquire_obstacle_proximity, this); // subscribe for the present pose
  	joystickoverideSubscriber_ = nh.subscribe("/joy_teleop/joy",10, &LocalPlannerUtil::joystickoveride,this);
  	override_by_joystick = false;
    //gap_arraySubscriber_ = nh.subscribe("candidate_gaps",10, &LocalPlannerUtil::acquire_candidate_gaps,this);

//*******************************************************************************




//********************************************************************************
// 									PARAMETERS
//********************************************************************************
	turnaround_threshold = 0.1;
	path_error_deadband = 0.2;
	angular_velocity_turnaround = 0.2;
	maximum_linear_velocity = 1.0;
	maximum_angular_velocity = 0.5;	
	approaching_distance = 1.0;
//********************************************************************************


	
	ROS_INFO("Distance = %ld \n",path1);
    ROS_INFO("Heading in degrees = %ld \n",path2);
	run(path1,path2);
	
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


double LocalPlannerUtil::path_curvature(double present_heading)
{
	// compute the path curvature and add to the heading error between the robot heading and the path
	double lookahead_heading_deviation = 0.0;
	double init_angle = present_heading;
	double angle, diff_angle;	
	
	angle = atan2(local_path[1] - pose.y, local_path[0] - pose.x);
	diff_angle = smallest_diff_angle(angle,  init_angle);
	init_angle = angle;
	lookahead_heading_deviation = lookahead_heading_deviation + abs(diff_angle);
	
	return lookahead_heading_deviation;

}


// Path planner and controller function.
bool LocalPlannerUtil::path_tracking_controller(long int total_distance, int mode)
{
	double bendahead, linear_velocity_constraint, angular_velocity_constraint, velocity_constraint;
	double linear_velocity;
	double angular_velocity;
	geometry_msgs::Twist velocity_command;
	vector<geometry_msgs::PoseStamped> plan;
	nav_msgs::Path localplan2publish;
	int sequence = 0;
	double distance_travelled = 0;
	x1 = 0;  
	bool turn_around = false; 

	ros::Duration(2).sleep();

	while (distance_travelled < total_distance)
	{

	//*********************************************************************
	//                     TURNAROUND SEQUENCE
	//*********************************************************************
	if (mode == 1 && turn_around == false){
		acquire_robotpose();
		double goal_heading = pose.heading;

		while(((pose.heading + 3.14) < (goal_heading + 6.28 - turnaround_threshold)) && (pose.heading + 3.14< 6.0))
		{
		ROS_INFO("Pose_heading = %f ", pose.heading+3.14);
		ROS_INFO("Goal_heading = %f ", goal_heading+6.28-turnaround_threshold);
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
		local_path.clear();


		velocity_cmdPublisher_.publish(velocity_command);
		local_pathPublisher_.publish(localplan2publish);

		acquire_robotpose();
		}	
		//ROS_INFO("Geobot has completed turn around");
		turn_around = true;
	}
	//*************************************************************************

	
	acquire_robotpose();
	
	x1 = pose.x + x0;
	local_path.push_back(x1);

	if(y1 < y2){
		local_path.push_back(pose.y - (y1+y2)/2);
	}
	if(y2 < y1){
		local_path.push_back(pose.y + (y1+y2)/2);
	}

	//ROS_INFO("Current X = %f ", pose.x);
	//ROS_INFO("Current Y = %f ", pose.y);
	//ROS_INFO("Pose_heading = %f ", pose.heading);
	//ROS_INFO("Lidar X = %f ", x0);
	//ROS_INFO("Lidar Left = %f ", y1);
	//ROS_INFO("Lidar Right = %f ", y2);
	//ROS_INFO("Next X = %f ", local_path[0]);
	//ROS_INFO("Next Y = %f ", local_path[1]);

	bendahead = path_curvature(pose.heading);
	//ROS_INFO("Bendahead is %f",bendahead);

	
	if (x0 > 0.25){
		linear_velocity_constraint = max((1 - pow((bendahead/(3.14*0.45)),1.5)),0.3); 

		linear_velocity = linear_velocity_constraint*maximum_linear_velocity; 
	
		if (linear_velocity > maximum_linear_velocity){
			linear_velocity = maximum_linear_velocity;
		}

		if (linear_velocity < -maximum_linear_velocity){
			linear_velocity = -maximum_linear_velocity;
		}

		if (distance_travelled > (total_distance - approaching_distance)){
		linear_velocity = 0.3;
		}
	}
	
	else linear_velocity = 0;


	if (abs(pose.y - local_path[1]) > path_error_deadband){
		angular_velocity_constraint = max((bendahead/(3.14*2)),0.3);
		
		if (y1 < y2){
			angular_velocity = -(angular_velocity_constraint*maximum_angular_velocity); 
		}

		if (y2 < y1){
			angular_velocity = angular_velocity_constraint*maximum_angular_velocity; 
		}

		if (angular_velocity > maximum_angular_velocity){
			angular_velocity = maximum_angular_velocity;
		}

		if (angular_velocity < -maximum_angular_velocity){
			angular_velocity = -maximum_angular_velocity;
		}

		if (distance_travelled > (total_distance - approaching_distance)){
			angular_velocity = 0.1;
		}
	}

	else angular_velocity = 0;

	velocity_command.linear.x = linear_velocity;
	velocity_command.linear.y = 0.0;
	velocity_command.linear.z = 0.0;
	velocity_command.angular.x = 0.0;
	velocity_command.angular.y = 0.0;
	velocity_command.angular.z = angular_velocity;

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

	velocity_cmdPublisher_.publish(velocity_command);
	local_pathPublisher_.publish(localplan2publish);

	distance_travelled += hypot(pose.x - prev_pose_x , pose.y - prev_pose_y);
	ROS_INFO("Distance travelled = %f \n", distance_travelled);
	
	prev_pose_x = pose.x;
	prev_pose_y = pose.y;

	}

	return true;

}

// Get the current pose of the geobot.
bool LocalPlannerUtil::acquire_robotpose()
{
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
	pose.heading = yaw;

	return true;
}

// Get the pose for the center of corridor point from lidar data.
void LocalPlannerUtil::acquire_obstacle_proximity(const pointcloud_to_laserscan::ObstacleProximity msg)
{
	y1 = msg.shortest_distance_to_wall_LS;
	y2 = msg.shortest_distance_to_wall_RS;
	x0 = msg.shortest_distance_to_obstacle_FT;
}



bool LocalPlannerUtil::run(long int a, long int b)
{

	bool goal_reached = false;
	bool returned = false;

	geometry_msgs::PoseStamped start;
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
	}

	//return goal_reached;

	geometry_msgs::PoseStamped finish;
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
		ROS_INFO("Cannot return");
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


}


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
  srv.request.a = atoll(argv[1]);
  srv.request.b = atoll(argv[2]);
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
  //ROS_INFO("Starteddddddddddddddddddddddd");
  geobot_local_planner_rupes::LocalPlannerUtil LPU;

  ros::waitForShutdown();

}