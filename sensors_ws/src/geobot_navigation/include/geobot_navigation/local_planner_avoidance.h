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
#include <geobot_navigation/GapDirection.h>
#include <geobot_navigation/SetGoalAction.h>
#include <actionlib/server/simple_action_server.h>
#include <tf/transform_listener.h>
#include <gap_finding_pkg/GapArray.h>
#include <pointcloud_to_laserscan/ObstacleProximity.h>
#include <sensor_msgs/Joy.h>
#include <geobot_navigation/navsat_conversions.h>
#include <dynamic_reconfigure/server.h>
#include <geobot_navigation/GainsConfig.h>

// path2select
#define ORIGINAL_PATH 0
#define OFFSET_ORIGINAL_PATH 1
#define NORMAL_PATH_TO_GAP 2
// gap_position2obstacle
#define GAP_LEFT_SIDE_OF_OBSTACLE 0
#define GAP_RIGHT_SIDE_OF_OBSTACLE 1
#define NO_GAP 3
// onwhich_sideofrobot_is_originalpath
#define LEFT_SIDE_OF_ROBOT 0
#define RIGHT_SIDE_OF_ROBOT 1

// obstacle configuration
#define LEFT_SIDE_BLOCKED 1
#define LEFT_SIDE_OPENED 0
#define FRONT_SIDE_BLOCKED 1
#define FRONT_SIDE_OPENED 0
#define RIGHT_SIDE_BLOCKED 1
#define RIGHT_SIDE_OPENED 0


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

struct Path_definition
{
	double x;
	double y;
};

vector <vector <double> >  local_path;
double minimum_velocity_constraint;
double maximum_linear_velocity;
double maximum_angular_velocity;
double velocity_constraint;
double error_tolerance2goal;
double error_gain, cte_gain, heading_gain, derivative_gain, steering_gain, derivative_heading_gain, proportional_gain, integral_gain, proportional_heading_gain, integral_heading_gain;
double min_delta_time; // for  D controller
double side_distance_avoidance_threshold, front_distance_avoidance_threshold, side_avoidance_blindband;
int no_of_segments_ahead;
int path2select;
int gap_position2obstacle;
int onwhich_sideofrobot_is_originalpath;



double obstacle_clearance, trajectory_projection, cross_track_error_deadband;
double gap_dist_right, gap_dist_left, gap_angle_right, gap_angle_left;
bool override_by_joystick;

ros::NodeHandle nh;
ros::NodeHandle nhPriv;
ros::Subscriber planSubscriber_, obstacle_proximitySubscriber_, gap_arraySubscriber_, joystickoverideSubscriber_;
ros::Publisher velocity_cmdPublisher_, local_pathPublisher_, alternate_pathPublisher_, gapDirectionPublisher_;
ros::ServiceServer move2goal_;
ros::ServiceClient makeplan_;
actionlib::SimpleActionServer<geobot_navigation::SetGoalAction> move2goal_action_; 
tf::TransformListener listener; // should not be in a callback

gap_finding_pkg::GapArray candidate_gap_msg;
pointcloud_to_laserscan::ObstacleProximity obstacle_proximity_msg;
string updatedpath_filename, utmZone;

dynamic_reconfigure::Server<geobot_navigation::GainsConfig> server;
dynamic_reconfigure::Server<geobot_navigation::GainsConfig>::CallbackType f;


public:

LocalPlannerUtil();
double smallest_diff_angle(double theta2, double theta1);
double path_curvature(double present_heading, int lookahead_segments);
double compute_cross_track_error(double x0, double y0, double x1, double y1, double x2, double y2);
double compute_along_track_error();
bool path_tracking_controller();
bool acquire_robotpose();
void acquire_globalpath(std::vector<geometry_msgs::PoseStamped>& path);
//bool run(geobot_navigation::SetGoal::Request& req, geobot_navigation::SetGoal::Response& resp); //for service
bool run(const geobot_navigation::SetGoalGoalConstPtr& req); //for action
int original_path2robot(double x0, double y0, double x1, double y1, double x2, double y2);
void choose_path();
void acquire_candidate_gaps(const gap_finding_pkg::GapArray msg);
void acquire_obstacle_proximity(const pointcloud_to_laserscan::ObstacleProximity msg);
void joystickoveride(const sensor_msgs::Joy joy_msg);
void parameter_callback(geobot_navigation::GainsConfig &config, uint32_t level);

};

};