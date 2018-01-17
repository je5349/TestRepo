#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Odometry.h"
#include <os5000s_compass/SerialPort.h>
#include <os5000s_compass/compass.h>
#include <os5000s_compass/Mutex.h>
#include <os5000s_compass/precisionCalendar.h>
#include <os5000s_compass/Timer.h>
#include <os5000s_compass/Demo.h>
#include <os5000s_compass/compass_heading.h>
#include <iostream>
#include <string>
#include <unistd.h>

struct quat{
float q_w;
float q_x;
float q_y;
float q_z;
};

quat toQuaternion(double pitch, double roll, double yaw)
{
  quat q;

  double cy = cos(yaw * 0.5);
  double sy = sin(yaw * 0.5);
  double cr = cos(roll * 0.5);
  double sr = sin(roll * 0.5);
  double cp = cos(pitch * 0.5);
  double sp = sin(pitch * 0.5);

  q.q_w = cy * cr * cp + sy * sr * sp;
  q.q_x = cy * sr * cp - sy * cr * sp;
  q.q_y = cy * cr * sp + sy * sr * cp;
  q.q_z = sy * cr * cp - cy * sr * sp;

  return q;
}

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

double yaw_I;
double roll_I;
double pitch_I;

using namespace std;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "compass_heading");
  ros::init(argc, argv, "orien_msg");
  ros::NodeHandle n;
  ros::Publisher compass_heading_pub = n.advertise<os5000s_compass::compass_heading>("compass_heading", 1);
  ros::Publisher orien_msg_pub = n.advertise<nav_msgs::Odometry>("orien_msg", 1);
  ros::Rate loop_rate(40);

  Compass myCompass;
  while (ros::ok())
  {
    os5000s_compass::compass_heading msg;
    nav_msgs::Odometry orien_msg;
    quat qu;

    msg.header.stamp = ros::Time::now();
    msg.heading = myCompass.getHeading();
    msg.pitch = myCompass.getPitch();
    msg.roll = myCompass.getRoll();
    msg.temperature = myCompass.getTemperature();
    msg.magnetic_vector_length = myCompass.getMagneticVectorLength();
    msg.mx = myCompass.getMx();
    msg.my = myCompass.getMy();
    msg.mz = myCompass.getMz();
    msg.acceleration_vector_length = myCompass.getAccelerationVectorLength();
    msg.ax = myCompass.getAx();
    msg.ay = myCompass.getAy();
    msg.az = myCompass.getAz();

    yaw_I = degreesToRadians(msg.heading);
    pitch_I = degreesToRadians(msg.pitch);
    roll_I = degreesToRadians(msg.roll);

    qu = toQuaternion(pitch_I,roll_I,yaw_I);

    orien_msg.header.stamp = ros::Time::now();          
    orien_msg.header.frame_id = "odom"; 
	orien_msg.pose.pose.position.x = 0.0;
    orien_msg.pose.pose.position.y = 0.0;
    orien_msg.pose.pose.position.z = 0.0;                      
    orien_msg.pose.pose.orientation.x = qu.q_x;               
    orien_msg.pose.pose.orientation.y = qu.q_z;               
    orien_msg.pose.pose.orientation.z = qu.q_z;               
    orien_msg.pose.pose.orientation.w = qu.q_w;

    if( std::abs(myCompass.getAccelerationVectorLength()-1)>0.05 )
    {// data is crap

        for( int i=0; i< 6; i++ )
            for( int j=0; j<6; j++ )
                if( i!= j)
                    orien_msg.pose.covariance[i*6+j] = 0;
                else
                    orien_msg.pose.covariance[i*6+j] = 99999;
    }
    else
    {
        // data is good
        for( int i=0; i< 6; i++ )
            for( int j=0; j<6; j++ )
                if( i!= j)
                    orien_msg.pose.covariance[i*6+j] = 0;
                else if( i < 3)
                    orien_msg.pose.covariance[i*6+j] = 99999;
                else
                    orien_msg.pose.covariance[i*6+j] = 0.01;
            }

    orien_msg.twist.twist.linear.x = 0.0;
    orien_msg.twist.twist.linear.y = 0.0;
    orien_msg.twist.twist.linear.z = 0.0;
    orien_msg.twist.twist.angular.x = 0.0;
    orien_msg.twist.twist.angular.y = 0.0;
    orien_msg.twist.twist.angular.z = 0.0;

    for( int i=0; i< 6; i++ )
        for( int j=0; j<6; j++ )
            if( i!= j)
                orien_msg.twist.covariance[i*6+j] = 0;
            else if( i < 3)
                orien_msg.twist.covariance[i*6+j] = 99999;

    compass_heading_pub.publish(msg);
    orien_msg_pub.publish(orien_msg);
    
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

//GOTO THIS LOCATION IN GEOBOT: /opt/ros/indigo/share/husky_control/config
//OPEN THIS FILE USING NANO: localization.yaml || Command to open: sudo nano localization.yaml
//ADD THE FOLLOWING PIECE OF CODE IN localization.yaml

// compass0: os5000s_compass/compass_heading
// compass0_config: [false, false, false,
//               true, true, true,
//               false, false, false,
//               false, false, false,
//               false, false, false]
// compass0_differential: true
