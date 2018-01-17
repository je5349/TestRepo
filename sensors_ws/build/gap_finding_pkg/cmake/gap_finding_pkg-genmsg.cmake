# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "gap_finding_pkg: 2 messages, 0 services")

set(MSG_I_FLAGS "-Igap_finding_pkg:/home/administrator/sensors_ws/src/gap_finding_pkg/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(gap_finding_pkg_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg" NAME_WE)
add_custom_target(_gap_finding_pkg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gap_finding_pkg" "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg" NAME_WE)
add_custom_target(_gap_finding_pkg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "gap_finding_pkg" "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg" "std_msgs/Header:gap_finding_pkg/Gap"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(gap_finding_pkg
  "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gap_finding_pkg
)
_generate_msg_cpp(gap_finding_pkg
  "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gap_finding_pkg
)

### Generating Services

### Generating Module File
_generate_module_cpp(gap_finding_pkg
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gap_finding_pkg
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(gap_finding_pkg_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(gap_finding_pkg_generate_messages gap_finding_pkg_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg" NAME_WE)
add_dependencies(gap_finding_pkg_generate_messages_cpp _gap_finding_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg" NAME_WE)
add_dependencies(gap_finding_pkg_generate_messages_cpp _gap_finding_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gap_finding_pkg_gencpp)
add_dependencies(gap_finding_pkg_gencpp gap_finding_pkg_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gap_finding_pkg_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(gap_finding_pkg
  "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gap_finding_pkg
)
_generate_msg_lisp(gap_finding_pkg
  "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gap_finding_pkg
)

### Generating Services

### Generating Module File
_generate_module_lisp(gap_finding_pkg
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gap_finding_pkg
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(gap_finding_pkg_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(gap_finding_pkg_generate_messages gap_finding_pkg_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg" NAME_WE)
add_dependencies(gap_finding_pkg_generate_messages_lisp _gap_finding_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg" NAME_WE)
add_dependencies(gap_finding_pkg_generate_messages_lisp _gap_finding_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gap_finding_pkg_genlisp)
add_dependencies(gap_finding_pkg_genlisp gap_finding_pkg_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gap_finding_pkg_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(gap_finding_pkg
  "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gap_finding_pkg
)
_generate_msg_py(gap_finding_pkg
  "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gap_finding_pkg
)

### Generating Services

### Generating Module File
_generate_module_py(gap_finding_pkg
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gap_finding_pkg
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(gap_finding_pkg_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(gap_finding_pkg_generate_messages gap_finding_pkg_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/Gap.msg" NAME_WE)
add_dependencies(gap_finding_pkg_generate_messages_py _gap_finding_pkg_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/administrator/sensors_ws/src/gap_finding_pkg/msg/GapArray.msg" NAME_WE)
add_dependencies(gap_finding_pkg_generate_messages_py _gap_finding_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(gap_finding_pkg_genpy)
add_dependencies(gap_finding_pkg_genpy gap_finding_pkg_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS gap_finding_pkg_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gap_finding_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/gap_finding_pkg
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(gap_finding_pkg_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gap_finding_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/gap_finding_pkg
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(gap_finding_pkg_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gap_finding_pkg)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gap_finding_pkg\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/gap_finding_pkg
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(gap_finding_pkg_generate_messages_py std_msgs_generate_messages_py)
endif()
