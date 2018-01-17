// Obtain the global path from the global planner
// While goal has not been reached keep generating local plan for the path controller to track
// If there is a new global plan, update the local plan

#include <local_planner.h>
#include <geometry_msgs/Twist.h>
#include <geobot_navigation/GetPlan.h>
#include <tf/tf.h>
#include <tf/LinearMath/Quaternion.h>
#include <gap_finding_pkg/GapArray.h>
#include <pointcloud_to_laserscan/ObstacleProximity.h>




using namespace std;

namespace geobot_local_planner{

LocalPlannerUtil::LocalPlannerUtil(): nhPriv("~")
{
	//nhPriv.resolveName("~");
	//ros::NodeHandle nhPriv("~");		
	nhPriv.param("maximum_linear_velocity", maximum_linear_velocity, 1.0);
	nhPriv.param("maximum_angular_velocity", maximum_angular_velocity, 1.5);
	nhPriv.param("error_tolerance2goal", error_tolerance2goal, 0.4);
	nhPriv.param("no_of_segments_ahead", no_of_segments_ahead, 5);
	nhPriv.param("error_gain", error_gain,1.0);
	nhPriv.param("cte_gain", cte_gain,1.0);
	nhPriv.param("heading_gain", heading_gain,1.0);
	nhPriv.param("velocity_constraint", velocity_constraint,1.0);
	nhPriv.param("obstacle_clearance", obstacle_clearance, 0.3);
	nhPriv.param("trajectory_projection", trajectory_projection, 3.0);
	nhPriv.param("cross_track_error_deadband", cross_track_error_deadband, 0.2);
	nhPriv.param("side_distance_avoidance_threshold", side_distance_avoidance_threshold, 0.8);
	nhPriv.param("front_distance_avoidance_threshold", front_distance_avoidance_threshold, 2.2);
	nhPriv.param("side_avoidance_blindband", side_avoidance_blindband, 0.5);



	gap_dist_right = 0.0;
	gap_dist_left = 0.0;
	gap_angle_right = 0.0;
	gap_angle_left = 0.0;
	path2select = ORIGINAL_PATH;
	onwhich_sideofrobot_is_originalpath = LEFT_SIDE_OF_ROBOT;

	velocity_cmdPublisher_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 20); // publish the velocity commands
  	local_pathPublisher_ = nh.advertise<nav_msgs::Path>("local_path", 20); // publish the local_path
  	alternate_pathPublisher_ = nh.advertise<nav_msgs::Path>("alternate_path", 20); // publish the alternate_path
  	// poseSubscriber_ = nh.subscribe("item_order",1000, &LocalPlannerUtil::subscribe_for_present_pose,this); // subscribe for the present pose
  	// planSubscriber_ = nh.subscribe("global_path",10, &LocalPlannerUtil::subscribe_for_globalpath,this); 

