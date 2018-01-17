// Obtain the global path from the global planner
// While goal has not been reached keep generating local plan for the path controller to track
// If there is a new global plan, update the local plan

#include <local_planner.h>
#include <geometry_msgs/Twist>
#include <nav_msgs/Path>
#include <geobot_navigation/GetPlan.h>



using namespace std;

namespace geobot_local_planner{

LocalPlannerUtil::LocalPlannerUtil()
{
	nhPriv.param("maximum_linear_velocity", maximum_linear_velocity, 1.0);
	nhPriv.param("maximum_angular_velocity", maximum_angular_velocity, 1.0);
	nhPriv.param("error_tolerance2goal", error_tolerance2goal, 0.4);
	nhPriv.param("no_of_segments_ahead", no_of_segments_ahead, 3);
	nhPriv.param("error_gain", error_gain,2.5);
	nhPriv.param("cte_gain", cte_gain,1.0);
	nhPriv.param("heading_gain", heading_gain,2.0);

	velocity_cmdPublisher_ = nh.advertise<geometry_msgs::Twist>("vel_cmd", 20); // publish the velocity commands
  	local_pathPublisher_ = nh.advertise<nav_msgs::Path>("local_path", 20); // publish the local_path
  	// poseSubscriber_ = nh.subscribe("item_order",1000, &LocalPlannerUtil::subscribe_for_present_pose,this); // subscribe for the present pose
  	planSubscriber_ = nh.subscribe("global_path",10, &LocalPlannerUtil::subscribe_for_globalpath,this); 

  	// Subscribe to the messages and services we need
    move2goal_ = nh.advertiseService("move2goal", &LocalPlannerUtil::run, this); // This is a move2goal server

    makeplan_ = nh.serviceClient<geobot_navigation::GetPlan>("makeplan"); // datatype may require edit
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

	return result=quat2.angleShortestPath(&quat1);

}

double LocalPlannerUtil::path_curvature(double present_heading, int lookahead_segments)
{
	// compute the path curvature and add to the heading error between the robot heading and the path
	double lookahead_heading_deviation = 0.0;
	double init_angle = present_heading;
	double angle, diff_angle;

	for (int i = segment; i < segment + lookahead_segments; i++)
	{
		angle = atan2(local_path[segment+i][2] - local_path[segment][2], local_path[segment+i][1] - local_path[segment][1]);
		diff_angle = smallest_diff_angle(angle,  init_angle); // may require edit
		init_angle = angle;
		lookahead_heading_deviation = lookahead_heading_deviation + abs(diff_angle);
	}

	return lookahead_heading_deviation;

}



double LocalPlannerUtil::compute_cross_track_error()
{
	// compute the cross track error to local path
	double Dx, Dy, numerator, denominator;

	Dx = local_path[segment+1][1] - local_path[segment][1];
	Dy = local_path[segment+1][2] - local_path[segment][2];

	numerator = Dy*pose.x - Dx*pose.y - local_path[segment][1]*local_path[segment+1][2] + local_path[segment+1][1]*local_path[segment][2];
	denominator = (Dx^2 + Dy*2)^0.5;
	return numerator/denominator;

}



double LocalPlannerUtil::compute_along_track_error()
{

	 // compute the along track error on the local path
	 double L1 , L2, L3;
	 double theta, cross_track_error;

	 L1 = sqrt((pose.x - local_path[segment+1][1])^2 + (pose.y - local_path[segment+1][2])^2);
	 L2 = sqrt((local_path[segment+1][1] - local_path[segment][1])^2 + (local_path[segment+1][2] - local_path[segment][2])^2);
	 L3 = sqrt((pose.x - local_path[segment][1])^2 + (pose.y - local_path[segment][2])^2);

	 theta = acos(-(L3^2 - L1^2 - L2^2)/(2*L1*L2));
	 cross_track_error = L1*cos(theta);

	 return cross_track_error;
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

	tf::Transform odom_base_transform;
	tf::TransformListener listener;
	tf::Matrix3x3 mat;
	double roll;
	double pitch;
	double yaw;
	double along_track_error;
	int lookahead_segments;
	double bendahead, linear_velocity;
	double goal_heading, error_heading, cross_track_error;
	double approaching_velocity, segment_length;

	geometry_msgs::Twist velocity_command;
	vector<geometry_msgs::PoseStamped> plan;
	
	


	// Try tracking the given local path
	for (int i = 0; i < local_path.size(); i++)
	{
		segment = i;

		// Obtain present pose using lookup transform
		listener.lookupTransform("odom","base_link", ros::Time(0),odom_base_transform);

		mat.setRotation(odom_base_transform.getRotation());
		mat.getRPY(roll, pitch, yaw);

		pose.x = odom_base_transform.getOrigin().getX();
		pose.y = odom_base_transform.getOrigin().getY();
		pose.heading = yaw;

		along_track_error = compute_along_track_error(); // Uses pose and local_path which are private variables

		while (along_track_error < error_tolerance2goal) 
		{
			lookahead_segments = min(no_of_segments_ahead, local_path.size() - segment); 
			bendahead = path_curvature(pose.heading, lookahead_segments);

			// Adjusting velocity with road or path curvature
			// In case of rough terrain, this will be the place to adjust the velocity	
			velocity_constraint = (1 - (bendahead/(3.14*0.6))^1.5);
			velocity_constraint = max(velocity_constraint,0.1);
			linear_velocity = velocity_constraint*maximum_linear_velocity; 


			// Slowing down proportionally to the end of final goal
			if (segment == local_path.size()-1)
			{
				segment_length = sqrt((local_path[segment+1][1] - local_path[segment][1])^2 + (local_path[segment+1][2]- local_path[segment][2])^2);	
				approaching_velocity = (abs(along_track_error)/segment_length)*linear_velocity;
				linear_velocity = min(linear_velocity, approaching_velocity);
			}


			// compute the required angular velocity
			goal_heading = atan2(local_path[segment+1][2]-local_path[segment][2], local_path[segment+1][1] - local_path[segment][1]);
			error_heading = smallest_diff_angle(goal_heading, pose.heading);

			cross_track_error = smallest_diff_angle();

			angular_velocity = heading_gain*error_heading + error_gain*atan2(cte_gain*cross_track_error, linear_velocity); 

			if (angular_velocity > maximum_angular_velocity)
			{angular_velocity = maximum_angular_velocity}

			if (angular_velocity < -maximum_angular_velocity)
			{angular_velocity = -maximum_angular_velocity}
 
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

	          cout << "x------"<< local_path[i][0] << "y------" << local_path[i][1] << endl;
	     
	          local_plan.pose.orientation.x = quat.x();
	          local_plan.pose.orientation.y = quat.y();
	          local_plan.pose.orientation.z = quat.z();
	          local_plan.pose.orientation.w = quat.w();
	     
	          plan.push_back(local_plan);
	      	}

	      	local_pathPublisher_.publish(plan);
	      	plan.clear();


			along_track_error = compute_along_track_error(); // Uses pose and local_path which are private variables


		}



	}

