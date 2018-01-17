; Auto-generated. Do not edit!


(cl:in-package geobot_navigation-srv)


;//! \htmlinclude SetGoal-request.msg.html

(cl:defclass <SetGoal-request> (roslisp-msg-protocol:ros-message)
  ((goal
    :reader goal
    :initarg :goal
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped)))
)

(cl:defclass SetGoal-request (<SetGoal-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetGoal-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetGoal-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name geobot_navigation-srv:<SetGoal-request> is deprecated: use geobot_navigation-srv:SetGoal-request instead.")))

(cl:ensure-generic-function 'goal-val :lambda-list '(m))
(cl:defmethod goal-val ((m <SetGoal-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation-srv:goal-val is deprecated.  Use geobot_navigation-srv:goal instead.")
  (goal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetGoal-request>) ostream)
  "Serializes a message object of type '<SetGoal-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetGoal-request>) istream)
  "Deserializes a message object of type '<SetGoal-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetGoal-request>)))
  "Returns string type for a service object of type '<SetGoal-request>"
  "geobot_navigation/SetGoalRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGoal-request)))
  "Returns string type for a service object of type 'SetGoal-request"
  "geobot_navigation/SetGoalRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetGoal-request>)))
  "Returns md5sum for a message object of type '<SetGoal-request>"
  "85ae384b155cfbcdf597bf321f1d0169")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetGoal-request)))
  "Returns md5sum for a message object of type 'SetGoal-request"
  "85ae384b155cfbcdf597bf321f1d0169")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetGoal-request>)))
  "Returns full string definition for message of type '<SetGoal-request>"
  (cl:format cl:nil "geometry_msgs/PoseStamped goal~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetGoal-request)))
  "Returns full string definition for message of type 'SetGoal-request"
  (cl:format cl:nil "geometry_msgs/PoseStamped goal~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetGoal-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetGoal-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetGoal-request
    (cl:cons ':goal (goal msg))
))
;//! \htmlinclude SetGoal-response.msg.html

(cl:defclass <SetGoal-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SetGoal-response (<SetGoal-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetGoal-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetGoal-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name geobot_navigation-srv:<SetGoal-response> is deprecated: use geobot_navigation-srv:SetGoal-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetGoal-response>) ostream)
  "Serializes a message object of type '<SetGoal-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetGoal-response>) istream)
  "Deserializes a message object of type '<SetGoal-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetGoal-response>)))
  "Returns string type for a service object of type '<SetGoal-response>"
  "geobot_navigation/SetGoalResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGoal-response)))
  "Returns string type for a service object of type 'SetGoal-response"
  "geobot_navigation/SetGoalResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetGoal-response>)))
  "Returns md5sum for a message object of type '<SetGoal-response>"
  "85ae384b155cfbcdf597bf321f1d0169")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetGoal-response)))
  "Returns md5sum for a message object of type 'SetGoal-response"
  "85ae384b155cfbcdf597bf321f1d0169")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetGoal-response>)))
  "Returns full string definition for message of type '<SetGoal-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetGoal-response)))
  "Returns full string definition for message of type 'SetGoal-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetGoal-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetGoal-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetGoal-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetGoal)))
  'SetGoal-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetGoal)))
  'SetGoal-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetGoal)))
  "Returns string type for a service object of type '<SetGoal>"
  "geobot_navigation/SetGoal")