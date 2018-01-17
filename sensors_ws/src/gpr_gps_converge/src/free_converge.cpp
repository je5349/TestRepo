#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstring>
#include <vector>
#include <ctime>
#include "ros/ros.h"
#include "gpr_collect/GprTrace.h"
#include "std_msgs/Int16.h"
#include "gpr_gps_converge/GprTraceLocation.h"
#include "gpr_gps_converge/GprConverged.h"

using namespace std;

class FreeConverge{
public:
	FreeConverge();
	void gprDataCallback(const gpr_collect::GprTrace& object);
	void gpsDataCallback(const gpr_gps_converge::GprTraceLocation& object);

private:
	ros::NodeHandle nh;
	ros::Subscriber gpr_receiver;
	ros::Subscriber gps_receiver;
//	ros::Publisher converged_data_emitter;

	std::vector<gpr_gps_converge::GprTraceLocation> gps_vector;
	void read_date(void);
	void generate_file_path(void);
	void save_param_file(gpr_collect::GprTrace, gpr_gps_converge::GprTraceLocation);
	void save_data_file(gpr_collect::GprTrace, gpr_gps_converge::GprTraceLocation);


	bool Start_flag;
	struct tm timeinfo_;
	char file_path_[128];
	string file_folder_;

};

FreeConverge::FreeConverge(){

	gpr_receiver = nh.subscribe("gpr_trace/gpr_free", 20, &FreeConverge::gprDataCallback, this);
	gps_receiver = nh.subscribe("gpr_pose", 20, &FreeConverge::gpsDataCallback, this);

//	converged_data_emitter = nh.advertise<gpr_gps_converge::GprConverged>("geobot_data/converged_gps_gpr",10);

	Start_flag = false;
	nh.param<string>("free_converge/data_folder", file_folder_,"/home/administrator/sensors_ws/src/gpr_gps_converge/data/");

}

void FreeConverge::read_date(void){
	time_t timer = time(NULL);
	struct tm timeinfo;
	timeinfo = *localtime(&timer);
	timeinfo_ = timeinfo;
}

void FreeConverge::generate_file_path(void){

	stringstream ss_;
	char year[6], month[4], day[4], hour[4], min[4], sec[4];
	ss_<<1900+timeinfo_.tm_year;
	ss_>>year;
	ss_.clear();
	ss_<<1+timeinfo_.tm_mon;
	ss_>>month;
	ss_.clear();
	ss_<<timeinfo_.tm_mday;
	ss_>>day;
	ss_.clear();
	ss_<<timeinfo_.tm_hour;
	ss_>>hour;
	ss_.clear();
	ss_<<timeinfo_.tm_min;
	ss_>>min;
	ss_.clear();
	ss_<<timeinfo_.tm_sec;
	ss_>>sec;
	char file[128];
	strcpy(file, file_folder_.c_str());
	strcat(file, year);
	strcat(file,"_");
	strcat(file,month);
	strcat(file,"_");
	strcat(file,day);
	strcat(file,"_");
	strcat(file,hour);
	strcat(file,"_");
	strcat(file,min);
	strcat(file,"_");
	strcat(file,sec);
	strcpy(file_path_, file);

}

void FreeConverge::save_param_file(gpr_collect::GprTrace msg, gpr_gps_converge::GprTraceLocation gps_msg){
	char param_file_path[128];
	strcpy(param_file_path, file_path_);
	strcat(param_file_path, ".param");
	ofstream param_file(param_file_path, ios::out);
	if(!param_file){
		cerr<<"Fail to create the param_data_printout file:"
			<<param_file_path<<endl;
		return;
	}
	param_file<<"Time: "<<asctime(&timeinfo_)<<endl;
	param_file<<"traceSize: "<<msg.traceSize_<<endl;
	param_file<<"headerSize: "<<msg.headerSize_<<endl;
	param_file<<"headerID: "<<msg.headerID_<<endl;
	param_file<<"traceStatusFlag: "<<msg.traceStatusFlag_<<endl;
	param_file<<"numStacks: "<<msg.numStacks_<<endl;
	param_file<<"hardwareFlag: "<<msg.hardwareFlag_<<endl;
	param_file<<"dataSize: "<<msg.dataSize_<<endl;
	param_file<<"sampleInterval: "<<msg.sampleInterval_<<endl;
	param_file<<"frequency: "<<msg.frequency_<<endl;
	param_file<<"CoordinateFormat: "<<gps_msg.CoordinateFormat<<endl;

	param_file.close();
}

void FreeConverge::save_data_file(gpr_collect::GprTrace msg, gpr_gps_converge::GprTraceLocation gps_msg){
	char data_file_path[128];
	strcpy(data_file_path, file_path_);
	strcat(data_file_path, ".data");
	ofstream data_file(data_file_path, ios::app);
	if(!data_file){
		cerr<<"Fail to create the data_printout file:"
			<<data_file_path<<endl;
		return;
	}
	data_file.precision(12);
	data_file<<msg.rosTime_.sec<<"."<<msg.rosTime_.nsec<<",";
	data_file<<gps_msg.stamp.sec<<"."<<gps_msg.stamp.nsec<<",";
	data_file<<fixed<<gps_msg.Longitude<<",";
	data_file<<fixed<<gps_msg.Latitude<<",";
	data_file<<fixed<<gps_msg.Altitude<<",";
	data_file<<gps_msg.latitude_label<<",";
	data_file<<gps_msg.longitude_label<<",";
	data_file<<gps_msg.UTMZone<<",";
	for(int i = 0; i<msg.dataSize_; i++){
		data_file<<msg.traceData_[i]<<" ";
	}
	data_file<<endl;

	data_file.close();
}

void FreeConverge::gprDataCallback(const gpr_collect::GprTrace& object){

	gpr_collect::GprTrace msg;
	msg = object;


	cout<<"trace number: "<<msg.traceNumber_<<endl;
	if(!gps_vector.empty()){
		gpr_gps_converge::GprTraceLocation gps_msg;
		gps_msg = gps_vector.back();

		// execute only once at the first trace
		if(!Start_flag){
			read_date();
			generate_file_path();
			save_param_file(msg, gps_msg);
			Start_flag = true;
		}
		// execute only once at the first trace

		save_data_file(msg, gps_msg);
	}

}

void FreeConverge::gpsDataCallback(const gpr_gps_converge::GprTraceLocation& object){
	while(gps_vector.size()>10){
		gps_vector.erase(gps_vector.begin());
	}
	gps_vector.push_back(object);
}


int main(int argc, char** argv){

	ros::init(argc, argv, "free_converge");
	ROS_INFO("Initializing free_converge node...");

	FreeConverge fcNode;
	ros::spin();
	return 0;
}

