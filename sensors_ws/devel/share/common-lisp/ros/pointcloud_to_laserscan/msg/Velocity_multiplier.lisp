; Auto-generated. Do not edit!


(cl:in-package pointcloud_to_laserscan-msg)


;//! \htmlinclude Velocity_multiplier.msg.html

(cl:defclass <Velocity_multiplier> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (ang_right
    :reader ang_right
    :initarg :ang_right
    :type cl:float
    :initform 0.0)
   (ang_left
    :reader ang_left
    :initarg :ang_left
    :type cl:float
    :initform 0.0)
   (lin_forward
    :reader lin_forward
    :initarg :lin_forward
    :type cl:float
    :initform 0.0)
   (lin_backward
    :reader lin_backward
    :initarg :lin_backward
    :type cl:float
    :initform 0.0))
)

(cl:defclass Velocity_multiplier (<Velocity_multiplier>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Velocity_multiplier>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Velocity_multiplier)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pointcloud_to_laserscan-msg:<Velocity_multiplier> is deprecated: use pointcloud_to_laserscan-msg:Velocity_multiplier instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Velocity_multiplier>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:header-val is deprecated.  Use pointcloud_to_laserscan-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'ang_right-val :lambda-list '(m))
(cl:defmethod ang_right-val ((m <Velocity_multiplier>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:ang_right-val is deprecated.  Use pointcloud_to_laserscan-msg:ang_right instead.")
  (ang_right m))

(cl:ensure-generic-function 'ang_left-val :lambda-list '(m))
(cl:defmethod ang_left-val ((m <Velocity_multiplier>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:ang_left-val is deprecated.  Use pointcloud_to_laserscan-msg:ang_left instead.")
  (ang_left m))

(cl:ensure-generic-function 'lin_forward-val :lambda-list '(m))
(cl:defmethod lin_forward-val ((m <Velocity_multiplier>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:lin_forward-val is deprecated.  Use pointcloud_to_laserscan-msg:lin_forward instead.")
  (lin_forward m))

(cl:ensure-generic-function 'lin_backward-val :lambda-list '(m))
(cl:defmethod lin_backward-val ((m <Velocity_multiplier>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:lin_backward-val is deprecated.  Use pointcloud_to_laserscan-msg:lin_backward instead.")
  (lin_backward m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Velocity_multiplier>) ostream)
  "Serializes a message object of type '<Velocity_multiplier>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ang_right))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ang_left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'lin_forward))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'lin_backward))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Velocity_multiplier>) istream)
  "Deserializes a message object of type '<Velocity_multiplier>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ang_right) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ang_left) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lin_forward) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'lin_backward) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Velocity_multiplier>)))
  "Returns string type for a message object of type '<Velocity_multiplier>"
  "pointcloud_to_laserscan/Velocity_multiplier")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Velocity_multiplier)))
  "Returns string type for a message object of type 'Velocity_multiplier"
  "pointcloud_to_laserscan/Velocity_multiplier")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Velocity_multiplier>)))
  "Returns md5sum for a message object of type '<Velocity_multiplier>"
  "e6bee81ca0235061272a09ce6e9fbf49")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Velocity_multiplier)))
  "Returns md5sum for a message object of type 'Velocity_multiplier"
  "e6bee81ca0235061272a09ce6e9fbf49")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Velocity_multiplier>)))
  "Returns full string definition for message of type '<Velocity_multiplier>"
  (cl:format cl:nil "Header header~%~%float32 ang_right         # right angular velocity multiplier [0 to 1]~%float32 ang_left          # left angular velocity multiplier [0 to 1]~%float32 lin_forward        # forward linear velocity multiplier [0 to 1]~%float32 lin_backward         # backward linear velocity multiplier [0 to 1]~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Velocity_multiplier)))
  "Returns full string definition for message of type 'Velocity_multiplier"
  (cl:format cl:nil "Header header~%~%float32 ang_right         # right angular velocity multiplier [0 to 1]~%float32 ang_left          # left angular velocity multiplier [0 to 1]~%float32 lin_forward        # forward linear velocity multiplier [0 to 1]~%float32 lin_backward         # backward linear velocity multiplier [0 to 1]~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Velocity_multiplier>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Velocity_multiplier>))
  "Converts a ROS message object to a list"
  (cl:list 'Velocity_multiplier
    (cl:cons ':header (header msg))
    (cl:cons ':ang_right (ang_right msg))
    (cl:cons ':ang_left (ang_left msg))
    (cl:cons ':lin_forward (lin_forward msg))
    (cl:cons ':lin_backward (lin_backward msg))
))
