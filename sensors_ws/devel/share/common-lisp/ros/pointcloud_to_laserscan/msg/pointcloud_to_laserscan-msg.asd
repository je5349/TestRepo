
(cl:in-package :asdf)

(defsystem "pointcloud_to_laserscan-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Velocity_multiplier" :depends-on ("_package_Velocity_multiplier"))
    (:file "_package_Velocity_multiplier" :depends-on ("_package"))
    (:file "ObstacleProximity" :depends-on ("_package_ObstacleProximity"))
    (:file "_package_ObstacleProximity" :depends-on ("_package"))
  ))