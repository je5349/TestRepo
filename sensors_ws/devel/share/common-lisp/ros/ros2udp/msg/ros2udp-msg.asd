
(cl:in-package :asdf)

(defsystem "ros2udp-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GprConverged" :depends-on ("_package_GprConverged"))
    (:file "_package_GprConverged" :depends-on ("_package"))
    (:file "GprTrace" :depends-on ("_package_GprTrace"))
    (:file "_package_GprTrace" :depends-on ("_package"))
    (:file "spi_array" :depends-on ("_package_spi_array"))
    (:file "_package_spi_array" :depends-on ("_package"))
  ))