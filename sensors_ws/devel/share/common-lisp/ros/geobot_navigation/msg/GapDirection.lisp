; Auto-generated. Do not edit!


(cl:in-package geobot_navigation-msg)


;//! \htmlinclude GapDirection.msg.html

(cl:defclass <GapDirection> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gap_seq
    :reader gap_seq
    :initarg :gap_seq
    :type cl:integer
    :initform 0)
   (sr_heading
    :reader sr_heading
    :initarg :sr_heading
    :type cl:float
    :initform 0.0)
   (sr_diff
    :reader sr_diff
    :initarg :sr_diff
    :type cl:float
    :initform 0.0)
   (sl_heading
    :reader sl_heading
    :initarg :sl_heading
    :type cl:float
    :initform 0.0)
   (sl_diff
    :reader sl_diff
    :initarg :sl_diff
    :type cl:float
    :initform 0.0))
)

(cl:defclass GapDirection (<GapDirection>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GapDirection>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GapDirection)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name geobot_navigation-msg:<GapDirection> is deprecated: use geobot_navigation-msg:GapDirection instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <GapDirection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation-msg:header-val is deprecated.  Use geobot_navigation-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gap_seq-val :lambda-list '(m))
(cl:defmethod gap_seq-val ((m <GapDirection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation-msg:gap_seq-val is deprecated.  Use geobot_navigation-msg:gap_seq instead.")
  (gap_seq m))

(cl:ensure-generic-function 'sr_heading-val :lambda-list '(m))
(cl:defmethod sr_heading-val ((m <GapDirection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation-msg:sr_heading-val is deprecated.  Use geobot_navigation-msg:sr_heading instead.")
  (sr_heading m))

(cl:ensure-generic-function 'sr_diff-val :lambda-list '(m))
(cl:defmethod sr_diff-val ((m <GapDirection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation-msg:sr_diff-val is deprecated.  Use geobot_navigation-msg:sr_diff instead.")
  (sr_diff m))

(cl:ensure-generic-function 'sl_heading-val :lambda-list '(m))
(cl:defmethod sl_heading-val ((m <GapDirection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation-msg:sl_heading-val is deprecated.  Use geobot_navigation-msg:sl_heading instead.")
  (sl_heading m))

(cl:ensure-generic-function 'sl_diff-val :lambda-list '(m))
(cl:defmethod sl_diff-val ((m <GapDirection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation-msg:sl_diff-val is deprecated.  Use geobot_navigation-msg:sl_diff instead.")
  (sl_diff m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GapDirection>) ostream)
  "Serializes a message object of type '<GapDirection>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gap_seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gap_seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gap_seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gap_seq)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sr_heading))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sr_diff))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sl_heading))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'sl_diff))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GapDirection>) istream)
  "Deserializes a message object of type '<GapDirection>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gap_seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'gap_seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'gap_seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'gap_seq)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sr_heading) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sr_diff) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sl_heading) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'sl_diff) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GapDirection>)))
  "Returns string type for a message object of type '<GapDirection>"
  "geobot_navigation/GapDirection")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GapDirection)))
  "Returns string type for a message object of type 'GapDirection"
  "geobot_navigation/GapDirection")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GapDirection>)))
  "Returns md5sum for a message object of type '<GapDirection>"
  "db868e1527d93c1574e7467a1c69f2bc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GapDirection)))
  "Returns md5sum for a message object of type 'GapDirection"
  "db868e1527d93c1574e7467a1c69f2bc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GapDirection>)))
  "Returns full string definition for message of type '<GapDirection>"
  (cl:format cl:nil "Header header~%~%uint32 gap_seq       ~%float32 sr_heading        ~%float32 sr_diff      ~%float32 sl_heading     ~%float32 sl_diff     ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GapDirection)))
  "Returns full string definition for message of type 'GapDirection"
  (cl:format cl:nil "Header header~%~%uint32 gap_seq       ~%float32 sr_heading        ~%float32 sr_diff      ~%float32 sl_heading     ~%float32 sl_diff     ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GapDirection>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GapDirection>))
  "Converts a ROS message object to a list"
  (cl:list 'GapDirection
    (cl:cons ':header (header msg))
    (cl:cons ':gap_seq (gap_seq msg))
    (cl:cons ':sr_heading (sr_heading msg))
    (cl:cons ':sr_diff (sr_diff msg))
    (cl:cons ':sl_heading (sl_heading msg))
    (cl:cons ':sl_diff (sl_diff msg))
))
