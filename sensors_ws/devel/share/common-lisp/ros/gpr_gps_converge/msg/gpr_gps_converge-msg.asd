
(cl:in-package :asdf)

(defsystem "gpr_gps_converge-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GprConverged" :depends-on ("_package_GprConverged"))
    (:file "_package_GprConverged" :depends-on ("_package"))
    (:file "GprTraceLocation" :depends-on ("_package_GprTraceLocation"))
    (:file "_package_GprTraceLocation" :depends-on ("_package"))
  ))