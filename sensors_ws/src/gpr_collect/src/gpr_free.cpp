#include <iostream>
#include <cstring>
#include <cstring>
#include "ros/ros.h"
#include "gpr_collect/n_nic.h"
#include "gpr_collect/GprTrace.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Time.h"


using namespace std;
int main(int argc, char** argv){

	ros::init(argc, argv, "gpr_free");
	ROS_INFO("Initializing gpr_free node...");

	ros::NodeHandle nh1_;
	ros::Publisher pub_ = nh1_.advertise<gpr_collect::GprTrace>("gpr_trace/gpr_free",1);
	ros::Rate loop_rate(15);
	string file_folder;
	nh1_.param<string>("gpr_free/param_folder",file_folder,"/home/administrator/sensors_ws/src/gpr_collect/param/");
	n_nic Nic1;
//  bool flag = false;
  Nic1._initNIC("41",1213,file_folder);

	while(ros::ok()){
		ros::Time time = ros::Time::now();
		Nic1._FreeRunTracesCollection();

		while(!Nic1.trace_stack_.empty()){

			//publish the trace out//
			//get one trace from the stack//
			Gpr_trace tmp_trace;
			tmp_trace = Nic1.trace_stack_.front();
			//erase the published trace//
			Nic1.trace_stack_.erase(Nic1.trace_stack_.begin());

			//populate the message//
			gpr_collect::GprTrace tmp_trace_msg;
			tmp_trace_msg.rosTime_ = time;
			tmp_trace_msg.traceSize_ = tmp_trace.traceSize_;
			tmp_trace_msg.headerSize_ = tmp_trace.headerSize_;
//			strcpy(tmp_trace_msg.headerID_, tmp_trace.headerID_);
			tmp_trace_msg.headerID_ = tmp_trace.headerID_;
			tmp_trace_msg.stampCount_ = tmp_trace.dataStamp_.count_;
			tmp_trace_msg.traceNumber_ = tmp_trace.dataStamp_.traceNumber_;

			tmp_trace_msg.odoTick_ = tmp_trace.dataStamp_.odoTick_;
			tmp_trace_msg.tracePos_ = tmp_trace.dataStamp_.tracePos_;
			tmp_trace_msg.duration_ = tmp_trace.dataStamp_.duration_;
			tmp_trace_msg.traceStatusFlag_ = tmp_trace.traceStatusFlag_;
			tmp_trace_msg.numStacks_ = tmp_trace.numStacks_;
			tmp_trace_msg.hardwareFlag_ = tmp_trace.hardwareFlag_;
			tmp_trace_msg.dataSize_ = (tmp_trace_msg.traceSize_-tmp_trace_msg.headerSize_)/2;

			for(int i = 0; i<tmp_trace_msg.dataSize_; i++){
				tmp_trace_msg.traceData_.push_back(tmp_trace.traceData_[i]);
			}
			tmp_trace_msg.sampleInterval_ = Nic1.getSampleInterval();
			tmp_trace_msg.frequency_ = Nic1.getFrequency();

			//publish the message//
			pub_.publish(tmp_trace_msg);

		}
		loop_rate.sleep();

	}
	Nic1._nic_close();
	return 0;
}

