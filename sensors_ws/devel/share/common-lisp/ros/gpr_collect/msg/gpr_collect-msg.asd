
(cl:in-package :asdf)

(defsystem "gpr_collect-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GprTrace" :depends-on ("_package_GprTrace"))
    (:file "_package_GprTrace" :depends-on ("_package"))
  ))