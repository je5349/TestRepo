#include <ros/ros.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "std_msgs/Float32.h"
#include "gpr_collect/GprTrace.h"
#include <math.h>

using namespace std;

class FileWrite{

public:
	FileWrite();
	void CallBack(const gpr_collect::GprTrace& msg);
	std::ofstream File_data;
	ros::NodeHandle nh;
	ros::Subscriber FileWriter;
// private: 
	
	
	

};

FileWrite::FileWrite() {
	
	FileWriter = nh.subscribe("gpr_trace/gpr_free", 1, &FileWrite::CallBack, this);

	
}

void FileWrite::CallBack(const gpr_collect::GprTrace& msg)
{
	// int count = 0;	
	
	if(File_data.is_open())
	{	
		for(int i = 0; i<msg.dataSize_; i++)
		{
                	File_data<<msg.traceData_[i]<<" ";
        	}
        	File_data<<endl;
       
	}
	else
	{
		ROS_INFO("Can't open file");

	}
		
}

int main(int argc, char **argv){

	ROS_INFO("initializing FileWrite");
	ros::init(argc,argv, "gpr_trace_log");

	
	FileWrite fw;
	fw.File_data.open("/home/administrator/sensors_ws/src/gpr_gps_converge/data/GPR_TRACE_LOG.txt");
	fw.File_data.precision(14);
	
	
	ros::spin();
	fw.File_data.close();
	
return 0;
}
