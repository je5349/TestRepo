#include <ros/ros.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "nmea_msgs/Sentence.h"
// #include <amazon/Object.h>

using namespace std;

int main(int argc, char** argv)
{  
  // initializing ros
  ROS_INFO(" initializing random_gps node");
  ros::init(argc, argv, "random_gps_node");
  ros::NodeHandle nh;
  // ros::Publisher pub = node_handle.advertise<message_type>(topic_name, queue_size);
  ros::Publisher gps_pub = nh.advertise<nmea_msgs::Sentence>("random_nmea_sentence", 1);

  
   ros::Rate r(20.0);  // frequency
   while(nh.ok())
   {
   	 ros::Time gps_time = ros::Time::now();
    //////////////////////////////////////////////
    //populate the nmea_sentence message
     nmea_msgs::Sentence nmea_sentence;
     nmea_sentence.header.stamp = gps_time;
     nmea_sentence.header.frame_id = "navsat";

     nmea_sentence.sentence = "$GPGGA,011906.05,3944.9679,N,10513.3265,W,9,08,0.9,1774.63,M,-15.50,M,04,0138*60";
     
     
     gps_pub.publish(nmea_sentence); // publish the message
     r.sleep();
   }
}
