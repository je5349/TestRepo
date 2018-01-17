; Auto-generated. Do not edit!


(cl:in-package pointcloud_to_laserscan-msg)


;//! \htmlinclude ObstacleProximity.msg.html

(cl:defclass <ObstacleProximity> (roslisp-msg-protocol:ros-message)
  ((shortest_distance_to_obstacle_LS
    :reader shortest_distance_to_obstacle_LS
    :initarg :shortest_distance_to_obstacle_LS
    :type cl:float
    :initform 0.0)
   (shortest_distance_to_obstacle_RS
    :reader shortest_distance_to_obstacle_RS
    :initarg :shortest_distance_to_obstacle_RS
    :type cl:float
    :initform 0.0)
   (shortest_distance_to_obstacle_FT
    :reader shortest_distance_to_obstacle_FT
    :initarg :shortest_distance_to_obstacle_FT
    :type cl:float
    :initform 0.0)
   (shortest_distance_to_obstacle_BK
    :reader shortest_distance_to_obstacle_BK
    :initarg :shortest_distance_to_obstacle_BK
    :type cl:float
    :initform 0.0)
   (left_side_blocked
    :reader left_side_blocked
    :initarg :left_side_blocked
    :type cl:fixnum
    :initform 0)
   (right_side_blocked
    :reader right_side_blocked
    :initarg :right_side_blocked
    :type cl:fixnum
    :initform 0)
   (front_side_blocked
    :reader front_side_blocked
    :initarg :front_side_blocked
    :type cl:fixnum
    :initform 0))
)

(cl:defclass ObstacleProximity (<ObstacleProximity>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObstacleProximity>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObstacleProximity)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pointcloud_to_laserscan-msg:<ObstacleProximity> is deprecated: use pointcloud_to_laserscan-msg:ObstacleProximity instead.")))

(cl:ensure-generic-function 'shortest_distance_to_obstacle_LS-val :lambda-list '(m))
(cl:defmethod shortest_distance_to_obstacle_LS-val ((m <ObstacleProximity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_LS-val is deprecated.  Use pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_LS instead.")
  (shortest_distance_to_obstacle_LS m))

(cl:ensure-generic-function 'shortest_distance_to_obstacle_RS-val :lambda-list '(m))
(cl:defmethod shortest_distance_to_obstacle_RS-val ((m <ObstacleProximity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_RS-val is deprecated.  Use pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_RS instead.")
  (shortest_distance_to_obstacle_RS m))

(cl:ensure-generic-function 'shortest_distance_to_obstacle_FT-val :lambda-list '(m))
(cl:defmethod shortest_distance_to_obstacle_FT-val ((m <ObstacleProximity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_FT-val is deprecated.  Use pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_FT instead.")
  (shortest_distance_to_obstacle_FT m))

(cl:ensure-generic-function 'shortest_distance_to_obstacle_BK-val :lambda-list '(m))
(cl:defmethod shortest_distance_to_obstacle_BK-val ((m <ObstacleProximity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_BK-val is deprecated.  Use pointcloud_to_laserscan-msg:shortest_distance_to_obstacle_BK instead.")
  (shortest_distance_to_obstacle_BK m))

(cl:ensure-generic-function 'left_side_blocked-val :lambda-list '(m))
(cl:defmethod left_side_blocked-val ((m <ObstacleProximity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:left_side_blocked-val is deprecated.  Use pointcloud_to_laserscan-msg:left_side_blocked instead.")
  (left_side_blocked m))

(cl:ensure-generic-function 'right_side_blocked-val :lambda-list '(m))
(cl:defmethod right_side_blocked-val ((m <ObstacleProximity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:right_side_blocked-val is deprecated.  Use pointcloud_to_laserscan-msg:right_side_blocked instead.")
  (right_side_blocked m))

(cl:ensure-generic-function 'front_side_blocked-val :lambda-list '(m))
(cl:defmethod front_side_blocked-val ((m <ObstacleProximity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pointcloud_to_laserscan-msg:front_side_blocked-val is deprecated.  Use pointcloud_to_laserscan-msg:front_side_blocked instead.")
  (front_side_blocked m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObstacleProximity>) ostream)
  "Serializes a message object of type '<ObstacleProximity>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'shortest_distance_to_obstacle_LS))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'shortest_distance_to_obstacle_RS))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'shortest_distance_to_obstacle_FT))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'shortest_distance_to_obstacle_BK))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'left_side_blocked)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'right_side_blocked)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'front_side_blocked)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObstacleProximity>) istream)
  "Deserializes a message object of type '<ObstacleProximity>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'shortest_distance_to_obstacle_LS) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'shortest_distance_to_obstacle_RS) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'shortest_distance_to_obstacle_FT) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'shortest_distance_to_obstacle_BK) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'left_side_blocked) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'right_side_blocked) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'front_side_blocked) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObstacleProximity>)))
  "Returns string type for a message object of type '<ObstacleProximity>"
  "pointcloud_to_laserscan/ObstacleProximity")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObstacleProximity)))
  "Returns string type for a message object of type 'ObstacleProximity"
  "pointcloud_to_laserscan/ObstacleProximity")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObstacleProximity>)))
  "Returns md5sum for a message object of type '<ObstacleProximity>"
  "387ca4833459998b5938e815fe525f5c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObstacleProximity)))
  "Returns md5sum for a message object of type 'ObstacleProximity"
  "387ca4833459998b5938e815fe525f5c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObstacleProximity>)))
  "Returns full string definition for message of type '<ObstacleProximity>"
  (cl:format cl:nil "float32 shortest_distance_to_obstacle_LS~%float32 shortest_distance_to_obstacle_RS~%float32 shortest_distance_to_obstacle_FT~%float32 shortest_distance_to_obstacle_BK~%int8 left_side_blocked~%int8 right_side_blocked~%int8 front_side_blocked~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObstacleProximity)))
  "Returns full string definition for message of type 'ObstacleProximity"
  (cl:format cl:nil "float32 shortest_distance_to_obstacle_LS~%float32 shortest_distance_to_obstacle_RS~%float32 shortest_distance_to_obstacle_FT~%float32 shortest_distance_to_obstacle_BK~%int8 left_side_blocked~%int8 right_side_blocked~%int8 front_side_blocked~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObstacleProximity>))
  (cl:+ 0
     4
     4
     4
     4
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObstacleProximity>))
  "Converts a ROS message object to a list"
  (cl:list 'ObstacleProximity
    (cl:cons ':shortest_distance_to_obstacle_LS (shortest_distance_to_obstacle_LS msg))
    (cl:cons ':shortest_distance_to_obstacle_RS (shortest_distance_to_obstacle_RS msg))
    (cl:cons ':shortest_distance_to_obstacle_FT (shortest_distance_to_obstacle_FT msg))
    (cl:cons ':shortest_distance_to_obstacle_BK (shortest_distance_to_obstacle_BK msg))
    (cl:cons ':left_side_blocked (left_side_blocked msg))
    (cl:cons ':right_side_blocked (right_side_blocked msg))
    (cl:cons ':front_side_blocked (front_side_blocked msg))
))
