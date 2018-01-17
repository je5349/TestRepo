# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "pointcloud_to_laserscan: 2 messages, 0 services")

set(MSG_I_FLAGS "-Ipointcloud_to_laserscan:/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(pointcloud_to_laserscan_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg" NAME_WE)
add_custom_target(_pointcloud_to_laserscan_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pointcloud_to_laserscan" "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg" NAME_WE)
add_custom_target(_pointcloud_to_laserscan_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pointcloud_to_laserscan" "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(pointcloud_to_laserscan
  "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pointcloud_to_laserscan
)
_generate_msg_cpp(pointcloud_to_laserscan
  "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pointcloud_to_laserscan
)

### Generating Services

### Generating Module File
_generate_module_cpp(pointcloud_to_laserscan
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pointcloud_to_laserscan
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(pointcloud_to_laserscan_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(pointcloud_to_laserscan_generate_messages pointcloud_to_laserscan_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg" NAME_WE)
add_dependencies(pointcloud_to_laserscan_generate_messages_cpp _pointcloud_to_laserscan_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg" NAME_WE)
add_dependencies(pointcloud_to_laserscan_generate_messages_cpp _pointcloud_to_laserscan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pointcloud_to_laserscan_gencpp)
add_dependencies(pointcloud_to_laserscan_gencpp pointcloud_to_laserscan_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pointcloud_to_laserscan_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(pointcloud_to_laserscan
  "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pointcloud_to_laserscan
)
_generate_msg_lisp(pointcloud_to_laserscan
  "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pointcloud_to_laserscan
)

### Generating Services

### Generating Module File
_generate_module_lisp(pointcloud_to_laserscan
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pointcloud_to_laserscan
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(pointcloud_to_laserscan_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(pointcloud_to_laserscan_generate_messages pointcloud_to_laserscan_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg" NAME_WE)
add_dependencies(pointcloud_to_laserscan_generate_messages_lisp _pointcloud_to_laserscan_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg" NAME_WE)
add_dependencies(pointcloud_to_laserscan_generate_messages_lisp _pointcloud_to_laserscan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pointcloud_to_laserscan_genlisp)
add_dependencies(pointcloud_to_laserscan_genlisp pointcloud_to_laserscan_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pointcloud_to_laserscan_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(pointcloud_to_laserscan
  "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pointcloud_to_laserscan
)
_generate_msg_py(pointcloud_to_laserscan
  "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pointcloud_to_laserscan
)

### Generating Services

### Generating Module File
_generate_module_py(pointcloud_to_laserscan
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pointcloud_to_laserscan
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(pointcloud_to_laserscan_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(pointcloud_to_laserscan_generate_messages pointcloud_to_laserscan_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/Velocity_multiplier.msg" NAME_WE)
add_dependencies(pointcloud_to_laserscan_generate_messages_py _pointcloud_to_laserscan_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/pointcloud_to_laserscan/msg/ObstacleProximity.msg" NAME_WE)
add_dependencies(pointcloud_to_laserscan_generate_messages_py _pointcloud_to_laserscan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pointcloud_to_laserscan_genpy)
add_dependencies(pointcloud_to_laserscan_genpy pointcloud_to_laserscan_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pointcloud_to_laserscan_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pointcloud_to_laserscan)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pointcloud_to_laserscan
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(pointcloud_to_laserscan_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pointcloud_to_laserscan)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pointcloud_to_laserscan
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(pointcloud_to_laserscan_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pointcloud_to_laserscan)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pointcloud_to_laserscan\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pointcloud_to_laserscan
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(pointcloud_to_laserscan_generate_messages_py std_msgs_generate_messages_py)
endif()
