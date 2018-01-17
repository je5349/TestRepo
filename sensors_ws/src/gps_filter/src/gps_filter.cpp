#include <ros/ros.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sensor_msgs/NavSatFix.h>


using namespace std;


class GpsFilter
{
public:
  GpsFilter();
  void gpsFixReceived(const sensor_msgs::NavSatFix& msg);
protected:
  ros::Subscriber gpsFixSubscriber_;
  ros::Publisher gpsFixFilteredPublisher_;
  ros::NodeHandle nh;
};

GpsFilter::GpsFilter()
{
  // nh.subscribe(topic_name,queue_size, pointer_to_callback_function);
  gpsFixSubscriber_ = nh.subscribe("gps/fix", 1, &GpsFilter::gpsFixReceived,this);
  gpsFixFilteredPublisher_ = nh.advertise<sensor_msgs::NavSatFix>("gps/fix_filtered", 20);
}

// callback function to receive original gps/fix data and adjust the covariance 
void GpsFilter::gpsFixReceived(const sensor_msgs::NavSatFix& msg)
{
  // processing the item order recieved and computing the grasp location
  sensor_msgs::NavSatFix newmsg = msg;
  // populating the message
 
  if(msg.status.status < 2)
  {
  newmsg.position_covariance[0] = 100*msg.position_covariance[0];
  newmsg.position_covariance[4] = 100*msg.position_covariance[4];
  newmsg.position_covariance[8] = 100*msg.position_covariance[8];
  }
  
  // publish the message
  gpsFixFilteredPublisher_.publish(newmsg);

}


// main program
int main(int argc, char** argv)
{
  // initializing ros
  ROS_INFO(" initializing the gps_filter node");
  ros::init(argc, argv, "gps_filter_node");

  GpsFilter gfilter;
 
  ros::spin();
}
