cmake_minimum_required(VERSION 2.8.3)
project(geobot_navigation_rupes)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
roscpp rospy std_msgs genmsg message_generation 
  tf
  angles
  pointcloud_to_laserscan
  gap_finding_pkg
  dynamic_reconfigure
)

## Declare ROS messages and services
add_message_files(FILES Num.msg)
add_service_files(FILES Path.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs
				geometry_msgs
				actionlib_msgs
)

## Declare a catkin package
catkin_package(  INCLUDE_DIRS include
  LIBRARIES geobot_navigation_rupes
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs message_runtime dynamic_reconfigure
  DEPENDS system_lib
  tf
  pointcloud_to_laserscan
  )

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})



add_executable(global_planner_rupes src/global_planner_my.cpp)
target_link_libraries(global_planner_rupes ${catkin_LIBRARIES})
add_dependencies(global_planner_rupes geobot_navigation_rupes_generate_messages_cpp)

add_executable(local_planner_rupes src/local_planner_my.cpp)
target_link_libraries(local_planner_rupes ${catkin_LIBRARIES})
add_dependencies(local_planner_rupes geobot_navigation_rupes_generate_messages_cpp)

