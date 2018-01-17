# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "geobot_navigation_rupes: 1 messages, 1 services")

set(MSG_I_FLAGS "-Igeobot_navigation_rupes:/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/indigo/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(geobot_navigation_rupes_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg" NAME_WE)
add_custom_target(_geobot_navigation_rupes_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "geobot_navigation_rupes" "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg" ""
)

get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv" NAME_WE)
add_custom_target(_geobot_navigation_rupes_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "geobot_navigation_rupes" "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(geobot_navigation_rupes
  "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/geobot_navigation_rupes
)

### Generating Services
_generate_srv_cpp(geobot_navigation_rupes
  "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/geobot_navigation_rupes
)

### Generating Module File
_generate_module_cpp(geobot_navigation_rupes
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/geobot_navigation_rupes
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(geobot_navigation_rupes_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(geobot_navigation_rupes_generate_messages geobot_navigation_rupes_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg" NAME_WE)
add_dependencies(geobot_navigation_rupes_generate_messages_cpp _geobot_navigation_rupes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv" NAME_WE)
add_dependencies(geobot_navigation_rupes_generate_messages_cpp _geobot_navigation_rupes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(geobot_navigation_rupes_gencpp)
add_dependencies(geobot_navigation_rupes_gencpp geobot_navigation_rupes_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS geobot_navigation_rupes_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(geobot_navigation_rupes
  "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/geobot_navigation_rupes
)

### Generating Services
_generate_srv_lisp(geobot_navigation_rupes
  "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/geobot_navigation_rupes
)

### Generating Module File
_generate_module_lisp(geobot_navigation_rupes
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/geobot_navigation_rupes
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(geobot_navigation_rupes_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(geobot_navigation_rupes_generate_messages geobot_navigation_rupes_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg" NAME_WE)
add_dependencies(geobot_navigation_rupes_generate_messages_lisp _geobot_navigation_rupes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv" NAME_WE)
add_dependencies(geobot_navigation_rupes_generate_messages_lisp _geobot_navigation_rupes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(geobot_navigation_rupes_genlisp)
add_dependencies(geobot_navigation_rupes_genlisp geobot_navigation_rupes_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS geobot_navigation_rupes_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(geobot_navigation_rupes
  "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/geobot_navigation_rupes
)

### Generating Services
_generate_srv_py(geobot_navigation_rupes
  "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/geobot_navigation_rupes
)

### Generating Module File
_generate_module_py(geobot_navigation_rupes
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/geobot_navigation_rupes
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(geobot_navigation_rupes_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(geobot_navigation_rupes_generate_messages geobot_navigation_rupes_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg/Num.msg" NAME_WE)
add_dependencies(geobot_navigation_rupes_generate_messages_py _geobot_navigation_rupes_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/geobot_navigation_rupes/srv/Path.srv" NAME_WE)
add_dependencies(geobot_navigation_rupes_generate_messages_py _geobot_navigation_rupes_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(geobot_navigation_rupes_genpy)
add_dependencies(geobot_navigation_rupes_genpy geobot_navigation_rupes_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS geobot_navigation_rupes_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/geobot_navigation_rupes)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/geobot_navigation_rupes
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(geobot_navigation_rupes_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(geobot_navigation_rupes_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(geobot_navigation_rupes_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/geobot_navigation_rupes)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/geobot_navigation_rupes
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(geobot_navigation_rupes_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(geobot_navigation_rupes_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(geobot_navigation_rupes_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/geobot_navigation_rupes)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/geobot_navigation_rupes\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/geobot_navigation_rupes
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(geobot_navigation_rupes_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(geobot_navigation_rupes_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(geobot_navigation_rupes_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
