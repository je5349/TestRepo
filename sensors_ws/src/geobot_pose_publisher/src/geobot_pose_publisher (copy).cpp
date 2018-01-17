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
#include <sensor_msgs/NavSatFix.h>
#include "geobot_pose_publisher/serial.h"


using namespace std;

void* spidar_port;
double output_pose_frequency;
bool forward_rawgps2serial;

class geobot_pose_publisher
{
public:


  geobot_pose_publisher();
  void forward_gps(const nmea_msgs::Sentence& spidar_nmea_sentence);
  void gpsFixCallback(const sensor_msgs::NavSatFixConstPtr& msg);
  void run();
  void output2serial(string output);
  

  
private:
  
  ros::Subscriber gpsSubscriber, gpsfixSubcriber;
  ros::NodeHandle nh;
  ros::NodeHandle nhPriv;
  tf::TransformListener listener; // should not be in a callback
  bool output_pose_in_utm;
  string gpr_antenna_frame_id, world_frame_id;
  double utmZ;
  string utmZone, longitude_label, latitude_label;
  double gps_height_above_ground;



};


geobot_pose_publisher::geobot_pose_publisher(): nhPriv("~")
{
  nhPriv.param<double>("output_pose_frequency", output_pose_frequency, 20.0); // This is the frequency(Hz) at which pose should written to the gpr-spidar
  nhPriv.param<bool>("output_pose_in_utm", output_pose_in_utm, true); // If false, the pose is in longitude and latitude
  nhPriv.param<bool>("forward_rawgps2serial",forward_rawgps2serial, false);
  nhPriv.param<string>("gpr_antenna_frame_id",gpr_antenna_frame_id, "gpr");
  nhPriv.param<string>("world_frame_id",world_frame_id, "utm");
  nhPriv.param<double>("gps_height_above_ground",gps_height_above_ground, 0.4);
  nhPriv.param<string>("utmZone",utmZone, "13S");

  gpsSubscriber = nh.subscribe("/gps/nmea_sentence",10, &geobot_pose_publisher::forward_gps,this); // this is to forward raw gps to the serial port
  gpsfixSubcriber = nh.subscribe("gps/fix", 10, &geobot_pose_publisher::gpsFixCallback, this);

  utmZ = 0.0;
  
}

void geobot_pose_publisher::gpsFixCallback(const sensor_msgs::NavSatFixConstPtr& msg)
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

// callback function to forward raw gps data
void geobot_pose_publisher::forward_gps(const nmea_msgs::Sentence& spidar_nmea_sentence)
{
 
	 
	 if(forward_rawgps2serial)
	 { 
		  // print out the gps sent to the spidar
		  string output = spidar_nmea_sentence.sentence;
		  string token;
		  stringstream split_output(output);

		// checking for the first string in the gps to extract GPGGA
		  getline(split_output, token, ',');
		// printf("%s\n", token.c_str());

		if (!token.compare("$GPGGA"))
		{
		  output = output + "\r\n";
		   ROS_INFO("%s \n", output.c_str());

		   output2serial(output);

		}

	}

}

void geobot_pose_publisher::output2serial(string output)
{
		  int status = WriteData(spidar_port, output.c_str(), output.length());

		  ROS_INFO("%s", output.c_str());

		  if (status == -1)
		  {
		    ROS_INFO(" Unable to open port");
		    CloseSerial(spidar_port);
		    ros::shutdown();
		  }
}


void geobot_pose_publisher::run()
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

		if(!output_pose_in_utm)
		{
			// convert to longitude and latitude
			RobotLocalization::NavsatConversions::UTMtoLL(gpr_y, gpr_x, utmZone, gpr_latitude, gpr_longitude);
			gpr_y = gpr_latitude;
			gpr_x = gpr_longitude;
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

		// then write to serial as intended

		stream_data << "GPGGA" <<"," << ros::Time::now() << "," << abs(gpr_y) << "," << latitude_label <<","<< abs(gpr_x) <<"," << longitude_label << "," << 4 << "," << 12 << "," << 0.1 << "," << gpr_z << "," << "M" << "," << "" << ","<< "M" << "," << "" << ","; //check out the real format
		
		//stream_data << "GPGGA" <<"," << "" << "," << "" << "," << "" <<","<< "" <<"," << "" << "," << 0 << "," << "" << "," << "" << "," << "" << "," << "" << "," << "" << ","<< "" << "," << "" << ","; 

		// calculate checksum and add it to the data stream
		string stream_data_checksum = stream_data.str();
		char checksum = 0;

		for(int i = 0; i<stream_data_checksum.length(); i++)
		{
			checksum = char(checksum ^ stream_data_checksum.at(i));
		}

		stream_data << "*" << std::hex << (int)checksum;
		output_data =  "$" + stream_data.str() + "\r\n";
		 
		output2serial(output_data);

}


// main program
int main(int argc, char** argv)
{
  // initializing ros
  ROS_INFO(" initializing geobot-gpr pose publisher node");
  ros::init(argc, argv, "geobot_gpr_publisher_node");


  geobot_pose_publisher gpp;

  string device = "/dev/gps_spidar";
  int status = OpenSerial(&(spidar_port), device.c_str());
  if (status == -3)
  {
    ROS_INFO(" Unable to open port");
    ros::shutdown();
  }

  SetupSerial(spidar_port);

  
  ros::Rate output_rate(output_pose_frequency); // Hz
  
  while(ros::ok())
  {
	  if(forward_rawgps2serial)
	  {
	  	// forward the raw gps data
	  	
	  	ros::spinOnce();
	  	

	  }
	  else
	  {
	  	 // output the actual gpr antenna pose to the spidar
	  	 ros::spinOnce();
	  	 gpp.run();


	  }

	 output_rate.sleep(); // sleeps for the any leftover time in a cycle. Calculated from the lasr time sleep.

 }
 

	CloseSerial(spidar_port);

}
