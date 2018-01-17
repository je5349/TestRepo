#include <ros/ros.h>
#include "robust_navigation/path_planning.h"
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


using namespace std; // avoid using "using namespace" in future programs

pathplan::pathplan()
{
  ROS_INFO("Path planning starting");
  float origin_x = -0.5;
  float origin_y = -0.5;
  int width = 10;
  int height = 10;
  int resolution = 1;
  //this has to be set using a launch file or terminal command!
  goal_.x = 100;
  goal_.y = 100;
  pathplan::testmap(origin_x,origin_y,width,height,resolution); // create map (10x10) and 1m cell dimension
}


void pathplan::testmap(float &origin_x,float &origin_y,int &width, int &height, int &resolution){ // might need to put a pose origin{
   test_map = node_.advertise<nav_msgs::OccupancyGrid>("test_map",1,true);
   test_map_ = new nav_msgs::OccupancyGrid;
   test_map_->header.seq=1; //this might need to be updated depending on how many time the occupancy grid is called
   test_map_->header.stamp=ros::Time::now();
   test_map_->header.frame_id="map"; //will be use robot odometry frame

   test_map_->info.map_load_time=ros::Time::now();
   test_map_->info.width = width;
   test_map_->info.height = height;
   test_map_->info.resolution = resolution; // 1 m per cell
   test_map_->info.origin.position.x = origin_x;
   test_map_->info.origin.position.y = origin_y;

  int p[width*height];

  for (int i=0;i<100;i++){
	if(i==99 || i==0){
		p[i] = 0;
	}
	else if (i%7==0 || i%6==0||i%8==0){
		p[i] =100;
	}
	else{
        p[i] = 0;
 	}
  }
  vector<signed char> a(p,p+100);
  test_map_->data = a;
  test_map.publish(*test_map_);
  ROS_INFO("Occupany map produced");
  pathplan::init();

}

void pathplan::init(){
  sub_= node_.subscribe("test_map", 1, &pathplan::Astar, this); //subscribe to occupancy grid test_map
}



