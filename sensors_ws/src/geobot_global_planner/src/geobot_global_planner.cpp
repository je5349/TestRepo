#include <pluginlib/class_list_macros.h>
#include <geobot_global_planner/geobot_global_planner.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
 
//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(geobot_global_planner::GlobalPlanner, nav_core::BaseGlobalPlanner)
 
  using namespace std;
 
  //Default Constructor
  namespace geobot_global_planner {
   
    GlobalPlanner::GlobalPlanner (){
   
    }
   
    GlobalPlanner::GlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
      initialize(name, costmap_ros);
    }
   
   
    void GlobalPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
   
    }
   
    bool GlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal,  std::vector<geometry_msgs::PoseStamped>& plan ){
   
       
      //Initialize file to read the global path from.
        int data_row = 0;
        int data_col = 0;
        string data_string;  
        string data_line;
        string filename;
        vector <vector <double> > path, interpath;
        vector <double>  newrow, new_point;

      // Input filename of global path
        cout << "Type in the filename" << endl;
        cin >> filename;

      // Open the file containing the global path
        ifstream fileIN(filename.c_str());
     
      //Check if file is valid
        if (fileIN.fail())
        {
          // if not return the start position as the goal
          cerr << "File cannot be accessed or the filename does not exist" << endl;

          geometry_msgs::PoseStamped new_goal = start;
            
          plan.push_back(new_goal);

          return true;
        }
      

      // If file path is successful, read in the path from the file line by line

        // Inittialize the path with the starting point

        newrow.push_back(start.pose.position.x);
        newrow.push_back(start.pose.position.y);
        path.push_back(newrow);
        newrow.clear();

        while(fileIN.good())
        {
          while(getline(fileIN, data_line))
          {
            istringstream streamdata(data_line);
            //cout << streamdata.str() << endl;
            data_col = 0;
            while(streamdata >> data_string)
            {
              //cout << data_string << endl;
              newrow.push_back(strtod(data_string.c_str(), NULL));
              data_col++;
            }
            path.push_back(newrow);
            newrow.clear();
            data_row++;
          }
        }

        // Close file
        fileIN.close();

    cout << "pre-path size-row------"<< path.size()<< endl;
    cout << "pre-path  size-column------"<< path.at(0).size()<< endl;


        float max_segment_length = 0.5;  // make parameter
        bool max_segment = false;

        // Interpolating between paths greater than max_segment_length threshold

        int step = 1;

        // while(min_path_segment(path) >  min_segment_length)
        while(!max_segment)
        {
           max_segment = true;
          int number_of_longer_segment = 0;

          for (int i = 0; i<path.size()-1; i++)
          {
            // storing previous point
          
              new_point.push_back(path[i][0]);
              new_point.push_back(path[i][1]);
              interpath.push_back(new_point);
              new_point.clear();

              // finding midpoints
            //cout << "norm-----" << sqrt(pow(path[i+1][0]-path[i][0],2) + pow(path[i+1][1]-path[i][1],2) ) << endl;
            if( sqrt(pow(path[i+1][0]-path[i][0],2) + pow(path[i+1][1]-path[i][1],2) ) > max_segment_length)
            {  
              number_of_longer_segment = number_of_longer_segment+1;
              float x = (path[i][0] + path[i+1][0])*0.5;
              float y = path[i][1] + (path[i+1][1] - path[i][1])*0.5;
              step = step+1;
        
              // storing the midpoint
              new_point.push_back(x);
              new_point.push_back(y);
              interpath.push_back(new_point);
              new_point.clear();
              step = step+1;
            }

          } 
          //cout << "Storing last point"<< endl;
          //cout << "no of number_of_longer_segment" << number_of_longer_segment << endl;
            // storing the last point
            new_point.push_back(path[path.size()-1][0]);
            new_point.push_back(path[path.size()-1][1]);
            interpath.push_back(new_point);
            new_point.clear();

            path.clear();
            path = interpath;
            interpath.clear();

            
            if(number_of_longer_segment > 0)
            {
              max_segment = false;
            }


        }

        cout << "post-path size-row------"<< path.size()<< endl;
        cout << "post-path  size-column------"<< path.at(0).size()<< endl;

        // Smoothing the path

        vector <vector <double> > newpath;

        newpath = path;

        float tolerance = 0.00001;
        float change = tolerance; // make parameter
        float alpha = 0.6;
        float beta = 0.1;
        


        while(change >= tolerance)
        {
          change = 0.0;
          for(int i=1;i<path.size()-1; i++)
          {
            for(int j=0;j<path.at(0).size(); j++)
            {
              float init = newpath[i][j];
              newpath[i][j] = newpath[i][j] + alpha*(path[i][j] - newpath[i][j]);
              newpath[i][j] = newpath[i][j] + beta*(newpath[i+1][j] + newpath[i-1][j] - 2*newpath[i][j]);
              change = change + abs(init - newpath[i][j]);

              cout << "change is "<< change << endl;

            }
          }

        }

        path = newpath;
        newpath.clear();


        // Publish out the path

        for (int i=0; i<path.size()-1; i++){

          geometry_msgs::PoseStamped new_goal = goal;
          tf::Quaternion goal_quat = tf::createQuaternionFromYaw(0);
     
           new_goal.pose.position.x = path[i][0];  // Latitude
           new_goal.pose.position.y = path[i][1];  // Longitude

           cout << "x------"<< path[i][0] << "y------" << path[i][1] << endl;
     
           new_goal.pose.orientation.x = goal_quat.x();
           new_goal.pose.orientation.y = goal_quat.y();
           new_goal.pose.orientation.z = goal_quat.z();
           new_goal.pose.orientation.w = goal_quat.w();
     
        plan.push_back(new_goal);
      }



      // plan.push_back(goal); Not needed in this case
     return true;
    }
    };
