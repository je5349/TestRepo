# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "gpr_gps_converge: 2 messages, 0 services")

set(MSG_I_FLAGS "-Igpr_gps_converge:/home/administrator/sensors_ws/src/gpr_gps_converge/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(gpr_gps_converge_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg" NAME_WE)
add_custom_target(_gpr_gps_converge_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gpr_gps_converge" "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg" ""
)

get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg" NAME_WE)
add_custom_target(_gpr_gps_converge_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gpr_gps_converge" "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(gpr_gps_converge
  "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpr_gps_converge
)
_generate_msg_cpp(gpr_gps_converge
  "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpr_gps_converge
)

### Generating Services

### Generating Module File
_generate_module_cpp(gpr_gps_converge
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpr_gps_converge
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(gpr_gps_converge_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(gpr_gps_converge_generate_messages gpr_gps_converge_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg" NAME_WE)
add_dependencies(gpr_gps_converge_generate_messages_cpp _gpr_gps_converge_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg" NAME_WE)
add_dependencies(gpr_gps_converge_generate_messages_cpp _gpr_gps_converge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpr_gps_converge_gencpp)
add_dependencies(gpr_gps_converge_gencpp gpr_gps_converge_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpr_gps_converge_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(gpr_gps_converge
  "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpr_gps_converge
)
_generate_msg_lisp(gpr_gps_converge
  "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpr_gps_converge
)

### Generating Services

### Generating Module File
_generate_module_lisp(gpr_gps_converge
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpr_gps_converge
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(gpr_gps_converge_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(gpr_gps_converge_generate_messages gpr_gps_converge_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg" NAME_WE)
add_dependencies(gpr_gps_converge_generate_messages_lisp _gpr_gps_converge_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg" NAME_WE)
add_dependencies(gpr_gps_converge_generate_messages_lisp _gpr_gps_converge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpr_gps_converge_genlisp)
add_dependencies(gpr_gps_converge_genlisp gpr_gps_converge_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpr_gps_converge_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(gpr_gps_converge
  "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpr_gps_converge
)
_generate_msg_py(gpr_gps_converge
  "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpr_gps_converge
)

### Generating Services

### Generating Module File
_generate_module_py(gpr_gps_converge
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpr_gps_converge
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(gpr_gps_converge_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(gpr_gps_converge_generate_messages gpr_gps_converge_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprConverged.msg" NAME_WE)
add_dependencies(gpr_gps_converge_generate_messages_py _gpr_gps_converge_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/gpr_gps_converge/msg/GprTraceLocation.msg" NAME_WE)
add_dependencies(gpr_gps_converge_generate_messages_py _gpr_gps_converge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gpr_gps_converge_genpy)
add_dependencies(gpr_gps_converge_genpy gpr_gps_converge_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gpr_gps_converge_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpr_gps_converge)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gpr_gps_converge
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(gpr_gps_converge_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpr_gps_converge)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gpr_gps_converge
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(gpr_gps_converge_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpr_gps_converge)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpr_gps_converge\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gpr_gps_converge
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(gpr_gps_converge_generate_messages_py std_msgs_generate_messages_py)
endif()
