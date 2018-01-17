#include "ros/ros.h"
#include "geobot_navigation_rupes/Path.h"
#include <tf/tf.h>

bool add(geobot_navigation_rupes::Path::Request  &req,
         geobot_navigation_rupes::Path::Response &res)
{
  res.path1 = req.a;
  res.path2 = req.b;
  ROS_INFO("distance= %f, heading= %f", (double)req.a, (double)req.b);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "geobot_global_planner_node");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("path", add);
  ROS_INFO("initializing geobot_global_planner_node");
  ros::spin();

  return 0;
}
