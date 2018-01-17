; Auto-generated. Do not edit!


(cl:in-package gap_finding_pkg-msg)


;//! \htmlinclude GapArray.msg.html

(cl:defclass <GapArray> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gaps
    :reader gaps
    :initarg :gaps
    :type (cl:vector gap_finding_pkg-msg:Gap)
   :initform (cl:make-array 0 :element-type 'gap_finding_pkg-msg:Gap :initial-element (cl:make-instance 'gap_finding_pkg-msg:Gap))))
)

(cl:defclass GapArray (<GapArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GapArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GapArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gap_finding_pkg-msg:<GapArray> is deprecated: use gap_finding_pkg-msg:GapArray instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <GapArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:header-val is deprecated.  Use gap_finding_pkg-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gaps-val :lambda-list '(m))
(cl:defmethod gaps-val ((m <GapArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gap_finding_pkg-msg:gaps-val is deprecated.  Use gap_finding_pkg-msg:gaps instead.")
  (gaps m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GapArray>) ostream)
  "Serializes a message object of type '<GapArray>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'gaps))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'gaps))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GapArray>) istream)
  "Deserializes a message object of type '<GapArray>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'gaps) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'gaps)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'gap_finding_pkg-msg:Gap))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GapArray>)))
  "Returns string type for a message object of type '<GapArray>"
  "gap_finding_pkg/GapArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GapArray)))
  "Returns string type for a message object of type 'GapArray"
  "gap_finding_pkg/GapArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GapArray>)))
  "Returns md5sum for a message object of type '<GapArray>"
  "7d5ee3363f969383412dfa34da32c3c4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GapArray)))
  "Returns md5sum for a message object of type 'GapArray"
  "7d5ee3363f969383412dfa34da32c3c4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GapArray>)))
  "Returns full string definition for message of type '<GapArray>"
  (cl:format cl:nil "Header header~%~%gap_finding_pkg/Gap[] gaps~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: gap_finding_pkg/Gap~%Header header~%~%float32 gap_width          # the width of the widest gap[m]~%float32 dist_right         # distance to the edge of obstacle on the right[m]~%float32 dist_left          # distance to the edge of obstacle on the left[m]~%float32 angle_right        # right scan angle border [rad]~%float32 angle_left         # left scan angle border [rad]~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GapArray)))
  "Returns full string definition for message of type 'GapArray"
  (cl:format cl:nil "Header header~%~%gap_finding_pkg/Gap[] gaps~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: gap_finding_pkg/Gap~%Header header~%~%float32 gap_width          # the width of the widest gap[m]~%float32 dist_right         # distance to the edge of obstacle on the right[m]~%float32 dist_left          # distance to the edge of obstacle on the left[m]~%float32 angle_right        # right scan angle border [rad]~%float32 angle_left         # left scan angle border [rad]~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GapArray>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'gaps) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GapArray>))
  "Converts a ROS message object to a list"
  (cl:list 'GapArray
    (cl:cons ':header (header msg))
    (cl:cons ':gaps (gaps msg))
))
