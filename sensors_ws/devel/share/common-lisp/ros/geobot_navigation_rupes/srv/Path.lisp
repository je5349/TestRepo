; Auto-generated. Do not edit!


(cl:in-package geobot_navigation_rupes-srv)


;//! \htmlinclude Path-request.msg.html

(cl:defclass <Path-request> (roslisp-msg-protocol:ros-message)
  ((a
    :reader a
    :initarg :a
    :type cl:float
    :initform 0.0)
   (b
    :reader b
    :initarg :b
    :type cl:float
    :initform 0.0))
)

(cl:defclass Path-request (<Path-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Path-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Path-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name geobot_navigation_rupes-srv:<Path-request> is deprecated: use geobot_navigation_rupes-srv:Path-request instead.")))

(cl:ensure-generic-function 'a-val :lambda-list '(m))
(cl:defmethod a-val ((m <Path-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation_rupes-srv:a-val is deprecated.  Use geobot_navigation_rupes-srv:a instead.")
  (a m))

(cl:ensure-generic-function 'b-val :lambda-list '(m))
(cl:defmethod b-val ((m <Path-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation_rupes-srv:b-val is deprecated.  Use geobot_navigation_rupes-srv:b instead.")
  (b m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Path-request>) ostream)
  "Serializes a message object of type '<Path-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'a))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'b))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Path-request>) istream)
  "Deserializes a message object of type '<Path-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'a) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'b) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Path-request>)))
  "Returns string type for a service object of type '<Path-request>"
  "geobot_navigation_rupes/PathRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Path-request)))
  "Returns string type for a service object of type 'Path-request"
  "geobot_navigation_rupes/PathRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Path-request>)))
  "Returns md5sum for a message object of type '<Path-request>"
  "f305bdd89c3cf25126ae31f8077dfa1b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Path-request)))
  "Returns md5sum for a message object of type 'Path-request"
  "f305bdd89c3cf25126ae31f8077dfa1b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Path-request>)))
  "Returns full string definition for message of type '<Path-request>"
  (cl:format cl:nil "float32 a~%float32 b~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Path-request)))
  "Returns full string definition for message of type 'Path-request"
  (cl:format cl:nil "float32 a~%float32 b~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Path-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Path-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Path-request
    (cl:cons ':a (a msg))
    (cl:cons ':b (b msg))
))
;//! \htmlinclude Path-response.msg.html

(cl:defclass <Path-response> (roslisp-msg-protocol:ros-message)
  ((path1
    :reader path1
    :initarg :path1
    :type cl:float
    :initform 0.0)
   (path2
    :reader path2
    :initarg :path2
    :type cl:float
    :initform 0.0))
)

(cl:defclass Path-response (<Path-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Path-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Path-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name geobot_navigation_rupes-srv:<Path-response> is deprecated: use geobot_navigation_rupes-srv:Path-response instead.")))

(cl:ensure-generic-function 'path1-val :lambda-list '(m))
(cl:defmethod path1-val ((m <Path-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation_rupes-srv:path1-val is deprecated.  Use geobot_navigation_rupes-srv:path1 instead.")
  (path1 m))

(cl:ensure-generic-function 'path2-val :lambda-list '(m))
(cl:defmethod path2-val ((m <Path-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader geobot_navigation_rupes-srv:path2-val is deprecated.  Use geobot_navigation_rupes-srv:path2 instead.")
  (path2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Path-response>) ostream)
  "Serializes a message object of type '<Path-response>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'path1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'path2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Path-response>) istream)
  "Deserializes a message object of type '<Path-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'path1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'path2) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Path-response>)))
  "Returns string type for a service object of type '<Path-response>"
  "geobot_navigation_rupes/PathResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Path-response)))
  "Returns string type for a service object of type 'Path-response"
  "geobot_navigation_rupes/PathResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Path-response>)))
  "Returns md5sum for a message object of type '<Path-response>"
  "f305bdd89c3cf25126ae31f8077dfa1b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Path-response)))
  "Returns md5sum for a message object of type 'Path-response"
  "f305bdd89c3cf25126ae31f8077dfa1b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Path-response>)))
  "Returns full string definition for message of type '<Path-response>"
  (cl:format cl:nil "float32 path1~%float32 path2~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Path-response)))
  "Returns full string definition for message of type 'Path-response"
  (cl:format cl:nil "float32 path1~%float32 path2~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Path-response>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Path-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Path-response
    (cl:cons ':path1 (path1 msg))
    (cl:cons ':path2 (path2 msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Path)))
  'Path-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Path)))
  'Path-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Path)))
  "Returns string type for a service object of type '<Path>"
  "geobot_navigation_rupes/Path")