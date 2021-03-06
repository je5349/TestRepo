
#include <ros/ros.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <std_msgs/String.h>
#include <ros2udp/spi_array.h>
#include <ros2udp/GprConverged.h>
#include <ctime> //needed for time() in random number generator
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <typeinfo>
#include <time.h>

#define BUFLEN 2048
#define MSGS 5	/* number of messages to send */

using namespace std;

//--------------Class------------------------------
class msg2socket
{
  ros::Subscriber data_in;
  ros::NodeHandle nh;

  //void udp_out(const ros2udp::GprTrace msg); //The class callback function?
  void udp_out(const ros2udp::GprConverged msg); //The class callback function?
  string today_date(void); //function that makes a string if current date


  public: 
    msg2socket();
    bool done; //header logic, print or dont print header every trace

};

//----------------Constructor----------------------------

msg2socket::msg2socket()
{
	done = 0; //First header not printed yet
	data_in = nh.subscribe("/geobot_data/converged_gps_gpr",2, &msg2socket::udp_out,this);
}

//-------------------Date function--------------------------
string msg2socket::today_date(void)
{
	const char* MONTHS[] =
	{
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
	};
	time_t     rawtime;
	struct tm* timeinfo;

	time( &rawtime );
	timeinfo = localtime( &rawtime );
	stringstream ss_date;
	ss_date << "Today's date is "
       		<< timeinfo->tm_mday << " "
      	 	<< MONTHS[ timeinfo->tm_mon ] << " "
       		<< (timeinfo->tm_year + 1900) << ".\n";
	return ss_date.str();
}
//----------------------------------------------------------




//------------- callback function to receive item_order data---------------

void msg2socket::udp_out(const ros2udp::GprConverged msg)
{

	ROS_INFO("Hey Im in the Callback!");  
  

	// Initializing Objects //
	//remaddr is receiving address
	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen=sizeof(remaddr);
	//char *server is place where message is being sent
	//const char * server = "138.67.227.232";	/* change this to use a different server */
	const char * server = "192.168.0.71";	/* Use for Geobot Tests */
	//const char * server = "138.67.41.241";	/* Use for indoor robotics lab tests */

		//const char * server = "10.0.0.6";	/* change this to use a different server */
	

	short shortBuf[210];

	/* create a socket */
	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");



	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY); //usually port 21234
	//"Send From" aka Client port: 5060
	myaddr.sin_port = htons(5060);
	//myaddr.sin_port = 5060;



	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		//return 0;
	}       

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */


	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) // <<-------------
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
//---------------------------------"Only Once Header"-----------------------------------------
	//use if you only want header (parameters) once per experiment
	if (done == 0) 
	{
		//ROS Time Interval (time between each of the 200 samples)???
		char time_intv_buf[50] = {0};
		string time_intv = msg.sampleInterval_;
    	strcpy(time_intv_buf, "Time Interval: ");
		strcat(time_intv_buf, time_intv.c_str());
		if (sendto(fd, time_intv_buf, strlen(time_intv_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
			perror("sendto");

		//ROS Frequency of the GPR 500 MHz or 1000 MHz
		char freq_buf[50] = {0};
		string freq = msg.frequency_;
    	strcpy(freq_buf, "Frequency: ");
		strcat(freq_buf, freq.c_str());
		if (sendto(fd, freq_buf, strlen(freq_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
			perror("sendto");

		//ROS Samples per trace
		char dataSize_buf[50] = {0};	
		int dataSize = msg.dataSize_;
		sprintf(dataSize_buf,"Samples per trace: %d",dataSize);
		if (sendto(fd, dataSize_buf, strlen(dataSize_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
			perror("sendto");

		//ROS Date of experiment
		char date_buf[50] = {0};
		string d_test = msg2socket::today_date();
		//cout << "date? " << d_test   << "\n";
		strcpy(date_buf, d_test.c_str());
		if (sendto(fd, date_buf, strlen(date_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
			perror("sendto");

		//ROS Number of Data Stacks 
		char dataStack_buf[50] = {0};	
		int numStacks = msg.numStacks_;
		sprintf(dataStack_buf,"Stack Number: %d",numStacks);
		if (sendto(fd, dataStack_buf, strlen(dataStack_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
			perror("sendto");


	 	done= 1; //lets program know "once only header" has been printed
 	}

//--------------------- "Every Trace" Header--------------------------------------------

	//ROS Time header (GPR)
	char time_buf[50] = {0};
	int sec = msg.rosTime_.sec;
	int nsec = msg.rosTime_.nsec;
	sprintf(time_buf,"GPR ROS Time (sec): %d.%d",sec,nsec);

	if (sendto(fd, time_buf, strlen(time_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
		perror("sendto");

	//ROS Time header (GPS)
	char time2_buf[50] = {0};
	int sec2 = msg.stamp.sec;
	int nsec2 = msg.stamp.nsec;
	sprintf(time2_buf,"GPS ROS Time (sec): %d.%d",sec2,nsec2);
	if (sendto(fd, time2_buf, strlen(time2_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
		perror("sendto");

	//ROS Trace Number header
	char traceNumber_buf[50] = {0};	
	int traceNumber = msg.traceNumber_;
	sprintf(traceNumber_buf,"Trace Number: %d",traceNumber);
	if (sendto(fd, traceNumber_buf, strlen(traceNumber_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
		perror("sendto");

	//Body of Coordinates Message	
	// X
	char longitude_buf[60] = {0};
	double longitude = msg.Longitude;
	sprintf(longitude_buf,"Longitude: %f",longitude);
	if (sendto(fd, longitude_buf, strlen(longitude_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
		perror("sendto");
	// Y
	char latitude_buf[60] = {0};
	double latitude = msg.Latitude;
	sprintf(latitude_buf,"Latitude: %f",latitude);
	if (sendto(fd, latitude_buf, strlen(latitude_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
		perror("sendto");
	// Z
	char altitude_buf[60] = {0};
	double altitude = msg.Altitude;
	sprintf(altitude_buf,"Altitude (m): %f",altitude);
	if (sendto(fd, altitude_buf, strlen(altitude_buf),0,(struct sockaddr *)&remaddr,slen)==-1)
		perror("sendto");


//-------------------GPR Trace------------------------------------------------------------

	//Body of Trace Message	
	char buf[BUFLEN] = {0};	
	int n = 0;
	int n_old = 0;
	for(int i = 0; i < 200; i++)
	{
		//loads msg.traceData_[i] sample in trace
		int trace = msg.traceData_[i];

		//writes each sample to the end of a buffer and adds a space.
		//Therby making one long buffer(buf) that will be sent out
		//after the 200 iterations (note: buf is pointer to buf[])
		n = sprintf(buf+n_old,"%d%c",trace,' ');

		//memory address offset counter that is used in 
		//the pointer arithmetic "buf+n_old"
		n_old = n + n_old;

	}

		//Sends out the long buf[] char array to the listening port
		if (sendto(fd, buf, strlen(buf),0,(struct sockaddr *)&remaddr,slen)==-1)
				perror("sendto");
//------------------------------------------------------------------------------------
	
	close(fd); //closes port
	ROS_INFO("end of call back");
}

//------------------- main program--------------

int main(int argc, char** argv)
{

  // initializing ros
  ROS_INFO(" initializing Spidar to UDP node");
  ros::init(argc, argv, "spidar_listener"); //initiating node with unique node name
  msg2socket str2udp;

   while(ros::ok)
  {
    ros::spin();
    return 0;
  }

}


