#include <ros/ros.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/Odometry.h>

using namespace std;


class ModifyPose
{
public:
  ModifyPose();
  void SlamPoseReceived(const geometry_msgs::PoseWithCovarianceStamped& pose_in);
protected:
  ros::Subscriber poseSubscriber_;
  ros::Publisher posePublisher_;
  ros::NodeHandle nh;
};

ModifyPose::ModifyPose()
{
  // nh.subscribe(topic_name,queue_size, pointer_to_callback_function);
  poseSubscriber_ = nh.subscribe("poseupdate",1000, &ModifyPose::SlamPoseReceived,this);
  posePublisher_ = nh.advertise<nav_msgs::Odometry>("converted_poseupdate", 20);
}

// callback function to receive slam_pose data
void ModifyPose::SlamPoseReceived(const geometry_msgs::PoseWithCovarianceStamped& pose_in)
{
  // processing the clam pose recieved
  //float scale_var = 0.000001;
  nav_msgs::Odometry pose_out;

  // populating the message
  pose_out.header = pose_in.header;
  pose_out.header.frame_id = "odom"; // originally not included edit1
  pose_out.child_frame_id = "base_link";
  pose_out.pose = pose_in.pose;

  
  // try to further reduce the variance corresponding to yaw
  //index = {0 ,7, 14, 21, 28, 35}; // corresponding diagonals

  for(int i=0;i<pose_in.pose.covariance.size();i++)
  {
    if(i%7 == 0)
    {
      pose_out.pose.covariance[i] = pose_in.pose.covariance[i]; // keep others the same
    }
    else
    {
      pose_out.pose.covariance[i] = 0.0; // zero out non diagonals
    }

    if(i==35)
    {
      pose_out.pose.covariance[i] = pose_in.pose.covariance[i] * 0.0000001; // increase rotation accurracy
    }
  }
  
  
  // publish the message
  posePublisher_.publish(pose_out);

}


// main program
int main(int argc, char** argv)
{
  // initializing ros
  ROS_INFO(" initializing modify slam pose node");
  ros::init(argc, argv, "modify_slam_pose_node");

  ModifyPose mp;
 
  ros::spin();
}
