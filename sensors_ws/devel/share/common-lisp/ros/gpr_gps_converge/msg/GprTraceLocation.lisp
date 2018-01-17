; Auto-generated. Do not edit!


(cl:in-package gpr_gps_converge-msg)


;//! \htmlinclude GprTraceLocation.msg.html

(cl:defclass <GprTraceLocation> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (CoordinateFormat
    :reader CoordinateFormat
    :initarg :CoordinateFormat
    :type cl:string
    :initform "")
   (Longitude
    :reader Longitude
    :initarg :Longitude
    :type cl:float
    :initform 0.0)
   (Latitude
    :reader Latitude
    :initarg :Latitude
    :type cl:float
    :initform 0.0)
   (Altitude
    :reader Altitude
    :initarg :Altitude
    :type cl:float
    :initform 0.0)
   (latitude_label
    :reader latitude_label
    :initarg :latitude_label
    :type cl:string
    :initform "")
   (longitude_label
    :reader longitude_label
    :initarg :longitude_label
    :type cl:string
    :initform "")
   (UTMZone
    :reader UTMZone
    :initarg :UTMZone
    :type cl:string
    :initform ""))
)

(cl:defclass GprTraceLocation (<GprTraceLocation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GprTraceLocation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GprTraceLocation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gpr_gps_converge-msg:<GprTraceLocation> is deprecated: use gpr_gps_converge-msg:GprTraceLocation instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:stamp-val is deprecated.  Use gpr_gps_converge-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'CoordinateFormat-val :lambda-list '(m))
(cl:defmethod CoordinateFormat-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:CoordinateFormat-val is deprecated.  Use gpr_gps_converge-msg:CoordinateFormat instead.")
  (CoordinateFormat m))

(cl:ensure-generic-function 'Longitude-val :lambda-list '(m))
(cl:defmethod Longitude-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:Longitude-val is deprecated.  Use gpr_gps_converge-msg:Longitude instead.")
  (Longitude m))

(cl:ensure-generic-function 'Latitude-val :lambda-list '(m))
(cl:defmethod Latitude-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:Latitude-val is deprecated.  Use gpr_gps_converge-msg:Latitude instead.")
  (Latitude m))

(cl:ensure-generic-function 'Altitude-val :lambda-list '(m))
(cl:defmethod Altitude-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:Altitude-val is deprecated.  Use gpr_gps_converge-msg:Altitude instead.")
  (Altitude m))

(cl:ensure-generic-function 'latitude_label-val :lambda-list '(m))
(cl:defmethod latitude_label-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:latitude_label-val is deprecated.  Use gpr_gps_converge-msg:latitude_label instead.")
  (latitude_label m))

(cl:ensure-generic-function 'longitude_label-val :lambda-list '(m))
(cl:defmethod longitude_label-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:longitude_label-val is deprecated.  Use gpr_gps_converge-msg:longitude_label instead.")
  (longitude_label m))

(cl:ensure-generic-function 'UTMZone-val :lambda-list '(m))
(cl:defmethod UTMZone-val ((m <GprTraceLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:UTMZone-val is deprecated.  Use gpr_gps_converge-msg:UTMZone instead.")
  (UTMZone m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GprTraceLocation>) ostream)
  "Serializes a message object of type '<GprTraceLocation>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'stamp) (cl:floor (cl:slot-value msg 'stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'CoordinateFormat))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'CoordinateFormat))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'Longitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'Latitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'Altitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'latitude_label))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'latitude_label))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'longitude_label))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'longitude_label))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'UTMZone))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'UTMZone))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GprTraceLocation>) istream)
  "Deserializes a message object of type '<GprTraceLocation>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'CoordinateFormat) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'CoordinateFormat) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Longitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Latitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Altitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'latitude_label) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'latitude_label) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'longitude_label) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'longitude_label) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'UTMZone) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'UTMZone) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GprTraceLocation>)))
  "Returns string type for a message object of type '<GprTraceLocation>"
  "gpr_gps_converge/GprTraceLocation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GprTraceLocation)))
  "Returns string type for a message object of type 'GprTraceLocation"
  "gpr_gps_converge/GprTraceLocation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GprTraceLocation>)))
  "Returns md5sum for a message object of type '<GprTraceLocation>"
  "ad9b5784e3da422663d2055d98f6046f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GprTraceLocation)))
  "Returns md5sum for a message object of type 'GprTraceLocation"
  "ad9b5784e3da422663d2055d98f6046f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GprTraceLocation>)))
  "Returns full string definition for message of type '<GprTraceLocation>"
  (cl:format cl:nil "time stamp~%string CoordinateFormat~%float64 Longitude~%float64 Latitude~%float64 Altitude~%string latitude_label~%string longitude_label~%string UTMZone~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GprTraceLocation)))
  "Returns full string definition for message of type 'GprTraceLocation"
  (cl:format cl:nil "time stamp~%string CoordinateFormat~%float64 Longitude~%float64 Latitude~%float64 Altitude~%string latitude_label~%string longitude_label~%string UTMZone~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GprTraceLocation>))
  (cl:+ 0
     8
     4 (cl:length (cl:slot-value msg 'CoordinateFormat))
     8
     8
     8
     4 (cl:length (cl:slot-value msg 'latitude_label))
     4 (cl:length (cl:slot-value msg 'longitude_label))
     4 (cl:length (cl:slot-value msg 'UTMZone))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GprTraceLocation>))
  "Converts a ROS message object to a list"
  (cl:list 'GprTraceLocation
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':CoordinateFormat (CoordinateFormat msg))
    (cl:cons ':Longitude (Longitude msg))
    (cl:cons ':Latitude (Latitude msg))
    (cl:cons ':Altitude (Altitude msg))
    (cl:cons ':latitude_label (latitude_label msg))
    (cl:cons ':longitude_label (longitude_label msg))
    (cl:cons ':UTMZone (UTMZone msg))
))
