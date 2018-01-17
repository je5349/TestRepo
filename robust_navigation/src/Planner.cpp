#include <ros/ros.h>
#include <robust_navigation/Planner.h>
#include <iostream>
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "message_filters/subscriber.h"
#include <tf/transform_broadcaster.h>
#include <algorithm>
#include <vector>
#include <boost/bind.hpp>
#include <geometry_msgs/Point.h>
#include "nav_msgs/MapMetaData.h"
#include <math.h>
#include <stdlib.h>


using namespace std; // avoid using "using namespace" in future programs

pathplan::pathplan()
{
  ROS_INFO("A* Path planner starting");
  goal_.x = 20; // get this param and store it in memory 
  goal_.y = 0;
  pathplan::init();
}


void pathplan::init(){
  sub_= node_.subscribe("test_map", 1, &pathplan::Astar, this); //subscribe to occupancy grid test_map
}


void pathplan::Astar(const nav_msgs::OccupancyGrid test_map_){ // need to input goal state in x,y terms //need an update parameter
    //initialize nav_msgs::Path
    path = node_.advertise<nav_msgs::Path>("path",1,true);

    //initialize Astar nav_msg path
    Astar_path_ = new nav_msgs::Path;
    //Astar_path_->header.seq=1;
    Astar_path_->header.stamp=ros::Time::now();
    Astar_path_->header.frame_id=test_map_.header.frame_id;

    if (!acquire_robotpose()){
        ROS_INFO("NO ROBOT POSE AVAILABLE");
        return; 
    }    
    ROS_INFO("Final Goal: x=%f, y=%f", goal_.x,goal_.y);

    //Map parameters
    float origin_x = pose.x;
    float origin_y = pose.y;
    int width = test_map_.info.width;
    int height = test_map_.info.height;
    float resolution = test_map_.info.resolution;

    //initialize hueristic_cost, movement, movement_cost, possible_paths, openset and closet used to calculate A* Path

    poss_path_ = new vector<vector<int> >;
    openset = new vector<vector<int> >;
    movement_cost.resize(height , vector<float> (width,0));
    movement.resize(height , vector<int> (width,10));
    hueristic_cost_.resize(height , vector<float> (width,0));

    pathplan::poss_path(); //create possible movement array i.e (1,0),(0,1),(1,1),(-1,-1) etc..

    pathplan::hueristic_cost(test_map_);//euclidean distance to goal (calculates an intermediate goal)
    
    vector<int> origin;
    origin.push_back(0);
    origin.push_back(0);
    openset->push_back(origin); //add the origin
    
    ROS_INFO("Robot Position: x=%f, y=%f",pose.x,pose.y); // Origin corresponds to odometry position of the robot

    // for(int i=0;i<test_map_.info.width;i++){
    //     for(int j=0;j<test_map_.info.height;j++){
    //         movement[i][j]=10;
    //         movement_cost[i][j]=0;
    //     }
    // }

    //movement[0][0]=0;
    movement.at(0).at(0) = 0;

    bool goal_reached=0;
    int temp_iterator_;
    float total_cost_;
    int x_1_;
    int y_1_;

    while(goal_reached==0){
        float temp_cost_=10000000;
        float Best_hueristic_cost_=1000000;

        if (openset->size()==0){
            ROS_INFO("NO PATH TO FINAL OR INTERMEDIATE GOAL!");
            return;
        }
        //ROS_INFO("EXPLORING OPENSET");
        for(int i=0;i<openset->size();i++){
            x_1_=(*openset)[i][0];
            y_1_=(*openset)[i][1];
            //ROS_INFO("EXPLORING %d IN THE OPENSET", i);
            if (abs(x_1_- int_goal_.x) < 0.2 && abs(y_1_ - int_goal_.y) < 0.2){ //checking if we have reached intermediate goal point
                if(temp_step.size()>=1){
                    temp_step.erase(temp_step.begin()+0);
                }
                goal_reached = 1;
                vector<int> pushback;
                pushback.push_back(int_goal_.x);
                pushback.push_back(int_goal_.y);
                temp_step.push_back(pushback);
                temp_iterator_=i;

                if (abs(x_1_ - origin_x) < 0.2 && abs(y_1_ + origin_y)<0.2){
                  ROS_INFO("FINAL GOAL REACHED! NEED ANOTHER GOAL");
                }
                else{
                  ROS_INFO("PATH TO INTERMEDIATE GOAL CALCULATED!");
                }
                break;

            }

            total_cost_=movement_cost.at(x_1_+width/2).at(y_1_+height/2)+hueristic_cost_.at(x_1_+width/2).at(y_1_+height/2);//movement+grid cost
            //ROS_INFO("Total_cost=%f, x=%d, y=%d",total_cost_,x_1_,y_1_);

            if ( (total_cost_ == temp_cost_ && hueristic_cost_.at(x_1_+width/2).at(y_1_+height/2) <= Best_hueristic_cost_) || (total_cost_<temp_cost_ && goal_reached==0)) {
                    if(temp_step.size()>=1){
                        temp_step.erase(temp_step.begin()+0);
                    }
                    temp_iterator_=i;
                    temp_cost_ = total_cost_;
                    Best_hueristic_cost_ = hueristic_cost_.at(x_1_+width/2).at(y_1_+height/2);
                    vector<int> pushback;
                    pushback.push_back(x_1_);
                    pushback.push_back(y_1_);
                    temp_step.push_back(pushback);
                    //ROS_INFO("ENTERD");
                }
        }
        //ROS_INFO("SELECTED: Total_cost=%f, x=%d, y=%d",total_cost_,temp_step[0][0],temp_step[0][1]);
        openset->erase(openset->begin()+temp_iterator_); //need to remove the step being expanded upon
        expand(temp_step[0], test_map_); // expand on all possible steps and store them in the openset vector
        closedset.push_back(temp_step[0]); // add to optimal path
        temp_step.clear();
        }
        
        int i = int_goal_.x;
        int j = int_goal_.y;
        //ROS_INFO("Goal: x=%d y=%d",i,j);
        vector<int> pushback;
        pushback.push_back(i);
        pushback.push_back(j);
        optimal_path.push_back(pushback);
        pushback.clear();
        bool reached=0;

        //back track to the origin 
        while(reached==0){ 
            int move_1 = movement.at(i+width/2).at(j+height/2);
            //ROS_INFO("Movement: %d" ,movement[i][j]);
            int n = 45*move_1;
            float x = cos(n*M_PI/180);
            float y = sin(n*M_PI/180);
            if (fabs(x) == float(cos(45*M_PI/180)))
            {
                x = x / cos(45*M_PI/180);
                y = y / sin(45*M_PI/180);
            }
            int i1 = i - int(x);
            int j1 = j - int(y);
            //ROS_INFO("STEP:x=%d, y=%d, MOVE: x=%f, y=%f", i,j,x,y);
            i = i1;
            j = j1;
            if((i==0) && (j==0)){
                reached = 1;
            }
            pushback.push_back(i);
            pushback.push_back(j);
            optimal_path.push_back(pushback);
            pushback.clear();
        }

        Astar_path_->poses.resize(optimal_path.size());

        for(int i=optimal_path.size()-1;i>=0;i--){
          //(*Astar_path_).poses[optimal_path.size()-1-i].header.seq=i;
          (*Astar_path_).poses[optimal_path.size()-1-i].header.stamp=ros::Time::now();
          (*Astar_path_).poses[optimal_path.size()-1-i].header.frame_id="odom";
          (*Astar_path_).poses[optimal_path.size()-1-i].pose.position.x=optimal_path[i][0]*resolution+origin_x;
          (*Astar_path_).poses[optimal_path.size()-1-i].pose.position.y=optimal_path[i][1]*resolution+origin_y;
          //optimal_path[i].clear();
          ROS_INFO("OPTIMAL PATH: x=%f, y=%f", optimal_path[i][0]*resolution+origin_x, optimal_path[i][1]*resolution+origin_y);
        }

        path.publish(*Astar_path_);

        optimal_path.clear();

        movement.clear();
        hueristic_cost_.clear();
        delete poss_path_;
        delete openset;
        delete Astar_path_;
}

