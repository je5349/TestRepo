# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "os5000s_compass: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ios5000s_compass:/home/administrator/sensors_ws/src/os5000s_compass/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(os5000s_compass_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg" NAME_WE)
add_custom_target(_os5000s_compass_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "os5000s_compass" "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg" "std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(os5000s_compass
  "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/os5000s_compass
)

### Generating Services

### Generating Module File
_generate_module_cpp(os5000s_compass
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/os5000s_compass
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(os5000s_compass_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(os5000s_compass_generate_messages os5000s_compass_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg" NAME_WE)
add_dependencies(os5000s_compass_generate_messages_cpp _os5000s_compass_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(os5000s_compass_gencpp)
add_dependencies(os5000s_compass_gencpp os5000s_compass_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS os5000s_compass_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(os5000s_compass
  "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/os5000s_compass
)

### Generating Services

### Generating Module File
_generate_module_lisp(os5000s_compass
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/os5000s_compass
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(os5000s_compass_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(os5000s_compass_generate_messages os5000s_compass_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg" NAME_WE)
add_dependencies(os5000s_compass_generate_messages_lisp _os5000s_compass_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(os5000s_compass_genlisp)
add_dependencies(os5000s_compass_genlisp os5000s_compass_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS os5000s_compass_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(os5000s_compass
  "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/os5000s_compass
)

### Generating Services

### Generating Module File
_generate_module_py(os5000s_compass
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/os5000s_compass
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(os5000s_compass_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(os5000s_compass_generate_messages os5000s_compass_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/os5000s_compass/msg/compass_heading.msg" NAME_WE)
add_dependencies(os5000s_compass_generate_messages_py _os5000s_compass_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(os5000s_compass_genpy)
add_dependencies(os5000s_compass_genpy os5000s_compass_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS os5000s_compass_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/os5000s_compass)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/os5000s_compass
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(os5000s_compass_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/os5000s_compass)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/os5000s_compass
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(os5000s_compass_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/os5000s_compass)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/os5000s_compass\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/os5000s_compass
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(os5000s_compass_generate_messages_py std_msgs_generate_messages_py)
endif()