	return true;

}


void LocalPlannerUtil::subscribe_for_globalpath(const nav_msgs::Path& path)
{
	// fill in the path message into a vector local path	

	vector <double>  new_point; 
	for (int i = 0; i < path.poses.size(); i++)
	{
		new_point.push_back(path.poses[i].pose.position.x);
        new_point.push_back(path.poses[i].pose.position.y);
        local_path.pushback(new_point);
		new_point.clear();
	}


}

bool LocalPlannerUtil::run(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response)
{
// Wait until a goal service is called
// Subscribe to the global path
// Assign the global path to the local path
// if no global path is available, call the makeplan service
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

	segment = 0;
	bool plansuccessful, goal_reached;	

	if (local_path.size() == 0)
	{
		// call to makeplan service client
		plansuccessful = makeplan_.call(request, response);
	}
	else
	{
		// plan exist
		plansuccessful = true;
	}

	if(plansuccessful)
	{
		goal_reached = path_tracking_controller();
	}
	else
	{
		goal_reached = false;
	}

	local_path.clear();

	return goal_reached;

}

}





int main(int argc, char **argv)
{
  // initializing ros
  ROS_INFO(" initializing geobot local planner");
  ros::init(argc, argv, "geobot_local_planner_node");

  geobot_local_planner::LocalPlannerUtil LPU;

  ros::spin();
}