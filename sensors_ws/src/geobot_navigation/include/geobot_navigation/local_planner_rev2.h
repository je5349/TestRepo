#include <ros/ros.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>
#include <geobot_navigation/SetGoal.h>
#include <tf/transform_listener.h>

using namespace std;

namespace geobot_local_planner{

class LocalPlannerUtil{

private:

//double cross_track_error;
//double along_track_error;
int segment;
struct Pose_{
	double x;
	double y;
	double heading;
};
Pose_ pose;

vector <vector <double> >  local_path;
double maximum_linear_velocity;
double maximum_angular_velocity;
double velocity_constraint;
double error_tolerance2goal;
double error_gain, cte_gain, heading_gain;
int no_of_segments_ahead;

ros::NodeHandle nh;
//ros::NodeHandle nhPriv;
ros::Subscriber planSubscriber_;
ros::Publisher velocity_cmdPublisher_, local_pathPublisher_;
ros::ServiceServer move2goal_;
ros::ServiceClient makeplan_;
tf::TransformListener listener; // should not be in a callback




public:

LocalPlannerUtil();
double smallest_diff_angle(double theta2, double theta1);
double path_curvature(double present_heading, int lookahead_segments);
double compute_cross_track_error();
double compute_along_track_error();
bool path_tracking_controller();
bool acquire_robotpose();
void acquire_globalpath(std::vector<geometry_msgs::PoseStamped>& path);
bool run(geobot_navigation::SetGoal::Request& req, geobot_navigation::SetGoal::Response& resp);

};

};