  	// Subscribe to the services we need
    move2goal_ = nh.advertiseService("move2goal", &LocalPlannerUtil::run, this); // This is a move2goal server
    makeplan_ = nh.serviceClient<geobot_navigation::GetPlan>("makeplan"); 
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

double LocalPlannerUtil::path_curvature(double present_heading, int lookahead_segments)
{
	// compute the path curvature and add to the heading error between the robot heading and the path
	double lookahead_heading_deviation = 0.0;
	double init_angle = present_heading;
	double angle, diff_angle;

//	cout << "segment-----"<< segment << endl;
//	cout << "local_path size-----"<< local_path.size() << endl;

	for (int i = 1; i < lookahead_segments; i++)
	{
//		cout << "i-----"<< i << endl;

//		cout << "local_path[segment+i][1]-----"<< local_path[segment+i][1] << endl;
//		cout << "local_path[segment][1]-----"<< local_path[segment][1] << endl;
//		cout << "local_path[segment+i][0] -----"<< local_path[segment+i][0]  << endl;
//		cout << "local_path[segment][0]-----"<< local_path[segment][0] << endl;
		
		angle = atan2(local_path[segment+i][1] - local_path[segment][1], local_path[segment+i][0] - local_path[segment][0]);
//		cout << "angle-----"<< angle << endl;
		diff_angle = smallest_diff_angle(angle,  init_angle); // may require edit
//		cout << "diff_angle-----"<< diff_angle << endl;
		init_angle = angle;
		lookahead_heading_deviation = lookahead_heading_deviation + abs(diff_angle);
	}

	return lookahead_heading_deviation;

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

	if(abs(xte) <= cross_track_error_deadband)  // This is to avoid oscillation of the robot around the path
	{
		xte = 0.0;
	}

	return xte;

}



double LocalPlannerUtil::compute_along_track_error()
{

	 // compute the along track error on the local path
	 double L1 , L2, L3;
	 double theta, along_track_error;

	 L1 = sqrt(pow((pose.x - local_path[segment+1][0]),2) + pow((pose.y - local_path[segment+1][1]),2));
	 L2 = sqrt(pow((local_path[segment+1][0] - local_path[segment][0]),2) + pow((local_path[segment+1][1] - local_path[segment][1]),2));
	 L3 = sqrt(pow((pose.x - local_path[segment][0]),2) + pow((pose.y - local_path[segment][1]),2));

	 theta = acos(-(L3*L3 - L1*L1 - L2*L2)/(2*L1*L2));
	 along_track_error = L1*cos(theta);

	 return along_track_error;
}

int LocalPlannerUtil::original_path2robot(double x0, double y0, double x1, double y1, double x2, double y2)
{
	double Dx, Dy, numerator, denominator, xte;

	Dx = x2 - x1;
	Dy = y2 - y1;

	numerator = Dy*x0 - Dx*y0 - x1*y2 + x2*y1;
	denominator = sqrt(Dx*Dx + Dy*Dy);
	xte = numerator/denominator;
/*

	if(abs(xte) <= cross_track_error_deadband)
	{
		xte = 0.0;
	}
*/
	if(xte >= 0.0)
	{return LEFT_SIDE_OF_ROBOT;}
	else
	{return RIGHT_SIDE_OF_ROBOT;}

}



bool LocalPlannerUtil::path_tracking_controller()
{
// Obtain present pose using lookup transform or subscribing for pose
// Track the local path
// publish the velocity command
// publish the local path within a window size

// Subscribe for obstacle configuration
// plan new route depending on obstacle configuration
// and track the new path until clear

// return 0 if goal unreachable

	double angular_velocity;
	double steering_angle;
	double along_track_error;
	int lookahead_segments, remaining_segments;
	double bendahead, linear_velocity;
	double goal_heading, error_heading, cross_track_error;
	double approaching_velocity, segment_length;
	int sequence = 0;
	bool obstacle_on_the_way = false;


	geometry_msgs::Twist velocity_command;
	vector<geometry_msgs::PoseStamped> plan;
	nav_msgs::Path localplan2publish, alternateplan2publish;
	
	Path_definition start_point, end_point;
	double LR, LL, L3, LR_heading, LL_heading, x1, x2, y1, y2, x_t, offset_direction, path_offset, x_center, y_center, new_traj_heading;


	// Try tracking the given local path
	for (int i = 0; i < local_path.size()-1; i++)
	{
		segment = i;
//		cout << "segment counter-----"<< segment << endl;

		
		along_track_error = compute_along_track_error();
//		cout << "along_track_error_start-----"<< along_track_error << endl;

		while (along_track_error > error_tolerance2goal) 
		{
			// Obtain present pose using lookup transform
			acquire_robotpose(); // pose is a private variable

			
			// If there is no obstacle, track the original local path
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			obstacle_on_the_way = false;
			start_point.x = local_path[segment][0] ;
			start_point.y = local_path[segment][1] ;
			end_point.x = local_path[segment+1][0] ;
			end_point.y = local_path[segment+1][1] ;



			// Computing robot position to the original local path tracked
			// onwhich_sideofrobot_is_originalpath is a private variable
			onwhich_sideofrobot_is_originalpath = original_path2robot(pose.x, pose.y, start_point.x, start_point.y, end_point.x, end_point.y);

			// check out for obstacles and choose path type
			// path2select, gap_position2obstacle are private variables
			// and are updated in choose_path()
			choose_path();
			
			if(path2select == OFFSET_ORIGINAL_PATH)
			{
				// If there is obstacle, offset the original local path
				// gap_dist_right and other gap parameters are private variable
				obstacle_on_the_way = true;

				LR = gap_dist_right;
				LL = gap_dist_left;

				LR_heading = fmod((pose.heading - gap_angle_right) , M_PI);
				LL_heading = fmod((pose.heading - gap_angle_left) , M_PI);

				x1 = pose.x + LR*cos(LR_heading);
				y1 = pose.y + LR*sin(LR_heading);
				x2 = pose.x + LL*cos(LL_heading);
				y2 = pose.y + LL*sin(LL_heading);

				

				if(gap_position2obstacle == GAP_RIGHT_SIDE_OF_OBSTACLE)
				{
					x_t = compute_cross_track_error(x2, y2, start_point.x, start_point.y, end_point.x, end_point.y);
					offset_direction = atan2(end_point.y - start_point.y, end_point.x - start_point.x) + M_PI/2;
					path_offset = x_t + obstacle_clearance;
				}
				else
				{
					x_t = compute_cross_track_error(x1, y1, start_point.x, start_point.y, end_point.x, end_point.y);
					offset_direction = atan2(end_point.y - start_point.y, end_point.x - start_point.x) + M_PI/2;
					path_offset = x_t - obstacle_clearance;
				}

				// what out for the sin and cos placement
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

				LR_heading = fmod((pose.heading - gap_angle_right) , M_PI);
				LL_heading = fmod((pose.heading - gap_angle_left) , M_PI);

				x1 = pose.x + LR*cos(LR_heading);
				y1 = pose.y + LR*sin(LR_heading);
				x2 = pose.x + LL*cos(LL_heading);
				y2 = pose.y + LL*sin(LL_heading);

				L3 = sqrt(pow((end_point.x - start_point.x),2) + pow((end_point.y - start_point.y),2));	


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

				new_traj_heading = atan2(y2 - y1, x2 - x1) + M_PI/2;

				start_point.x = x_center;
				start_point.y = y_center;
				end_point.x = x_center + trajectory_projection*cos(new_traj_heading);
				end_point.y = y_center + trajectory_projection*sin(new_traj_heading);

			}


			if(path2select == NORMAL_PATH_TO_GAP)
			{
				
				double angle = atan2(end_point.y - start_point.y, end_point.x - start_point.x);
//				cout << "angle-----"<< angle << endl;
				double diff_angle = smallest_diff_angle(angle,  pose.heading); 
//				cout << "diff_angle-----"<< diff_angle << endl;
				bendahead = abs(diff_angle);
			}
			else
			{
				remaining_segments = local_path.size() - segment;
//				cout << "remaining_segments-----"<< remaining_segments << endl;
				lookahead_segments = min(no_of_segments_ahead, remaining_segments); 
//				cout << "lookahead_segments-----"<< lookahead_segments << endl;
				bendahead = path_curvature(pose.heading, lookahead_segments); 
//				cout << "bendahead-----"<< bendahead << " pose.heading-----"<< pose.heading << " pose.x-----"<< pose.x << " pose.y-----"<< pose.y << endl;
			}



			// Adjusting velocity with road or path curvature
			// In case of rough terrain, this will be the place to adjust the velocity	
			velocity_constraint = (1 - pow((bendahead/(3.14*0.6)),1.5));
//			cout << "velocity_constraint-----"<< velocity_constraint << endl;
			velocity_constraint = max(velocity_constraint,0.1);
			linear_velocity = velocity_constraint*maximum_linear_velocity; 


			// Slowing down proportionally to the end of final goal
			if (segment == local_path.size()-1)
			{
				segment_length = sqrt(pow((local_path[segment+1][0] - local_path[segment][0]),2) + pow((local_path[segment+1][1]- local_path[segment][1]),2));	
				approaching_velocity = (abs(along_track_error)/segment_length)*linear_velocity;
				linear_velocity = min(linear_velocity, approaching_velocity);
			}
//			cout << "linear_velocity-----"<< linear_velocity << endl;

			// compute the required angular velocity
			goal_heading = atan2(end_point.y - start_point.y, end_point.x - start_point.x);
//			cout << "goal_heading-----"<< goal_heading << endl;
			//error_heading = smallest_diff_angle(goal_heading, pose.heading); // check this

			error_heading = goal_heading - pose.heading;
			// computing smallest angle
			if (error_heading > M_PI)
			{
				error_heading = error_heading - (M_PI*2);
			}

			if (error_heading < -M_PI)
			{
				error_heading = error_heading + (M_PI*2);
			}



//			cout << "error_heading-----"<< error_heading << endl;

			cross_track_error = compute_cross_track_error(pose.x, pose.y, start_point.x, start_point.y, end_point.x, end_point.y);
//			cout << "cross_track_error-----"<< cross_track_error << endl;

			steering_angle = heading_gain*error_heading + error_gain*atan2(cte_gain*cross_track_error,linear_velocity);  //check this
		
			angular_velocity = steering_angle;

//			cout << "angular_velocity-----"<< angular_velocity << endl;

			if (angular_velocity > maximum_angular_velocity)
			{angular_velocity = maximum_angular_velocity;}

			if (angular_velocity < -maximum_angular_velocity)
				{angular_velocity = -maximum_angular_velocity;}


 
			// then publish the commanded velocity
			velocity_command.linear.x = linear_velocity;
			velocity_command.linear.y= 0.0;
			velocity_command.linear.z= 0.0;

			velocity_command.angular.x = 0.0;
			velocity_command.angular.y = 0.0;
			velocity_command.angular.z = angular_velocity;

			velocity_cmdPublisher_.publish(velocity_command);


			

			// Publish out the local plan presently followed
			ros::Time time_now = ros::Time::now();

	        for (int i = segment; i < segment + lookahead_segments; i++)
	        {
	          geometry_msgs::PoseStamped local_plan;
	          tf::Quaternion quat = tf::createQuaternionFromYaw(0);

	          local_plan.header.seq = i;
	          local_plan.header.stamp = time_now;
	          local_plan.header.frame_id = "odom";
          
	          local_plan.pose.position.x = local_path[i][0];  // Latitude
	          local_plan.pose.position.y = local_path[i][1];  // Longitude

	          // cout << "x------"<< local_path[i][0] << "y------" << local_path[i][1] << endl;
	     
	          local_plan.pose.orientation.x = quat.x();
	          local_plan.pose.orientation.y = quat.y();
	          local_plan.pose.orientation.z = quat.z();
	          local_plan.pose.orientation.w = quat.w();
	     
	          plan.push_back(local_plan);
	      	}


	      	localplan2publish.poses = plan;
		    localplan2publish.header.seq = sequence++;
		    localplan2publish.header.stamp = ros::Time::now();
		    localplan2publish.header.frame_id = "odom";
	      	local_pathPublisher_.publish(localplan2publish);
	      	plan.clear();


	      	// Publish the alternate path to avoid the obstacle
		    if(obstacle_on_the_way)
		    {
		      geometry_msgs::PoseStamped alternate_plan;
	          tf::Quaternion alternate_quat = tf::createQuaternionFromYaw(0);

	          alternate_plan.header.seq = 0;
	          alternate_plan.header.stamp = time_now;
	          alternate_plan.header.frame_id = "odom";
          
	          alternate_plan.pose.position.x = start_point.x;  // Latitude
	          alternate_plan.pose.position.y = start_point.y;  // Longitude
	         	     
	          alternate_plan.pose.orientation.x = alternate_quat.x();
	          alternate_plan.pose.orientation.y = alternate_quat.y();
	          alternate_plan.pose.orientation.z = alternate_quat.z();
	          alternate_plan.pose.orientation.w = alternate_quat.w();
	          plan.push_back(alternate_plan);

	          alternate_plan.header.seq = 1;
	          alternate_plan.header.stamp = time_now;
	          alternate_plan.header.frame_id = "odom";
          
	          alternate_plan.pose.position.x = end_point.x;  // Latitude
	          alternate_plan.pose.position.y = end_point.y;  // Longitude
	         	     
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

		    }


			along_track_error = compute_along_track_error(); 
//			cout << "along_track_error-----"<< along_track_error << endl;

		}



	}

	return true;

}

bool LocalPlannerUtil::acquire_robotpose()
{
	tf::StampedTransform odom_base_transform;
	tf::Matrix3x3 mat;
	double roll;
	double pitch;
	double yaw;

	
	try{
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



// Note:
// To avoid acquiring global path again (by calling makeplan service) after it has been already computed by the global planner node,
// another function as below can be added but as a subscriber. 
// Caveat: local_path variable cannot be overwritten while tracking is being performed

void LocalPlannerUtil::acquire_globalpath(std::vector<geometry_msgs::PoseStamped>& path)
{
	// fill in the path message into a vector local path	

	vector <double>  new_point; 
	for (int i = 0; i < path.size(); i++)
	{
		new_point.push_back(path[i].pose.position.x);
        new_point.push_back(path[i].pose.position.y);
        local_path.push_back(new_point);
		new_point.clear();
	}


}



// This is to find the best candidate gap and the path to take
void LocalPlannerUtil::choose_path()
{
	// subcribe to candidate gaps
	// subscribe to obstacle region
	// find best candidate gap
	// determine which path to take

	gap_finding_pkg::GapArray candidate_gap_msg;
	pointcloud_to_laserscan::ObstacleProximity obstacle_proximity_msg;
	double shortest_distance_to_obstacle_LS, shortest_distance_to_obstacle_RS, shortest_distance_to_obstacle_FT;
	

	try
	{
		candidate_gap_msg = *(ros::topic::waitForMessage<gap_finding_pkg::GapArray>("candidate_gaps", ros::Duration(0.5)));
		
	}
	catch(...)
	{
		ROS_ERROR("Could not get candidate_gaps message");
	}


	try
	{
		obstacle_proximity_msg = *(ros::topic::waitForMessage<pointcloud_to_laserscan::ObstacleProximity>("obstacle_proximity", ros::Duration(0.5)));
		shortest_distance_to_obstacle_LS = obstacle_proximity_msg.shortest_distance_to_obstacle_LS;
		shortest_distance_to_obstacle_FT = obstacle_proximity_msg.shortest_distance_to_obstacle_FT;
		shortest_distance_to_obstacle_RS = obstacle_proximity_msg.shortest_distance_to_obstacle_RS;
	}
	catch(...)
	{
		shortest_distance_to_obstacle_LS = 0.0;
		shortest_distance_to_obstacle_FT = 0.0;
		shortest_distance_to_obstacle_RS = 0.0;
		ROS_ERROR("Could not get obstacle_proximity message");
	}
	


	std::vector<double > best_candidate_gap, candidate_gap_smallest2LS, candidate_gap_smallest2RS;
	
	double closest_localpath_trajectory_heading = atan2(local_path[segment+1][1] - local_path[segment][1], local_path[segment+1][0] - local_path[segment][0]);
	double SR_diff_smallest = M_PI*2; // initializing to a large angle
	double SL_diff_smallest = M_PI*2; // initializing to a large angle
	double SR_heading, SL_heading, SR_diff, SL_diff;

	if(!candidate_gap_msg.gaps.empty()) // That is, if there are gaps to drive through
	{
		for(int i = 0; i < candidate_gap_msg.gaps.size(); i++)
		{
			SR_heading = fmod((pose.heading - candidate_gap_msg.gaps[i].angle_right),M_PI);
			SR_diff = abs(smallest_diff_angle(closest_localpath_trajectory_heading, SR_heading));
			SL_heading = fmod((pose.heading - candidate_gap_msg.gaps[i].angle_left),M_PI);
			SL_diff = abs(smallest_diff_angle(closest_localpath_trajectory_heading, SL_heading));

			// finding the closest gap ray to the tracked path
			if(SR_diff < SR_diff_smallest)
			{
				SR_diff_smallest = SR_diff;
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].dist_right);
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].dist_left);
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].angle_right);
				candidate_gap_smallest2RS.push_back(candidate_gap_msg.gaps[i].angle_left);
			}
			if(SL_diff < SL_diff_smallest)
			{
				SL_diff_smallest = SL_diff;
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].dist_right);
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].dist_left);
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].angle_right);
				candidate_gap_smallest2LS.push_back(candidate_gap_msg.gaps[i].angle_left);
			}


			// finding the side of the gap with respect to the obstacle
			if(SL_diff_smallest < SR_diff_smallest)
			{
				gap_dist_right = candidate_gap_smallest2LS[0];
				gap_dist_left = candidate_gap_smallest2LS[1];
				gap_angle_right = candidate_gap_smallest2LS[2];
				gap_angle_left = candidate_gap_smallest2LS[3];
				gap_position2obstacle = GAP_LEFT_SIDE_OF_OBSTACLE; // left sided gap.
			}
			if(SL_diff_smallest >= SR_diff_smallest)
			{
				gap_dist_right = candidate_gap_smallest2RS[0];
				gap_dist_left = candidate_gap_smallest2RS[1];
				gap_angle_right = candidate_gap_smallest2RS[2];
				gap_angle_left = candidate_gap_smallest2RS[3];
				gap_position2obstacle = GAP_RIGHT_SIDE_OF_OBSTACLE; // right sided gap. That is, the robot is right sided
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

	// initialization
	int obstacle_array[3] = {LEFT_SIDE_OPENED, FRONT_SIDE_OPENED,  RIGHT_SIDE_OPENED}; // L F R


	
	if(shortest_distance_to_obstacle_LS < side_distance_avoidance_threshold)
	{
		obstacle_array[0] = 1;
	}
	if(shortest_distance_to_obstacle_FT < front_distance_avoidance_threshold)
	{
		obstacle_array[1] = 1;
	}
	if(shortest_distance_to_obstacle_RS < side_distance_avoidance_threshold)
	{
		obstacle_array[2] = 1;
	}



	if(gap_position2obstacle != NO_GAP)
	{
		// selecting which path to take
		if((obstacle_array[0] == LEFT_SIDE_OPENED) &&  (obstacle_array[1] == FRONT_SIDE_OPENED) && (obstacle_array[2] == RIGHT_SIDE_OPENED))
		{
			// keep tracking previous path selected until there is an opening
			if((shortest_distance_to_obstacle_LS > (side_distance_avoidance_threshold + side_avoidance_blindband)) && (shortest_distance_to_obstacle_RS > (side_distance_avoidance_threshold + side_avoidance_blindband)))
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
			if(onwhich_sideofrobot_is_originalpath = RIGHT_SIDE_OF_ROBOT)
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
		}
		else if((obstacle_array[0] == LEFT_SIDE_BLOCKED) && (obstacle_array[1] == FRONT_SIDE_BLOCKED) && (obstacle_array[2] == RIGHT_SIDE_OPENED))
		{
			path2select = NORMAL_PATH_TO_GAP;
			if(gap_position2obstacle == GAP_RIGHT_SIDE_OF_OBSTACLE)
			{ path2select = OFFSET_ORIGINAL_PATH;}
		}
	}



}

