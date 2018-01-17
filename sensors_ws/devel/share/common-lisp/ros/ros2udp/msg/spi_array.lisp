; Auto-generated. Do not edit!


(cl:in-package ros2udp-msg)


;//! \htmlinclude spi_array.msg.html

(cl:defclass <spi_array> (roslisp-msg-protocol:ros-message)
  ((spi_array
    :reader spi_array
    :initarg :spi_array
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 200 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass spi_array (<spi_array>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <spi_array>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'spi_array)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros2udp-msg:<spi_array> is deprecated: use ros2udp-msg:spi_array instead.")))

(cl:ensure-generic-function 'spi_array-val :lambda-list '(m))
(cl:defmethod spi_array-val ((m <spi_array>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros2udp-msg:spi_array-val is deprecated.  Use ros2udp-msg:spi_array instead.")
  (spi_array m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <spi_array>) ostream)
  "Serializes a message object of type '<spi_array>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'spi_array))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <spi_array>) istream)
  "Deserializes a message object of type '<spi_array>"
  (cl:setf (cl:slot-value msg 'spi_array) (cl:make-array 200))
  (cl:let ((vals (cl:slot-value msg 'spi_array)))
    (cl:dotimes (i 200)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<spi_array>)))
  "Returns string type for a message object of type '<spi_array>"
  "ros2udp/spi_array")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'spi_array)))
  "Returns string type for a message object of type 'spi_array"
  "ros2udp/spi_array")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<spi_array>)))
  "Returns md5sum for a message object of type '<spi_array>"
  "a07e4f811e0030cb667022828fa40185")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'spi_array)))
  "Returns md5sum for a message object of type 'spi_array"
  "a07e4f811e0030cb667022828fa40185")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<spi_array>)))
  "Returns full string definition for message of type '<spi_array>"
  (cl:format cl:nil "int16[200] spi_array~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'spi_array)))
  "Returns full string definition for message of type 'spi_array"
  (cl:format cl:nil "int16[200] spi_array~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <spi_array>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'spi_array) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <spi_array>))
  "Converts a ROS message object to a list"
  (cl:list 'spi_array
    (cl:cons ':spi_array (spi_array msg))
))
