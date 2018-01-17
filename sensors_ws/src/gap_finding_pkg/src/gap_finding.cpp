#include <ros/ros.h>
#include <ros/console.h>
#include <sensor_msgs/LaserScan.h>
#include <gap_finding_pkg/Gap.h>
#include <gap_finding_pkg/GapArray.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


using namespace std;


// callback function to receive scan data

class GapFindingRos
{
public:
  GapFindingRos();
  
  void scanMessageReceived(const sensor_msgs::LaserScan& scan);
  
protected:

  ros::Subscriber scanSubscriber_;
  ros::Publisher widest_gapPublisher_;
  ros::Publisher candidate_gapPublisher_;
  ros::NodeHandle nh;

  float robot_halfwidth_with_clearance_; // meters
  float smallest_border_angle_; // rad

  //double previous_scan_range;

};


GapFindingRos::GapFindingRos()
{
  widest_gapPublisher_ = nh.advertise<gap_finding_pkg::Gap>("widest_gap", 20);
  candidate_gapPublisher_ = nh.advertise<gap_finding_pkg::GapArray>("candidate_gaps", 20);
  // nh.subscribe(topic_name,queue_size, pointer_to_callback_function);
  scanSubscriber_ = nh.subscribe("scan",1000, &GapFindingRos::scanMessageReceived,this);
  robot_halfwidth_with_clearance_ = 0.5;
  smallest_border_angle_ = 0.0523599;
}


void GapFindingRos::scanMessageReceived(const sensor_msgs::LaserScan& scan)
{

  float obstacle_threshold = 2.0; // meters add as a parameter
  float previous_scan_range = obstacle_threshold - 0.01; // use this as the right range border of angle if the gap start at the scan start point
  float previous_scan_angle = scan.angle_min;
  float angle_increment = scan.angle_increment;
  int size = scan.ranges.size();
  bool right_border_exist = false;
  float present_scan_range;
  float present_scan_angle;
  int gap_increment = 0;
  float dist_right;
  float angle_right;
  float dist_left;
  float angle_left;
  vector <vector <double> > array_of_gaps;
  vector <double>  newgap;
  int valid_scan_startpoint = 0;    // because the first 43 scan points are always 0.019m
  float gapend_default_range = 3.0;  // meters // parameter // scan max range or obstacle threshold

  //ROS_INFO(" Start");
  // check all scan points for gaps
  for(int i = valid_scan_startpoint; i<size;  ++i) 
  {
    present_scan_range = scan.ranges[i];
    present_scan_angle = scan.angle_min + angle_increment*i;

    if((present_scan_range >= obstacle_threshold) && (previous_scan_range < obstacle_threshold) && (right_border_exist == false))
    {
      // right border of gap
      if(i == valid_scan_startpoint) // // use this as the right range border of angle if the gap start at the scan start point
      {
        newgap.push_back(gapend_default_range); 
      }
      else
      {
        newgap.push_back(previous_scan_range);
      }

      previous_scan_angle = scan.angle_min + angle_increment*(i-1);
      newgap.push_back(previous_scan_angle);

      //ROS_INFO(" RT");
      right_border_exist = true; // starting the gap 
    }

    if((present_scan_range < obstacle_threshold) && (previous_scan_range >= obstacle_threshold) && (right_border_exist == true))
    {
                 
        // left border of gap
        newgap.push_back(present_scan_range);
        newgap.push_back(present_scan_angle);
        //ROS_INFO("LT ");
        array_of_gaps.push_back(newgap);
        newgap.clear();

        right_border_exist = false; //closing the gap

    }

    if((i == size-1) && (right_border_exist == true))
    {
      // if it is the last scan point
      // left border of gap
      newgap.push_back(gapend_default_range); 
      newgap.push_back(scan.angle_max);
      //ROS_INFO("LLT ");
      array_of_gaps.push_back(newgap);
      newgap.clear();

      right_border_exist = false; //closing the gap
    }

    
    previous_scan_range = present_scan_range;
    //previous_scan_angle = present_scan_angle;

  }



  //ROS_INFO(" end");

  //ROS_INFO("data size-row------" << array_of_gaps.size());
  //ROS_INFO("data size-column------" << array_of_gaps.at(0).size());

  gap_finding_pkg::Gap widest_gap;
  gap_finding_pkg::GapArray candidate_gaps;
  // find gaps; create a gap message and store the gap there
  
  // initializing gap parameters meters and radians
  ros::Time gap_time = ros::Time::now();


  // initializing widest gap field
  widest_gap.header = scan.header;
  widest_gap.header.stamp = gap_time;
  widest_gap.header.frame_id = "gap";
  widest_gap.gap_width =  0.0; 
  widest_gap.dist_right = 0.0;
  widest_gap.dist_left = 0.0;
  widest_gap.angle_right = 0.0;
  widest_gap.angle_left = 0.0;

  // initializing array of gaps field
  candidate_gaps.header = scan.header;
  candidate_gaps.header.stamp = gap_time;
  candidate_gaps.header.frame_id = "gap";

  int seq_num = 1;

  if(!array_of_gaps.empty()) // array_of_gaps is not empty
  {
      int rowsize = array_of_gaps.size();
      int colsize = array_of_gaps.at(0).size();
      float previous_gap_width = robot_halfwidth_with_clearance_ * 2;   // defining the characteristic length of the robot
      float gap_width_threshold = robot_halfwidth_with_clearance_ * 2;   // defining the characteristic length of the robot
      float gap_width;

      //ROS_INFO(" point1");

      for (int i = 0; i<rowsize; ++i)
      {
        dist_right = array_of_gaps[i][0];
        angle_right = array_of_gaps[i][1];
        dist_left = array_of_gaps[i][2];
        angle_left = array_of_gaps[i][3];
        //ROS_INFO(" point2");
        gap_width = sqrt(dist_right*dist_right + dist_left*dist_left - 2*dist_right*dist_left*cos(angle_left - angle_right));

        if (gap_width > previous_gap_width)  // && (abs(angle_right - angle_left) > ) )  finding the widest gap
        {
          previous_gap_width = gap_width;
          widest_gap.gap_width =  gap_width; 
          widest_gap.dist_right = array_of_gaps[i][0];
          widest_gap.angle_right = array_of_gaps[i][1];
          widest_gap.dist_left = array_of_gaps[i][2];
          widest_gap.angle_left = array_of_gaps[i][3];

        }

        if ((gap_width > gap_width_threshold)  && (abs(angle_right - angle_left) > smallest_border_angle_) )  //finding the candidate threshold gaps
        {

          gap_finding_pkg::Gap gap;
	  gap.header.seq = seq_num++;
          gap.gap_width =  gap_width; 
          gap.dist_right = array_of_gaps[i][0];
          gap.angle_right = array_of_gaps[i][1];
          gap.dist_left = array_of_gaps[i][2];
          gap.angle_left = array_of_gaps[i][3];

          candidate_gaps.gaps.push_back(gap);

        }


      }
      //ROS_INFO(" point3");
      array_of_gaps.clear();
  }
  widest_gapPublisher_.publish(widest_gap);
  candidate_gapPublisher_.publish(candidate_gaps);

  //ROS_INFO(" point4");
}






// main program
int main(int argc, char** argv)
{
  // initializing ros
  ROS_INFO(" initializing gap finding node to detrmine candidtae gaps and the widest gap in the environment");
  ros::init(argc, argv, "gap_finding_node");

  GapFindingRos gf;
 
  ros::spin();

}