// This is to drive to a goal
bool LocalPlannerUtil::run(geobot_navigation::SetGoal::Request& req, geobot_navigation::SetGoal::Response& resp)
{
// Wait until a goal service is called
// Acquire the global path from service response
// Assign the global path to the local path
// Call the path_tracking_controller
// Alert the operator of goal completion
// and wait for another goal service to be called

	nhPriv.getParam("maximum_linear_velocity", maximum_linear_velocity);
	nhPriv.getParam("maximum_angular_velocity", maximum_angular_velocity);
	nhPriv.getParam("error_tolerance2goal", error_tolerance2goal);
	nhPriv.getParam("no_of_segments_ahead", no_of_segments_ahead);
	nhPriv.getParam("error_gain", error_gain);
	nhPriv.getParam("cte_gain", cte_gain);
	nhPriv.getParam("heading_gain", heading_gain);
	nhPriv.getParam("velocity_constraint", velocity_constraint);

	geobot_navigation::GetPlan srv_getplan;
	srv_getplan.request.goal = req.goal;
	bool goal_reached = false;

	geometry_msgs::PoseStamped start;

	if(!acquire_robotpose()) // update the robot pose
	{
		ROS_ERROR("An error as occurred");
		return goal_reached;
	}

	tf::Quaternion start_quat = tf::createQuaternionFromYaw(0);
    start.pose.position.x = pose.x;  
    start.pose.position.y = pose.y; 
     
    start.pose.orientation.x = start_quat.x();
    start.pose.orientation.y = start_quat.y();
    start.pose.orientation.z = start_quat.z();
    start.pose.orientation.w = start_quat.w();


	srv_getplan.request.start = start;

	segment = 0;
		

	// call to makeplan service client
	// if makeplan is successful, try tracking the path

	if (makeplan_.call(srv_getplan))
	{
		acquire_globalpath(srv_getplan.response.plan);
		goal_reached = path_tracking_controller();
		local_path.clear();
	}
	else
		{ROS_INFO("Global path is not acquired");}

	if(goal_reached)
	{
		ROS_INFO("Goal is reached");
	}
	else
	{
		ROS_INFO("Goal unreachable");
	}


	return goal_reached;

}



// This service can be called to  explore the environment using widest gap approach 
// Not yet developed but it will work like the "bool LocalPlannerUtil::run(geobot_navigation::SetGoal::Request& req, geobot_navigation::SetGoal::Response& resp)"
// but with no goal just an empty call.

//bool LocalPlannerUtil::explpore()
//{}

}





int main(int argc, char **argv)
{
  // initializing ros
  ROS_INFO(" initializing geobot local planner");
  ros::init(argc, argv, "geobot_local_planner_node");

  geobot_local_planner::LocalPlannerUtil LPU;

  ros::spin();
}