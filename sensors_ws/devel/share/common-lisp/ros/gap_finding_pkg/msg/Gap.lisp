; Auto-generated. Do not edit!


(cl:in-package gap_finding_pkg-msg)


;//! \htmlinclude Gap.msg.html

(cl:defclass <Gap> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gap_width
    :reader gap_width
    :initarg :gap_width
    :type cl:float
    :initform 0.0)
   (dist_right
    :reader dist_right
    :initarg :dist_right
    :type cl:float
    :initform 0.0)
   (dist_left
    :reader dist_left
    :initarg :dist_left
    :type cl:float
    :initform 0.0)
   (angle_right
    :reader angle_right
    :initarg :angle_right
    :type cl:float
    :initform 0.0)
   (angle_left
    :reader angle_left
    :initarg :angle_left
    :type cl:float
    :initform 0.0))
)

(cl:defclass Gap (<Gap>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Gap>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Gap)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gap_finding_pkg-msg:<Gap> is deprecated: use gap_finding_pkg-msg:Gap instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Gap>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:header-val is deprecated.  Use gap_finding_pkg-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gap_width-val :lambda-list '(m))
(cl:defmethod gap_width-val ((m <Gap>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:gap_width-val is deprecated.  Use gap_finding_pkg-msg:gap_width instead.")
  (gap_width m))

(cl:ensure-generic-function 'dist_right-val :lambda-list '(m))
(cl:defmethod dist_right-val ((m <Gap>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:dist_right-val is deprecated.  Use gap_finding_pkg-msg:dist_right instead.")
  (dist_right m))

(cl:ensure-generic-function 'dist_left-val :lambda-list '(m))
(cl:defmethod dist_left-val ((m <Gap>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:dist_left-val is deprecated.  Use gap_finding_pkg-msg:dist_left instead.")
  (dist_left m))

(cl:ensure-generic-function 'angle_right-val :lambda-list '(m))
(cl:defmethod angle_right-val ((m <Gap>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:angle_right-val is deprecated.  Use gap_finding_pkg-msg:angle_right instead.")
  (angle_right m))

(cl:ensure-generic-function 'angle_left-val :lambda-list '(m))
(cl:defmethod angle_left-val ((m <Gap>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:angle_left-val is deprecated.  Use gap_finding_pkg-msg:angle_left instead.")
  (angle_left m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Gap>) ostream)
  "Serializes a message object of type '<Gap>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gap_width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dist_right))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dist_left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_right))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Gap>) istream)
  "Deserializes a message object of type '<Gap>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gap_width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dist_right) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dist_left) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_right) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_left) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Gap>)))
  "Returns string type for a message object of type '<Gap>"
  "gap_finding_pkg/Gap")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Gap)))
  "Returns string type for a message object of type 'Gap"
  "gap_finding_pkg/Gap")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Gap>)))
  "Returns md5sum for a message object of type '<Gap>"
  "79c057cbab3544dbadcc4f7af24d22c1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Gap)))
  "Returns md5sum for a message object of type 'Gap"
  "79c057cbab3544dbadcc4f7af24d22c1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Gap>)))
  "Returns full string definition for message of type '<Gap>"
  (cl:format cl:nil "Header header~%~%float32 gap_width          # the width of the widest gap[m]~%float32 dist_right         # distance to the edge of obstacle on the right[m]~%float32 dist_left          # distance to the edge of obstacle on the left[m]~%float32 angle_right        # right scan angle border [rad]~%float32 angle_left         # left scan angle border [rad]~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Gap)))
  "Returns full string definition for message of type 'Gap"
  (cl:format cl:nil "Header header~%~%float32 gap_width          # the width of the widest gap[m]~%float32 dist_right         # distance to the edge of obstacle on the right[m]~%float32 dist_left          # distance to the edge of obstacle on the left[m]~%float32 angle_right        # right scan angle border [rad]~%float32 angle_left         # left scan angle border [rad]~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Gap>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Gap>))
  "Converts a ROS message object to a list"
  (cl:list 'Gap
    (cl:cons ':header (header msg))
    (cl:cons ':gap_width (gap_width msg))
    (cl:cons ':dist_right (dist_right msg))
    (cl:cons ':dist_left (dist_left msg))
    (cl:cons ':angle_right (angle_right msg))
    (cl:cons ':angle_left (angle_left msg))
))
