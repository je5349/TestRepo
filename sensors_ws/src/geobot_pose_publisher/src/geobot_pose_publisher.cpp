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
#include <tf/tf.h>
#include <tf/LinearMath/Quaternion.h>
#include <tf/transform_listener.h>
#include <geobot_pose_publisher/navsat_conversions.h>
#include <geobot_pose_publisher/GprTraceLocation.h>
#include <sensor_msgs/NavSatFix.h>


using namespace std;


double output_pose_frequency;


class geobot_pose_publisher_class
{
public:


  geobot_pose_publisher_class();
  void gpsFixCallback(const sensor_msgs::NavSatFixConstPtr& msg);
  void run();

  

  
private:
  
  ros::Subscriber gpsSubscriber, gpsfixSubcriber;
  ros::Publisher gprPublisher;
  ros::NodeHandle nh;
  ros::NodeHandle nhPriv;
  tf::TransformListener listener; // should not be in a callback
  bool output_pose_in_utm;
  string gpr_antenna_frame_id, world_frame_id;
  double utmZ;
  string utmZone, longitude_label, latitude_label;
  double gps_height_above_ground;



};


geobot_pose_publisher_class::geobot_pose_publisher_class(): nhPriv("~")
{
  nhPriv.param<double>("output_pose_frequency", output_pose_frequency, 20.0); // This is the frequency(Hz) at which pose should written to the gpr-spidar
  nhPriv.param<bool>("output_pose_in_utm", output_pose_in_utm, true); // If false, the pose is in longitude and latitude
  nhPriv.param<string>("gpr_antenna_frame_id",gpr_antenna_frame_id, "gpr");
  nhPriv.param<string>("world_frame_id",world_frame_id, "utm");
  nhPriv.param<double>("gps_height_above_ground",gps_height_above_ground, 0.4);
  nhPriv.param<string>("utmZone",utmZone, "13S");

 
  gpsfixSubcriber = nh.subscribe("gps/fix", 10, &geobot_pose_publisher_class::gpsFixCallback, this);
  gprPublisher = nh.advertise<geobot_pose_publisher::GprTraceLocation>("gpr_pose", 20);
  

  utmZ = 0.0;
  
}

void geobot_pose_publisher_class::gpsFixCallback(const sensor_msgs::NavSatFixConstPtr& msg)
{
	
   // This it to update the gps info like zone, altitude
	double utmY, utmX; //needs to be locally defined since not used anywhere

	if(std::isnan(msg->latitude) || std::isnan(msg->longitude) || std::isnan(msg->altitude))
	{
		return;
	}

	RobotLocalization::NavsatConversions::LLtoUTM(msg->latitude, msg->longitude, utmY, utmX, utmZone);
	utmZ = msg->altitude - gps_height_above_ground;

	// other parameters like status can be added
}


void geobot_pose_publisher_class::run()
{
	 tf::StampedTransform world_gpr_transform;
	 tf::Matrix3x3 mat;
	 double roll;
	 double pitch;
	 double yaw;
	 double gpr_x;
	 double gpr_y;
	 double gpr_z;
	 double gpr_latitude;
	 double gpr_longitude;
	 ostringstream stream_data; 
	 stream_data.precision(10);
	 string output_data;
	 string CoordinateFormat;
	 geobot_pose_publisher::GprTraceLocation msg;

		 
	try{
		listener.lookupTransform(world_frame_id.c_str(),gpr_antenna_frame_id.c_str(), ros::Time(0), world_gpr_transform);	
		}
		catch(tf::TransformException &ex)
		{
			ROS_ERROR("%s",ex.what());
			return;
		}
		

		mat.setRotation(world_gpr_transform.getRotation());
		mat.getRPY(roll, pitch, yaw);

		gpr_x = world_gpr_transform.getOrigin().getX();
		gpr_y = world_gpr_transform.getOrigin().getY();
		gpr_z = utmZ;
		CoordinateFormat = "UTM";


		if(!output_pose_in_utm)
		{
			// convert to longitude and latitude
			RobotLocalization::NavsatConversions::UTMtoLL(gpr_y, gpr_x, utmZone, gpr_latitude, gpr_longitude);
			gpr_y = gpr_latitude;
			gpr_x = gpr_longitude;
			CoordinateFormat = "LongLat";
		}

		if(gpr_y < 0.0)
		{
			latitude_label = "S";
		}
		else
		{
			latitude_label = "N";
		}

		if(gpr_x < 0.0)
		{
			longitude_label = "W";
		}
		else
		{
			longitude_label = "E";
		}



		// then publish out as message
		msg.stamp = ros::Time::now();
		msg.CoordinateFormat = CoordinateFormat;
		msg.Longitude = abs(gpr_x);
		msg.Latitude = abs(gpr_y);
		msg.Altitude = gpr_z;
		msg.latitude_label = latitude_label;
		msg.longitude_label = longitude_label;
		msg.UTMZone = utmZone;

		gprPublisher.publish(msg);

}


// main program
int main(int argc, char** argv)
{
  // initializing ros
  ROS_INFO(" initializing geobot-gpr pose publisher node");
  ros::init(argc, argv, "geobot_gpr_publisher_node");


  geobot_pose_publisher_class gpp;

  
  ros::Rate output_rate(output_pose_frequency); // Hz
  
  while(ros::ok())
  {

	ros::spinOnce();
	gpp.run();
	output_rate.sleep(); // sleeps for the any leftover time in a cycle. Calculated from the lasr time sleep.

 }
 
 	



}