void pathplan::Astar(const nav_msgs::OccupancyGrid& test_map_){ // need to input goal state in x,y terms //need an update parameter
    //initialize nav_msgs::Path

    path = node_.advertise<nav_msgs::Path>("path",1,true);

    Astar_path_ = new nav_msgs::Path;
    Astar_path_->header.seq=1;
    Astar_path_->header.stamp=ros::Time::now();
    Astar_path_->header.frame_id="map";

    hueristic_cost_ = new vector<float>;
    poss_path_ = new vector<vector<int> >;
    openset = new vector<vector<int> >;
    int_goal_.x=goal_.x;
    int_goal_.y=goal_.y;
    pathplan::poss_path(); //create possible movement array i.e (1,0),(0,1),(1,1),(-1,-1) etc..
    pathplan::hueristic_cost(test_map_);//euclidean distance to goal

    vector<int> origin;

    origin.push_back(test_map_.info.origin.position.x);
    origin.push_back(test_map_.info.origin.position.y);
    openset->push_back(origin); //add the origin

    for(int i=0;i<test_map_.info.width;i++){
        for(int j=0;j<test_map_.info.height;j++){
            movement[i][j]=10;
            movement_cost[i][j]=0;
        }
    }

    movement[0][0]=0;

    bool goal_reached=0;
    int origin_x = test_map_.info.origin.position.x;
    int origin_y = test_map_.info.origin.position.y;
    int temp_iterator_;
    float total_cost_;
    int x_1_;
    int y_1_;

    while(goal_reached==0){
        float temp_cost_=100000000000;
        float Best_hueristic_cost_=10000000000;
        if (openset->size()==0){
            ROS_INFO("NO PATH TO FINAL GOAL OR INTERMEDIATE GOAL!");
            return;
        }
        for(int i=0;i<openset->size();i++){
            x_1_=(*openset)[i][0];
            y_1_=(*openset)[i][1];
            if (x_1_ == int_goal_.x && y_1_ == int_goal_.y){ //checking if we have reached intermediate goal point
                if(temp_step.size()>=1){
                    temp_step.erase(temp_step.begin()+0);
                }
                goal_reached = 1;
                vector<int> pushback;
                pushback.push_back(int_goal_.x);
                pushback.push_back(int_goal_.y);
                temp_step.push_back(pushback);
                temp_iterator_=i;
                ROS_INFO("INTERMEDIATE GOAL REACHED!");
                break;
            }

            total_cost_=movement_cost[x_1_][y_1_]+(*hueristic_cost_)[10*(y_1_-origin_y)+(x_1_-origin_x)];//movement+grid cost
            //ROS_INFO("Total_cost=%f, x=%d, y=%d",total_cost_,x_1_,y_1_);
            if ( (total_cost_ == temp_cost_ && (*hueristic_cost_)[10*(y_1_-origin_y)+(x_1_-origin_x)] <= Best_hueristic_cost_) || (total_cost_<temp_cost_ && goal_reached==0)) {
                    if(temp_step.size()>=1){
                        temp_step.erase(temp_step.begin()+0);
                    }
                    temp_iterator_=i;
                    temp_cost_ = total_cost_;
                    Best_hueristic_cost_ = (*hueristic_cost_)[10*(y_1_-origin_y)+(x_1_-origin_x)];
                    vector<int> pushback;
                    pushback.push_back(x_1_);
                    pushback.push_back(y_1_);
                    temp_step.push_back(pushback);
                    //ROS_INFO("total: %f, temp_cost: %f, Best_H_cost: %f, Current_H_cost: %f x= %d, y=%d", total_cost_, temp_cost_, Best_hueristic_cost_, (*hueristic_cost_)[10*(y_1_-origin_y)+(x_1_-origin_x)], x_1_,y_1_);
            }
        }
        //ROS_INFO("SELECTED: Total_cost=%f, x=%d, y=%d",total_cost_,temp_step[0][0],temp_step[0][1]);
        openset->erase(openset->begin()+temp_iterator_); //need to remove the step being expanded upon
        expand(temp_step[0]); // expand on all possible steps and store them in the openset vector
        closedset.push_back(temp_step[0]); // add to optimal path
        temp_step.clear();
        }

        int i = int_goal_.x;
        int j = int_goal_.y;
        vector<int> pushback;
        pushback.push_back(i);
        pushback.push_back(j);
        optimal_path.push_back(pushback);
        pushback.clear();
        bool reached=0;
        while(reached==0){
            int move_1 = movement[i][j];
            ROS_INFO("Movement: %d",movement[i][j]);
            int n = 45*move_1;
            float x = cos(n*M_PI/180);
            float y = sin(n*M_PI/180);
            if (fabs(x) == float(cos(45*M_PI/180)))
            {
                x = x / cos(45*M_PI/180);
                y = y / sin(45*M_PI/180);
            }

            int i1 = i - x;
            int j1 = j - y;
            ROS_INFO("x=%d, y=%d", i,j);
            i = i1;
            j = j1;
            if((i==0) && (j==0)){
                reached = 1;
            }
            pushback.push_back(i);
            pushback.push_back(j);
            optimal_path.push_back(pushback);
            pushback.clear();
            ros::Duration(0.5).sleep();
        }

//        pushback.push_back(0);
//        pushback.push_back(0);
//        optimal_path.push_back(pushback);
//        pushback.clear();

        Astar_path_->poses.resize(optimal_path.size());

        for(int i=optimal_path.size()-1;i>=0;i--){
          (*Astar_path_).poses[optimal_path.size()-1-i].header.seq=i;
          (*Astar_path_).poses[optimal_path.size()-1-i].header.stamp=ros::Time::now();
          (*Astar_path_).poses[optimal_path.size()-1-i].header.frame_id="map";
          (*Astar_path_).poses[optimal_path.size()-1-i].pose.position.x=optimal_path[i][0];
          (*Astar_path_).poses[optimal_path.size()-1-i].pose.position.y=optimal_path[i][1];
        }
        path.publish(*Astar_path_);

        delete hueristic_cost_;
        delete poss_path_;
        delete openset;
        delete Astar_path_;
}


