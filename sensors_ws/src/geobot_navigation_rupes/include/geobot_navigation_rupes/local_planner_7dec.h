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
#include <geobot_navigation_rupes/Path.h>
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
#include <geobot_navigation_rupes/navsat_conversions.h>
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

namespace geobot_local_planner_rupes{

class LocalPlannerUtil{

private: 

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
Path_definition start_point, end_point;
pointcloud_to_laserscan::ObstacleProximity obstacle_proximity_msg;
gap_finding_pkg::GapArray candidate_gap_msg;
tf::TransformListener listener;
ros::NodeHandle nh;
ros::Publisher velocity_cmdPublisher_, local_pathPublisher_, alternate_pathPublisher_, gapDirectionPublisher_;
ros::Subscriber joystickoverideSubscriber_, obstacle_proximitySubscriber_, gap_arraySubscriber_;

bool override_by_joystick;
bool turn_around;
double front, front_plus_current, left, right;
vector <double> local_path;
double turnaround_threshold, path_error_deadband, angular_velocity_turnaround;
double maximum_linear_velocity, maximum_angular_velocity;
double approaching_distance;
double distance_travelled;
double bendahead, linear_velocity_constraint, angular_velocity_constraint, velocity_constraint;
double linear_velocity, angular_velocity;
double direction, error_heading;
double cross_track_error;
int path2select;
int gap_position2obstacle;
int onwhich_sideofrobot_is_originalpath;
double error_gain, cte_gain, heading_gain, derivative_gain, steering_gain, derivative_heading_gain, proportional_gain, integral_gain, proportional_heading_gain, integral_heading_gain;
double min_delta_time; // for  D controller
double side_distance_avoidance_threshold, front_distance_avoidance_threshold, side_avoidance_blindband;
double obstacle_clearance, trajectory_projection, cross_track_error_deadband;
double gap_dist_right, gap_dist_left, gap_angle_right, gap_angle_left;
double right_turn, left_turn, diff_turn;


public:

LocalPlannerUtil();
bool acquire_robotpose();
void acquire_obstacle_proximity(const pointcloud_to_laserscan::ObstacleProximity msg);
void joystickoveride(const sensor_msgs::Joy joy_msg);
double smallest_diff_angle(double theta2, double theta1);
double path_curvature(double present_heading);
bool path_tracking_controller(double total_distance, int mode);
bool run(double a, double b);
double compute_cross_track_error(double current_x, double current_y, double start_x, double start_y, double next_x, double next_y);
void acquire_candidate_gaps(const gap_finding_pkg::GapArray msg);
int original_path2robot(double current_x, double current_y, double start_x, double start_y, double next_x, double next_y);
void choose_path();

};

};
