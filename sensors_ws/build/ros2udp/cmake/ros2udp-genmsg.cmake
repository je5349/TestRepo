# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ros2udp: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iros2udp:/home/administrator/sensors_ws/src/ros2udp/msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ros2udp_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg" NAME_WE)
add_custom_target(_ros2udp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros2udp" "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg" ""
)

get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg" NAME_WE)
add_custom_target(_ros2udp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros2udp" "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ros2udp
  "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros2udp
)
_generate_msg_cpp(ros2udp
  "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros2udp
)

### Generating Services

### Generating Module File
_generate_module_cpp(ros2udp
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros2udp
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ros2udp_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ros2udp_generate_messages ros2udp_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg" NAME_WE)
add_dependencies(ros2udp_generate_messages_cpp _ros2udp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg" NAME_WE)
add_dependencies(ros2udp_generate_messages_cpp _ros2udp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros2udp_gencpp)
add_dependencies(ros2udp_gencpp ros2udp_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros2udp_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ros2udp
  "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros2udp
)
_generate_msg_lisp(ros2udp
  "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros2udp
)

### Generating Services

### Generating Module File
_generate_module_lisp(ros2udp
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros2udp
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ros2udp_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ros2udp_generate_messages ros2udp_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg" NAME_WE)
add_dependencies(ros2udp_generate_messages_lisp _ros2udp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg" NAME_WE)
add_dependencies(ros2udp_generate_messages_lisp _ros2udp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros2udp_genlisp)
add_dependencies(ros2udp_genlisp ros2udp_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros2udp_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ros2udp
  "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros2udp
)
_generate_msg_py(ros2udp
  "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros2udp
)

### Generating Services

### Generating Module File
_generate_module_py(ros2udp
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros2udp
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ros2udp_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ros2udp_generate_messages ros2udp_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/GprConverged.msg" NAME_WE)
add_dependencies(ros2udp_generate_messages_py _ros2udp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/ros2udp/msg/spi_array.msg" NAME_WE)
add_dependencies(ros2udp_generate_messages_py _ros2udp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros2udp_genpy)
add_dependencies(ros2udp_genpy ros2udp_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros2udp_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros2udp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros2udp
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(ros2udp_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(ros2udp_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros2udp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros2udp
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(ros2udp_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(ros2udp_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros2udp)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros2udp\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros2udp
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(ros2udp_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(ros2udp_generate_messages_py std_msgs_generate_messages_py)
endif()