void pathplan::hueristic_cost(const nav_msgs::OccupancyGrid& test_map_){ //publishes goal
  float origin_x = test_map_.info.origin.position.x;
  float origin_y = test_map_.info.origin.position.y;
  int width = test_map_.info.width;
  int height = test_map_.info.height;
  float hueristic_cost_test_= sqrt(pow(origin_x-goal_.x,2) + pow(origin_y-goal_.y,2));

  for (int i=0;i<100;i++) // calculate euclidean distance // 100 = map_width * map_height
  {
    int x = origin_x+i%10;
    int y = origin_y+i/10;
    float cost = sqrt(pow(x-goal_.x,2) + pow(y-goal_.y,2)); // euclidean + occupied cost
    hueristic_cost_->push_back(cost);
    if (i!=0 && (*hueristic_cost_)[i] < hueristic_cost_test_ && goal_.x>width && goal_.y>height && test_map_.data[10*(y-origin_y)+(x-origin_x)]!=100){
        int_goal_.x = x;
        int_goal_.y = y;
        hueristic_cost_test_ =(*hueristic_cost_)[i];
    }
  }
  ROS_INFO("Intermediate Goal: x=%f, y=%f", int_goal_.x,int_goal_.y);
}


void pathplan::expand(vector<int> &step){
    int origin_x = test_map_->info.origin.position.x;
    int origin_y = test_map_->info.origin.position.y;
    vector<int> b;
    for (int i=0;i<poss_path_->size();i++){
        int x = step[0]+ (*poss_path_)[i][0];
        int y = step[1]+ (*poss_path_)[i][1];
        b.push_back(x);
        b.push_back(y);
        if (test_map_->data[10*(y-origin_y)+(x-origin_x)] !=100 && x >= 0 && x<10 && y >=0 && y<10){ //Only expand on nodes inside the domain and unoccupied
            if (movement[x][y]==10){ //Only expand on nodes that are not explored
                openset->push_back(b);
                movement[x][y]=i; //capture movements
                int diagonal_cost_=pathplan::diagonalcost(x,y);
                    if(i%2 == 1){
                        movement_cost[x][y]=movement_cost[step[0]][step[1]] +  1400+ diagonal_cost_; //make these costs variable
                    }
                    else{
                        movement_cost[x][y]=movement_cost[step[0]][step[1]] + 10 + diagonal_cost_; //make these costs variable
                    }
                    //ROS_INFO("Expaneded: x=%d, y=%d",x,y);
            }
        }
        b.clear();
    }
}


int pathplan::diagonalcost(int &x,int &y){
    int n;
    float x_1,y_1;
    float diagonal_cost;
    int origin_x = test_map_->info.origin.position.x;
    int origin_y = test_map_->info.origin.position.y;
    for(int i=0;i<4;i++){
        n = 90*i;
        x_1 = cos(n*M_PI/180);
        y_1 = sin(n*M_PI/180);
        if((x_1+x)>=0 && (x_1+x)<test_map_->info.width && (y_1+y)>=0 && (y_1+y)<test_map_->info.height){
            x_1 = x_1 + x;
            y_1 = y_1 + y;
            if(test_map_->data[10*(y_1-origin_y)+(x_1-origin_x)]==100){
                diagonal_cost = diagonal_cost + 2500;
            }
        }
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



int main(int argc, char ** argv)
{
  ros::init(argc, argv, "planner_node");
  pathplan pp;
  
  ros::spin();

  return(0);
}
