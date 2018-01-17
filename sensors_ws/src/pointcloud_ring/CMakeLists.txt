cmake_minimum_required(VERSION 2.8.3)
project(pointcloud_ring)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
)


catkin_package(
#  INCLUDE_DIRS include
# LIBRARIES pointcloud_ring
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs
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

## Declare a C++ library
# add_library(pointcloud_ring
#   src/${PROJECT_NAME}/pointcloud_ring.cpp
# )



## Declare a C++ executable
add_executable(pointcloud_ring_node src/converter_cloud2.cpp)



## Specify libraries to link a library or executable target against
target_link_libraries(pointcloud_ring_node
  ${catkin_LIBRARIES}
)


