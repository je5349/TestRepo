
(cl:in-package :asdf)

(defsystem "geobot_pose_publisher-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GprTraceLocation" :depends-on ("_package_GprTraceLocation"))
    (:file "_package_GprTraceLocation" :depends-on ("_package"))
  ))