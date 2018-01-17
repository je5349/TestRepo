
(cl:in-package :asdf)

(defsystem "os5000s_compass-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "compass_heading" :depends-on ("_package_compass_heading"))
    (:file "_package_compass_heading" :depends-on ("_package"))
  ))