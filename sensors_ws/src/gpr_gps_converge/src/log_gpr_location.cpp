#include <ros/ros.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "std_msgs/Float32.h"
#include "gpr_gps_converge/GprTraceLocation.h"
#include <math.h>

using namespace std;

class FileWrite{

public:
	FileWrite();
	void CallBack(const gpr_gps_converge::GprTraceLocation& msg);
	std::ofstream File_data;
	ros::NodeHandle nh;
	ros::Subscriber FileWriter;
// private: 
	
	
	

};

FileWrite::FileWrite() {
	
	FileWriter = nh.subscribe("gpr_pose", 1, &FileWrite::CallBack, this);

	
}

void FileWrite::CallBack(const gpr_gps_converge::GprTraceLocation& msg)
{
	// int count = 0;	
	
	if(File_data.is_open())
	{	
		File_data << msg.stamp << "\t" << msg.CoordinateFormat << "\t" << msg.Longitude << "\t" << msg.Latitude << "\t" << msg.Altitude << "\t" << msg.latitude_label << "\t" << msg.longitude_label << "\t" << msg.UTMZone << endl;
	 if(msg.Latitude == NAN || msg.Longitude == NAN)
	 {
	 	ROS_INFO("Nan warning");
	 }
	}
	else
	{
		ROS_INFO("Can't open file");

	}
		
}

int main(int argc, char **argv){

	ROS_INFO("initializing FileWrite");
	ros::init(argc,argv, "gpr_location_log");

	
	FileWrite fw;
	fw.File_data.open("/home/administrator/sensors_ws/src/gpr_gps_converge/data/GPR_LOCATION_LOG.txt");
	fw.File_data.precision(14);
	fw.File_data << "time_stamp" << "\t" << "CoordinateFormat" << "\t" << "Longitude" << "\t" << "Latitude" << "\t" <<"Altitude" << "\t" << "latitude_label" << "\t" << "longitude_label" << "\t" << "UTMZone" << endl;
	
	ros::spin();
	fw.File_data.close();
	
return 0;
}
