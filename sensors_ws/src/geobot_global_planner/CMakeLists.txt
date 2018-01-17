cmake_minimum_required(VERSION 2.8.3)
project(geobot_global_planner)

find_package(catkin REQUIRED
  COMPONENTS
    angles
    costmap_2d
    dynamic_reconfigure
    geometry_msgs
    nav_core
    navfn
    nav_msgs
    pluginlib
    roscpp
    tf
)



catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    costmap_2d
    dynamic_reconfigure
    geometry_msgs
    nav_core
    navfn
    nav_msgs
    pluginlib
    roscpp
    tf
)

include_directories(~/ros_ws/src/geobot_global_planner/include/geobot_global_planner
  include
  ${catkin_INCLUDE_DIRS}
)


## Declare a C++ library
add_library(geobot_global_planner_lib   src/geobot_global_planner.cpp
)