void pathplan::hueristic_cost(const nav_msgs::OccupancyGrid test_map_){ //publishes goal
  float origin_x = pose.x;
  float origin_y = pose.y;
  int width = test_map_.info.width;
  int height = test_map_.info.height;
  float resolution = test_map_.info.resolution;

  float best_hueristic_cost_ = sqrt(pow(origin_x-goal_.x,2) + pow(origin_y-goal_.y,2));
  
  // if ( abs(goal_.x-origin_x)  > width/2 || abs(goal_.y-origin_y) > height/2){ // if the goal point is outside the map then we need to find intermediate points 
    for (int i=0;i<(width)*(height);i++) // calculate euclidean distance // 100 = map_width * map_height
    {

      float x = i%(width) - width/2;
      float y = i/(height) - height/2;

      float cost =  sqrt(pow((x+origin_x)-goal_.x,2) + pow((y+origin_y)-goal_.y,2));
      hueristic_cost_.at(i%height).at(int(i/width)) = cost; // euclidean + occupied cost
    
      
      if (cost < best_hueristic_cost_ && test_map_.data[i] != 100 && x > -width/2 && x<width/2 && y > -width/2 && y<height/2){
          int_goal_.x = x;
          int_goal_.y = y;
          best_hueristic_cost_= cost;
          //ROS_INFO("NOW GOAL IS: x = %f y=%f",x,y);
      }
    }
  ROS_INFO("Intermediate Goal: x=%f, y=%f", int_goal_.x+origin_x,int_goal_.y+origin_y);
}


