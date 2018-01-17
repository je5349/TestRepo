cmake_minimum_required(VERSION 2.8.3)
project(convert_slam_pose)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  std_msgs
)


# find_package(Boost REQUIRED COMPONENTS system)




## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   geometry_msgs#   nav_msgs#   std_msgs
 )



###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES convert_slam_pose
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp std_msgs
  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)



## Declare a C++ executable
 add_executable(convert_slam_pose_node src/convert_slam_pose.cpp)


## Specify libraries to link a library or executable target against
 target_link_libraries(convert_slam_pose_node
   ${catkin_LIBRARIES}
 )

