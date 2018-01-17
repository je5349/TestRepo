#include <ros/ros.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "nmea_msgs/Sentence.h"
#include "spidar/serial.h"

//#include <amazon/Grasp.h>

using namespace std;

void* spidar_port;

class spidar_gps
{
public:
  spidar_gps();
  void forward_gps(const nmea_msgs::Sentence& spidar_nmea_sentence);


private:
  
  ros::Subscriber gpsSubscriber;
  ros::NodeHandle nh;
};

spidar_gps::spidar_gps()
{
  // nh.subscribe(topic_name,queue_size, pointer_to_callback_function);
  gpsSubscriber = nh.subscribe("/gps/nmea_sentence",1, &spidar_gps::forward_gps,this);
}

// callback function to spidar_gps
void spidar_gps::forward_gps(const nmea_msgs::Sentence& spidar_nmea_sentence)
{
  
  // print out the gps sent to the spidar
  string output = spidar_nmea_sentence.sentence;
  output = output + "\r\n";
   ROS_INFO("%s \n", output.c_str());


  int status = WriteData(spidar_port, output.c_str(), output.length());

  if (status == -1)
  {
    ROS_INFO(" Unable to open port");
    CloseSerial(spidar_port);
    ros::shutdown();
  }

}


// main program
int main(int argc, char** argv)
{
  // initializing ros
  ROS_INFO(" initializing gps2spidar node");
  ros::init(argc, argv, "gps2spidar_node");



  spidar_gps sg;

  string device = "/dev/ttyUSB0";
  int status = OpenSerial(&(spidar_port), device.c_str());
  if (status == -3)
  {
    ROS_INFO(" Unable to open port");
    ros::shutdown();
  }

  SetupSerial(spidar_port);

  ros::spin();

  CloseSerial(spidar_port);
}