void pathplan::expand(vector<int> &step, const nav_msgs::OccupancyGrid test_map_){
    int origin_x = pose.x;
    int origin_y = pose.y;
    int width = test_map_.info.width;
    int height = test_map_.info.height;
    float resolution = test_map_.info.resolution;

    vector<int> b;
    //ROS_INFO("possible paths: %d", poss_path_->size());
    for (int i=0;i<poss_path_->size();i++){
        int x = step[0]+ (*poss_path_)[i][0];
        int y = step[1]+ (*poss_path_)[i][1];
        b.push_back(x);
        b.push_back(y);

        if (x > -width/2 && x<width/2 && y > -width/2 && y<height/2){ //Only expand on nodes inside the domain and unoccupied
            if (test_map_.data[(x + width/2) + width*(y+height/2)] !=100 && movement.at(x+width/2).at(y+width/2)==10){ //Only expand on nodes that are not explored
                openset->push_back(b); // add the expanded node to the openset 
                movement.at(x+width/2).at(y+height/2)=i; //capture movement
                	// add cost of the expanded cell to the movement_cost 2D array 
                    if(i%2 == 1){
                        float diagonal_cost_=pathplan::diagonalcost(x,y,i, test_map_);
                        movement_cost.at(x+width/2).at(y+height/2)=movement_cost.at(step[0]+width/2).at(step[1]+height/2) +  14.0 + diagonal_cost_; //make these costs variable
                        //ROS_INFO("Expanded: x=%d, y=%d",x,y);
                    }
                    else{
                        movement_cost.at(x+width/2).at(y+height/2)=movement_cost.at(step[0]+width/2).at(step[1]+height/2) +  10.0; //make these costs variable
                        //ROS_INFO("Expanded: x=%d, y=%d",x,y);
                    }
                    
            }
        }
        b.clear();
    }
}


float pathplan::diagonalcost(int &x,int &y, int &angle, const nav_msgs::OccupancyGrid test_map_){
    float n=90*(angle-1);
    float x_1= 0.0;
    float y_1 = 0.0;
    float diagonal_cost=0.0;

    int width = test_map_.info.width;
    int height = test_map_.info.height;
    for(int i=0;i<2;i++){
        x_1 = cos(n*M_PI/180);
        y_1 = sin(n*M_PI/180);

        if(int(x_1+x)> -width/2 && int(x_1+x)< width/2 && int(y_1+y)> height/2 && int(y_1+y)< height/2){
            x_1 = x_1 + x;
            y_1 = y_1 + y;
            if(test_map_.data[int((x_1+width/2)+width*(y_1+height/2))]==100.0){
                diagonal_cost = diagonal_cost + 50.0;
            }
        }
        n = n + 90.0;
    }
    return diagonal_cost;
}

void pathplan::poss_path(){
        vector<int> pushback;
        int n;
        float x,y;
        for (int i=0;i<=7;i++){
            n = 45*i;
            x = cos(n*M_PI/180);
            y = sin(n*M_PI/180);
            if (fabs(x) == float(cos(45*M_PI/180)))
            {
                x = x / cos(45*M_PI/180);
                y = y / sin(45*M_PI/180);
            }
            pushback.push_back(x);
            pushback.push_back(y);
            poss_path_->push_back(pushback);
            pushback.clear();
        }
}

bool pathplan::acquire_robotpose()
{
  tf::StampedTransform odom_base_transform;
  tf::Matrix3x3 mat;
  double roll;
  double pitch;
  double yaw;

  
  try{
  listener.waitForTransform("/odom", "/base_link", ros::Time(0), ros::Duration(2.0));
  listener.lookupTransform("/odom","/base_link", ros::Time(0), odom_base_transform);  
  }
  catch(tf::TransformException &ex)
  {
    ROS_ERROR("%s",ex.what());
    return false;
  }
  

  mat.setRotation(odom_base_transform.getRotation());
  mat.getRPY(roll, pitch, yaw);

  pose.x = odom_base_transform.getOrigin().getX();
  pose.y = odom_base_transform.getOrigin().getY();
  pose.heading = yaw;

  return true;
}




int main(int argc, char ** argv)
{
  ros::init(argc, argv, "planner_node");
  pathplan pp;
  
  ros::spin();

  return(0);
}



