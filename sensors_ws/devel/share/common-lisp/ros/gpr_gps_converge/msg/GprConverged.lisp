; Auto-generated. Do not edit!


(cl:in-package gpr_gps_converge-msg)


;//! \htmlinclude GprConverged.msg.html

(cl:defclass <GprConverged> (roslisp-msg-protocol:ros-message)
  ((rosTime_
    :reader rosTime_
    :initarg :rosTime_
    :type cl:real
    :initform 0)
   (traceSize_
    :reader traceSize_
    :initarg :traceSize_
    :type cl:integer
    :initform 0)
   (headerSize_
    :reader headerSize_
    :initarg :headerSize_
    :type cl:fixnum
    :initform 0)
   (headerID_
    :reader headerID_
    :initarg :headerID_
    :type cl:string
    :initform "")
   (stampCount_
    :reader stampCount_
    :initarg :stampCount_
    :type cl:integer
    :initform 0)
   (traceNumber_
    :reader traceNumber_
    :initarg :traceNumber_
    :type cl:integer
    :initform 0)
   (odoTick_
    :reader odoTick_
    :initarg :odoTick_
    :type cl:integer
    :initform 0)
   (tracePos_
    :reader tracePos_
    :initarg :tracePos_
    :type cl:float
    :initform 0.0)
   (duration_
    :reader duration_
    :initarg :duration_
    :type cl:float
    :initform 0.0)
   (traceStatusFlag_
    :reader traceStatusFlag_
    :initarg :traceStatusFlag_
    :type cl:integer
    :initform 0)
   (numStacks_
    :reader numStacks_
    :initarg :numStacks_
    :type cl:fixnum
    :initform 0)
   (hardwareFlag_
    :reader hardwareFlag_
    :initarg :hardwareFlag_
    :type cl:fixnum
    :initform 0)
   (traceData_
    :reader traceData_
    :initarg :traceData_
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0))
   (dataSize_
    :reader dataSize_
    :initarg :dataSize_
    :type cl:integer
    :initform 0)
   (sampleInterval_
    :reader sampleInterval_
    :initarg :sampleInterval_
    :type cl:string
    :initform "")
   (frequency_
    :reader frequency_
    :initarg :frequency_
    :type cl:string
    :initform "")
   (stamp
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

(cl:defclass GprConverged (<GprConverged>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GprConverged>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GprConverged)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gpr_gps_converge-msg:<GprConverged> is deprecated: use gpr_gps_converge-msg:GprConverged instead.")))

(cl:ensure-generic-function 'rosTime_-val :lambda-list '(m))
(cl:defmethod rosTime_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:rosTime_-val is deprecated.  Use gpr_gps_converge-msg:rosTime_ instead.")
  (rosTime_ m))

(cl:ensure-generic-function 'traceSize_-val :lambda-list '(m))
(cl:defmethod traceSize_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:traceSize_-val is deprecated.  Use gpr_gps_converge-msg:traceSize_ instead.")
  (traceSize_ m))

(cl:ensure-generic-function 'headerSize_-val :lambda-list '(m))
(cl:defmethod headerSize_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:headerSize_-val is deprecated.  Use gpr_gps_converge-msg:headerSize_ instead.")
  (headerSize_ m))

(cl:ensure-generic-function 'headerID_-val :lambda-list '(m))
(cl:defmethod headerID_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:headerID_-val is deprecated.  Use gpr_gps_converge-msg:headerID_ instead.")
  (headerID_ m))

(cl:ensure-generic-function 'stampCount_-val :lambda-list '(m))
(cl:defmethod stampCount_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:stampCount_-val is deprecated.  Use gpr_gps_converge-msg:stampCount_ instead.")
  (stampCount_ m))

(cl:ensure-generic-function 'traceNumber_-val :lambda-list '(m))
(cl:defmethod traceNumber_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:traceNumber_-val is deprecated.  Use gpr_gps_converge-msg:traceNumber_ instead.")
  (traceNumber_ m))

(cl:ensure-generic-function 'odoTick_-val :lambda-list '(m))
(cl:defmethod odoTick_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:odoTick_-val is deprecated.  Use gpr_gps_converge-msg:odoTick_ instead.")
  (odoTick_ m))

(cl:ensure-generic-function 'tracePos_-val :lambda-list '(m))
(cl:defmethod tracePos_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:tracePos_-val is deprecated.  Use gpr_gps_converge-msg:tracePos_ instead.")
  (tracePos_ m))

(cl:ensure-generic-function 'duration_-val :lambda-list '(m))
(cl:defmethod duration_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:duration_-val is deprecated.  Use gpr_gps_converge-msg:duration_ instead.")
  (duration_ m))

(cl:ensure-generic-function 'traceStatusFlag_-val :lambda-list '(m))
(cl:defmethod traceStatusFlag_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:traceStatusFlag_-val is deprecated.  Use gpr_gps_converge-msg:traceStatusFlag_ instead.")
  (traceStatusFlag_ m))

(cl:ensure-generic-function 'numStacks_-val :lambda-list '(m))
(cl:defmethod numStacks_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:numStacks_-val is deprecated.  Use gpr_gps_converge-msg:numStacks_ instead.")
  (numStacks_ m))

(cl:ensure-generic-function 'hardwareFlag_-val :lambda-list '(m))
(cl:defmethod hardwareFlag_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:hardwareFlag_-val is deprecated.  Use gpr_gps_converge-msg:hardwareFlag_ instead.")
  (hardwareFlag_ m))

(cl:ensure-generic-function 'traceData_-val :lambda-list '(m))
(cl:defmethod traceData_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:traceData_-val is deprecated.  Use gpr_gps_converge-msg:traceData_ instead.")
  (traceData_ m))

(cl:ensure-generic-function 'dataSize_-val :lambda-list '(m))
(cl:defmethod dataSize_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:dataSize_-val is deprecated.  Use gpr_gps_converge-msg:dataSize_ instead.")
  (dataSize_ m))

(cl:ensure-generic-function 'sampleInterval_-val :lambda-list '(m))
(cl:defmethod sampleInterval_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:sampleInterval_-val is deprecated.  Use gpr_gps_converge-msg:sampleInterval_ instead.")
  (sampleInterval_ m))

(cl:ensure-generic-function 'frequency_-val :lambda-list '(m))
(cl:defmethod frequency_-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:frequency_-val is deprecated.  Use gpr_gps_converge-msg:frequency_ instead.")
  (frequency_ m))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:stamp-val is deprecated.  Use gpr_gps_converge-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'CoordinateFormat-val :lambda-list '(m))
(cl:defmethod CoordinateFormat-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:CoordinateFormat-val is deprecated.  Use gpr_gps_converge-msg:CoordinateFormat instead.")
  (CoordinateFormat m))

(cl:ensure-generic-function 'Longitude-val :lambda-list '(m))
(cl:defmethod Longitude-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:Longitude-val is deprecated.  Use gpr_gps_converge-msg:Longitude instead.")
  (Longitude m))

(cl:ensure-generic-function 'Latitude-val :lambda-list '(m))
(cl:defmethod Latitude-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:Latitude-val is deprecated.  Use gpr_gps_converge-msg:Latitude instead.")
  (Latitude m))

(cl:ensure-generic-function 'Altitude-val :lambda-list '(m))
(cl:defmethod Altitude-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:Altitude-val is deprecated.  Use gpr_gps_converge-msg:Altitude instead.")
  (Altitude m))

(cl:ensure-generic-function 'latitude_label-val :lambda-list '(m))
(cl:defmethod latitude_label-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:latitude_label-val is deprecated.  Use gpr_gps_converge-msg:latitude_label instead.")
  (latitude_label m))

(cl:ensure-generic-function 'longitude_label-val :lambda-list '(m))
(cl:defmethod longitude_label-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:longitude_label-val is deprecated.  Use gpr_gps_converge-msg:longitude_label instead.")
  (longitude_label m))

(cl:ensure-generic-function 'UTMZone-val :lambda-list '(m))
(cl:defmethod UTMZone-val ((m <GprConverged>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gpr_gps_converge-msg:UTMZone-val is deprecated.  Use gpr_gps_converge-msg:UTMZone instead.")
  (UTMZone m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GprConverged>) ostream)
  "Serializes a message object of type '<GprConverged>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'rosTime_)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'rosTime_) (cl:floor (cl:slot-value msg 'rosTime_)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let* ((signed (cl:slot-value msg 'traceSize_)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'headerSize_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'headerSize_)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'headerID_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'headerID_))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stampCount_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'stampCount_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'stampCount_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'stampCount_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traceNumber_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traceNumber_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traceNumber_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traceNumber_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'odoTick_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'odoTick_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'odoTick_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'odoTick_)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'tracePos_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'duration_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traceStatusFlag_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traceStatusFlag_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traceStatusFlag_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traceStatusFlag_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'numStacks_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'numStacks_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hardwareFlag_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'hardwareFlag_)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'traceData_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'traceData_))
  (cl:let* ((signed (cl:slot-value msg 'dataSize_)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sampleInterval_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sampleInterval_))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'frequency_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'frequency_))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GprConverged>) istream)
  "Deserializes a message object of type '<GprConverged>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rosTime_) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'traceSize_) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'headerSize_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'headerSize_)) (cl:read-byte istream))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'headerID_) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'headerID_) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'stampCount_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'stampCount_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'stampCount_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'stampCount_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traceNumber_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traceNumber_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traceNumber_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traceNumber_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'odoTick_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'odoTick_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'odoTick_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'odoTick_)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tracePos_) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'duration_) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traceStatusFlag_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traceStatusFlag_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traceStatusFlag_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traceStatusFlag_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'numStacks_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'numStacks_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'hardwareFlag_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'hardwareFlag_)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'traceData_) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'traceData_)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536)))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'dataSize_) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sampleInterval_) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sampleInterval_) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frequency_) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'frequency_) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GprConverged>)))
  "Returns string type for a message object of type '<GprConverged>"
  "gpr_gps_converge/GprConverged")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GprConverged)))
  "Returns string type for a message object of type 'GprConverged"
  "gpr_gps_converge/GprConverged")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GprConverged>)))
  "Returns md5sum for a message object of type '<GprConverged>"
  "faaa83bf44fd3deeece9389459e44003")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GprConverged)))
  "Returns md5sum for a message object of type 'GprConverged"
  "faaa83bf44fd3deeece9389459e44003")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GprConverged>)))
  "Returns full string definition for message of type '<GprConverged>"
  (cl:format cl:nil "time rosTime_~%int64 traceSize_~%uint16 headerSize_~%string headerID_~%uint32 stampCount_~%uint32 traceNumber_~%uint32 odoTick_~%float64 tracePos_~%float64 duration_~%uint32 traceStatusFlag_~%uint16 numStacks_~%uint16 hardwareFlag_~%int16[] traceData_~%int32 dataSize_~%string sampleInterval_~%string frequency_~%time stamp~%string CoordinateFormat~%float64 Longitude~%float64 Latitude~%float64 Altitude~%string latitude_label~%string longitude_label~%string UTMZone~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GprConverged)))
  "Returns full string definition for message of type 'GprConverged"
  (cl:format cl:nil "time rosTime_~%int64 traceSize_~%uint16 headerSize_~%string headerID_~%uint32 stampCount_~%uint32 traceNumber_~%uint32 odoTick_~%float64 tracePos_~%float64 duration_~%uint32 traceStatusFlag_~%uint16 numStacks_~%uint16 hardwareFlag_~%int16[] traceData_~%int32 dataSize_~%string sampleInterval_~%string frequency_~%time stamp~%string CoordinateFormat~%float64 Longitude~%float64 Latitude~%float64 Altitude~%string latitude_label~%string longitude_label~%string UTMZone~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GprConverged>))
  (cl:+ 0
     8
     8
     2
     4 (cl:length (cl:slot-value msg 'headerID_))
     4
     4
     4
     8
     8
     4
     2
     2
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'traceData_) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     4
     4 (cl:length (cl:slot-value msg 'sampleInterval_))
     4 (cl:length (cl:slot-value msg 'frequency_))
     8
     4 (cl:length (cl:slot-value msg 'CoordinateFormat))
     8
     8
     8
     4 (cl:length (cl:slot-value msg 'latitude_label))
     4 (cl:length (cl:slot-value msg 'longitude_label))
     4 (cl:length (cl:slot-value msg 'UTMZone))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GprConverged>))
  "Converts a ROS message object to a list"
  (cl:list 'GprConverged
    (cl:cons ':rosTime_ (rosTime_ msg))
    (cl:cons ':traceSize_ (traceSize_ msg))
    (cl:cons ':headerSize_ (headerSize_ msg))
    (cl:cons ':headerID_ (headerID_ msg))
    (cl:cons ':stampCount_ (stampCount_ msg))
    (cl:cons ':traceNumber_ (traceNumber_ msg))
    (cl:cons ':odoTick_ (odoTick_ msg))
    (cl:cons ':tracePos_ (tracePos_ msg))
    (cl:cons ':duration_ (duration_ msg))
    (cl:cons ':traceStatusFlag_ (traceStatusFlag_ msg))
    (cl:cons ':numStacks_ (numStacks_ msg))
    (cl:cons ':hardwareFlag_ (hardwareFlag_ msg))
    (cl:cons ':traceData_ (traceData_ msg))
    (cl:cons ':dataSize_ (dataSize_ msg))
    (cl:cons ':sampleInterval_ (sampleInterval_ msg))
    (cl:cons ':frequency_ (frequency_ msg))
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':CoordinateFormat (CoordinateFormat msg))
    (cl:cons ':Longitude (Longitude msg))
    (cl:cons ':Latitude (Latitude msg))
    (cl:cons ':Altitude (Altitude msg))
    (cl:cons ':latitude_label (latitude_label msg))
    (cl:cons ':longitude_label (longitude_label msg))
    (cl:cons ':UTMZone (UTMZone msg))
))
