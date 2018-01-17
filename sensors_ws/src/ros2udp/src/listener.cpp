

#include <ros/ros.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
//#include <kobuki_msgs/BumperEvent.h> //Message type in : Bumper
//#include <geometry_msgs/Twist.h> //Message Type out : Velocity
#include <std_msgs/String.h>
#include <ctime> //needed for time() in random number generator
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"

#define BUFLEN 2048
#define MSGS 5	/* number of messages to send */

using namespace std;

//--------------Class------------------------------
class bumpbump
{
  ros::Subscriber data_in;
  //ros::Publisher pb_velocity;
  ros::NodeHandle nh;
  //double command_velocity_l;
  //double command_velocity_a;
  //int b_0

  void udp_out(const std_msgs::String msg); //The class callback function?

  public: 
    bumpbump();
    //void pub_vel();

};
//----------------Constructor----------------------------
bumpbump::bumpbump()
{
  //command_velocity_l = .2;
  //command_velocity_a = 0;

  // nh.subscribe(topic_name,queue_size, pointer_to_callback_function);
 
 
  //pb_velocity = nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  //sb_bump_event = nh.subscribe<kobuki_msgs::BumperEvent>("msg",10, &bumpbump::avoid_obs,this); // <( O.o )>
  //sb_bump_event = nh.subscribe("/mobile_base/events/bumper",10, &bumpbump::avoid_obs,this);
  data_in = nh.subscribe("/chatter",10, &bumpbump::udp_out,this);
}

//------------- callback function to receive item_order data---------------
//void bumpbump::avoid_obs(const kobuki_msgs::BumperEvent& msg); //call back function
void bumpbump::udp_out(const std_msgs::String msg) //call back function
{
  ROS_INFO("Hey Im in the Callback!");  
  

	// Initializing Objects //
	//remaddr is receiving address
	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen=sizeof(remaddr);
	//char *server is place where message is being sent
	char *server = "192.168.0.133";	/* change this to use a different server */
	char buf[BUFLEN];

	/* create a socket */

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//"Send From" aka Client port: 5060
	myaddr.sin_port = htons(5060);
	//myaddr.sin_port = 5060;

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
	{
		perror("bind failed");
		return 0;
	}       

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	/* now let's send the messages */
/*
	for (i=0; i < MSGS; i++) {
		printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
		sprintf(buf, "This is packet %d", i);
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1)
			perror("sendto");
	}
*/
	printf("Sending text packet to %s port %d\n", server, SERVICE_PORT);
	sprintf(buf, "Hello World! I have made it to the other side!");
	if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1)
			perror("sendto");



	close(fd);
	return 0;



  ROS_INFO("end of call back");
}

void bumpbump::pub_vel()
{
  
  //Just makes kobuki drive forward
  
    // convert the double command velo to twist type

    //Instantiate a Twist object
    geometry_msgs::Twist vel;
    vel.linear.x = command_velocity_l;
    pb_velocity.publish(vel);
    ROS_INFO(" Im in pub_vel, going straight ");

    
  
}

// main program
int main(int argc, char** argv)
{

  // initializing ros
  ROS_INFO(" initializing kobuki_bump node");
  ros::init(argc, argv, "kobuki_bump"); //initiating node with unique node name
  bumpbump kobuki_bump;

//ros::AsyncSpinner spinner(2)
//spinner.start();

  ros::Rate loop_rate(10); //send message at 10 hz
  //Just makes kobuki drive forward
  while(ros::ok)
  {

    kobuki_bump.pub_vel(); //call function that sets path to forward
    ROS_INFO("before spinOnce");
    
    //while(ros::ok)
    //{
    ros::spinOnce();  //takes your newest message when bumper pressed
    //sleep(1);
    //}
    
    //ros::spin();
    ROS_INFO("After spinOnce");
    
    ROS_INFO("start sleep");
    loop_rate.sleep();
    ROS_INFO("end sleep");
  }
//ros::waitForShutdown();
}


