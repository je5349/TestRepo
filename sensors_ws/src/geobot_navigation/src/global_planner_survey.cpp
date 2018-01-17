#include <global_planner_survey.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <tf/tf.h>

#include <tf/LinearMath/Transform.h>
#include <tf/LinearMath/Vector3.h>



// Execute when a service prompts to move to a goal
// 

 
  using namespace std;
 
  
  namespace geobot_global_planner {

//Default Constructor
  	GlobalPlannerUtil::GlobalPlannerUtil()
  	{
  		 // define parameters here
  		 makeplan_ =  nh.advertiseService("makeplan", &GlobalPlannerUtil::makePlan, this);
  		 planPublisher_ = nh.advertise<nav_msgs::Path>("global_path", 20);
       trajectory_filepath_world_ = "/home/blaster-ws/ros_ws/src/geobot_gui/src/coordinates.coord";
       utmZone = "13S";
   
    }

   
    bool GlobalPlannerUtil::makePlan(geobot_navigation::GetPlan::Request &req, geobot_navigation::GetPlan::Response &resp)
    {

      // call the Pathplanner run to generate the message
      // read in the path message and smoothing path
      // then publish the smoothed path

        if(path_planner_obj.run())
        {
              path_planner_obj.corners.clear(); // clearing previous read boundaries
              vector <vector <double> > path;
              vector <double>   new_point;
              nav_msgs::Path path2publish;
              geometry_msgs::PoseStamped new_goal = req.start;
              resp.plan.push_back(new_goal);



              

                for (int i = 0; i<path_planner_obj.path.size()-1; i++)
                {
                  // transfering points from the planner object

                
                    new_point.push_back(path_planner_obj.path[i][0]);
                    new_point.push_back(path_planner_obj.path[i][1]);
                    path.push_back(new_point);
                    new_point.clear();

                }

                path_planner_obj.path.clear(); // clearing previous paths

              

              // Smoothing the path

              vector <vector <double> > newpath;

              newpath = path;

              float tolerance = 0.000001;
              float diff_change = tolerance*100; // make parameter
              float previous_change, change;
              float alpha = 0.6;
              float beta = 0.2;
              


              while(diff_change >= tolerance)
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

                    

                  }

                }


                //cout << "change is "<< change << endl;

                diff_change = abs(previous_change - change);
                previous_change = change;

              }
              

              path = newpath;
              newpath.clear();



              //Listen for the transorm from odom_utm so that paths can be displayed on the map for visualization
              tf::StampedTransform utm_odom_transform;
              tf::Transform odom_Path;
              tf::Transform transform2utm;
              bool obtained_transform2utm = false;
              std::ofstream fileOUT;
              string data_string;
              double gpr_x;
              double gpr_y;
              double gpr_latitude;
              double gpr_longitude;

              try
              {
                listener.waitForTransform("utm","odom", ros::Time(0), ros::Duration(1.0));
                listener.lookupTransform("utm", "odom", ros::Time(0), utm_odom_transform); 
                obtained_transform2utm = true; 
              }
              catch(tf::TransformException &ex)
              {
                 ROS_ERROR("%s",ex.what());
                 
              }

              //Opening output file that geobot_gui shows on the map
              fileOUT.open(trajectory_filepath_world_.c_str(), std::ofstream::out | std::ofstream::trunc);
              fileOUT.precision(14);

              // Publish out the path

              for (int i=0; i<path.size()-1; i++)
              {

                geometry_msgs::PoseStamped new_goal = req.goal;
                tf::Quaternion goal_quat = tf::createQuaternionFromYaw(0);
           
                 new_goal.pose.position.x = path[i][0];  // Latitude
                 new_goal.pose.position.y = path[i][1];  // Longitude

                 if(obtained_transform2utm)
                 {
                    // convert to longitude and latitude
                    odom_Path.setOrigin(tf::Vector3(path[i][0], path[i][1], 0.0));  // Easting, Northing, Altitude
                    transform2utm.mult(utm_odom_transform, odom_Path);
                    gpr_x = transform2utm.getOrigin().getX();
                    gpr_y = transform2utm.getOrigin().getY();
                    RobotLocalization::NavsatConversions::UTMtoLL(gpr_y, gpr_x, utmZone, gpr_latitude, gpr_longitude);

                    fileOUT << gpr_longitude << "\t" << gpr_latitude << endl;
                 }

                 cout << "x------"<< path[i][0] << "y------" << path[i][1] << endl;
           
                 new_goal.pose.orientation.x = goal_quat.x();
                 new_goal.pose.orientation.y = goal_quat.y();
                 new_goal.pose.orientation.z = goal_quat.z();
                 new_goal.pose.orientation.w = goal_quat.w();
           
                resp.plan.push_back(new_goal);
              }

              path2publish.poses = resp.plan;
    
              path2publish.header.seq = 1;
              path2publish.header.stamp = ros::Time::now();
              path2publish.header.frame_id = "odom";
            
              planPublisher_.publish(path2publish);
            



/*
              nav_msgs::Path path2publish;
              path2publish = path_planner_obj.path_msg;
              planPublisher_.publish(path2publish);
      */
              fileOUT.close();
      
            return true;
        }
        else
        {
          std::cout<<"\nThe path planning process failed...\n"
             <<std::endl;
        }






      /*
       
      //Initialize file to read the global path from.
        int data_row = 0;
        int data_col = 0;
        string data_string;  
        string data_line, frameid_data;
        string filename;
        vector <vector <double> > path, interpath;
        vector <double>  newrow, new_point;
        nav_msgs::Path path2publish;

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

          geometry_msgs::PoseStamped new_goal = req.start;
            
          resp.plan.push_back(new_goal);

          return false;
        }
      

      // If file path is successful, read in the path from the file line by line

        // Inittialize the path with the starting point assuming in odom frame
        
        //newrow.push_back(req.start.pose.position.x);
        //newrow.push_back(req.start.pose.position.y);

        newrow.push_back(0.0);
        newrow.push_back(0.0);

        path.push_back(newrow);
        newrow.clear();

        

      // Check for the frame of the path in the first line
        getline(fileIN, frameid_data);
        string frame_id;
     
        if(frameid_data == "odom")
        {
          frame_id = frameid_data;
        }
        else if(frameid_data == "utm")
        {
          frame_id = frameid_data;
        }
        else
        {
          cout << "Define the frame of the path in the first line" << endl;
          return false;
        }

        cout << "frameid_data-----"<< frameid_data<< endl;


       

        // Read the remaining path of the file line by line
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
            cout<<"newrow[0]_____"<< newrow[0] <<" newrow[1]_____"<< newrow[1]<< endl;
            newrow.clear();
            data_row++;
          }
        }



        // Close file
        fileIN.close();


        cout << "pre-path size-row------"<< path.size()<< endl;
        cout << "pre-path  size-column------"<< path.at(0).size()<< endl;


        // if file is in the utm frame, convert into odom frame ignoring the starting point

        if(frame_id == "utm")
        {
          tf::StampedTransform odom_utm_transform;
          tf::Transform Utm_Path;
          tf::Transform transformed2odom;

          try{
              listener.lookupTransform("odom","utm", ros::Time(0), odom_utm_transform);  
              }
              catch(tf::TransformException &ex)
              {
                ROS_ERROR("%s",ex.what());
                return false;
              }

         for (int i = 1; i<path.size(); i++) // Ignore starting point
         {
            Utm_Path.setOrigin(tf::Vector3(path[i][0], path[i][1], 0.0));  // Easting, Northing, Altitude
            transformed2odom.mult(odom_utm_transform, Utm_Path);

            path[i][0] = transformed2odom.getOrigin().getX();// Easting or utmX
            path[i][1] = transformed2odom.getOrigin().getY();// Northing or utmY

            cout<<"path[i][0]_____"<< path[i][0] <<" path[i][]_____"<< path[i][1]<< endl;
         }

          //return true;
        }


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
            cout<<"i_____"<< i <<"  size   " <<path.size() << endl;

            cout<<"storing previous point"<<endl;

            cout<<"path[i][0]_____"<< path[i][0] <<" path[i][]_____"<< path[i][1]<< endl;
          
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
              cout<<"storing the midpoint"<<endl;
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
            cout<<"storing the last point"<<endl;
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

        float tolerance = 0.001;
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

          geometry_msgs::PoseStamped new_goal = req.goal;
          tf::Quaternion goal_quat = tf::createQuaternionFromYaw(0);
     
           new_goal.pose.position.x = path[i][0];  // Latitude
           new_goal.pose.position.y = path[i][1];  // Longitude

           cout << "x------"<< path[i][0] << "y------" << path[i][1] << endl;
     
           new_goal.pose.orientation.x = goal_quat.x();
           new_goal.pose.orientation.y = goal_quat.y();
           new_goal.pose.orientation.z = goal_quat.z();
           new_goal.pose.orientation.w = goal_quat.w();
     
        resp.plan.push_back(new_goal);
      }

      */

     //path2publish.poses = resp.plan;
    
      /*
        path2publish.poses = path_planner_obj.path_msg;
     path2publish.header.seq = 1;
     path2publish.header.stamp = ros::Time::now();
     path2publish.header.frame_id = "odom";
  
     planPublisher_.publish(path2publish);
      

      // plan.push_back(req.goal); Not needed in this case
     return true;
     */
    }
    };



int main(int argc, char **argv)
{
  // initializing ros
  ROS_INFO(" initializing geobot global planner");
  ros::init(argc, argv, "geobot_global_planner_node");

  geobot_global_planner::GlobalPlannerUtil GPU;

  ros::spin();
}




bool IsMember(std::string* str, char obj);




PathPlanner::PathPlanner(){
  path_emitter = handle1.advertise<nav_msgs::Path>(
      "lawn_mowing/path",9);
  clockwise = 1;

}

/*
int main(int argc, char** argv){

  ros::init(argc, argv, "path_planning");
  ROS_INFO("Initializing path_planning node...");
  PathPlanner obj;
  if(obj.run()){
    ros::Rate loop_rate(1);
    while(ros::ok()){
      obj.Path_msgpub();
      ros::spinOnce();
      loop_rate.sleep();
    }
  }
  else{
    std::cout<<"\nThe path planning process failed...\n"
       <<std::endl;
  }

  return 0;
}
*/



void PathPlanner::ParamSetup(){

  handle1.param("path_planning/vehicle_length", vehicle_length, 1.2);
  handle1.param("path_planning/vehicle_width", vehicle_width, 0.8);
  handle1.param("path_planning/vehicle_height", vehicle_height, 0.5);
  handle1.param("path_planning/path_step_distance", scan_step, 0.5);
  handle1.param("path_planning/zero_tolerance", zero_tolerance, 0.01);

  cruise_step = vehicle_width;

        std::cout<<"\nParameters Setup:\n\n"
                 <<"The size of the vehicle:\n"
                 <<"Length, Width, Height: "
                 <<vehicle_length<<", "
                 <<vehicle_width<<", "
                 <<vehicle_height<<".\n"
                 <<"Step distance: "<<scan_step<<"\n"
     <<std::endl;
}

bool PathPlanner::CornerEntry(){

  std::ifstream corner_file;
  std::string delimiters(", :|;\n");
  bool enter_flag = false;
  std::string corner_file_path;
  handle1.param<std::string>(
      "path_planning/corner_file_path",
      corner_file_path,
      "/home/blaster-ws/ros_ws/src/geobot_navigation/corners.txt"
      );
  corner_file.open(corner_file_path.c_str());
  if(!corner_file.fail()){
    std::cout<<"Reading in corners now..."<<std::endl;
  }
  else{
    std::cout<<"Fail to read in corners from\n"
       <<corner_file_path<<std::endl;
    std::string pass;
    handle1.param<std::string>(
      "path_planning/failure_tolerance",
      pass,"Yes");
    if(!pass.compare(0,3,"Yes")){
      std::cout<<"\nEnter Yes to enter corners manually\n"
         <<"Or hit Enter to exit:(Yes/Enter):";
      std::string inputString;
                  std::getline(std::cin,inputString);
      if(!inputString.compare(0,3,"Yes")){
        std::cout<<"Manually Enter corners...\n"
           <<std::endl;
        enter_flag = true;
      }
      else{
        return false;
      }
    }
    else{
      return false;
    }
  }

  std::string inputString;
  std::vector<std::string> inputVector;
  if(!enter_flag){
    while( std::getline(corner_file, inputString))
      inputVector.push_back(inputString);
    corner_file.close();
  }
  else{
    while(inputString.compare(0,4,"stop")){
      static int flag_i = 1;
      std::cout<<"Type in corner "<<flag_i
                           <<"(Enter stop to terminate):";
                  std::getline(std::cin,inputString);
      if(!(inputString[0]==NULL)){
        inputVector.push_back(inputString);
        flag_i++;
      }
    }
  }
  for(int i = 0; i<inputVector.size()-enter_flag; i++){
    std::vector<std::string> parts;
    inputString = inputVector[i];
    boost::split(parts, inputString, boost::is_any_of(delimiters));
    boost::array<double, 2> x;
                int x_i = 0;
                for(int i = 0; i < parts.size(); i++){

                        if(parts[i][0]==NULL){
                                continue;
                        }
                        std::stringstream ss(parts[i]);
                        ss >> x[x_i];
                        x_i++;
                        if(x_i>=2) break;
                }
    if(x_i == 1) x[x_i] = 0;
                corners.push_back(x);
  }
  
  std::cout<<"Total number of corners: "
     <<corners.size()<<std::endl;
  if(!corners.size())
    return false;
  else{
    std::string show;
    handle1.param<std::string>("path_planning/show_entered_corners",
        show,"No");
    if(!show.compare(0,3,"Yes"))
      DisplayPoints("entered corners",corners,"Jump");
    return true;
  }
}

bool PathPlanner::ObstacleEntry(){

  std::ifstream obstacle_file;
  std::string delimiters(", :|;\n");
  bool enter_flag = false;
  std::string obstacle_file_path;
  handle1.param<std::string>(
      "path_planning/obstacle_file_path",
      obstacle_file_path,
      "/home/blaster-ws/ros_ws/src/geobot_navigation/obstacles.txt"
      );
  obstacle_file.open(obstacle_file_path.c_str());
  if(!obstacle_file.fail()){
    std::cout<<"Reading in obstacle now..."<<std::endl;
  }
  else{
    std::cout<<"Fail to read in obstacle from\n"
       <<obstacle_file_path<<std::endl;
    std::string pass;
    handle1.param<std::string>(
      "path_planning/failure_tolerance",
      pass,"Yes");
    if(!pass.compare(0,3,"Yes")){
      std::cout<<"\nEnter Yes to enter obstacle manually\n"
         <<"Or hit Enter to exit:(Yes/Enter):";
      std::string inputString;
                  std::getline(std::cin,inputString);
      if(!inputString.compare(0,3,"Yes")){
        std::cout<<"Manually Enter obstacles...\n"
           <<std::endl;
        enter_flag = true;
      }
      else{
        return false;
      }
    }
    else{
      return false;
    }
  }

  std::string inputString;
  std::vector<std::string> inputVector;
  if(!enter_flag){
    while( std::getline(obstacle_file, inputString))
      inputVector.push_back(inputString);
    obstacle_file.close();
  }
  else{
    while(inputString.compare(0,4,"stop")){
      static int flag_i = 1;
      std::cout<<"Type in obstacle "<<flag_i
                           <<"(Enter stop to terminate):";
                  std::getline(std::cin,inputString);
      if(!(inputString[0]==NULL)){
        inputVector.push_back(inputString);
        flag_i++;
      }
    }
  }
  for(int i = 0; i<inputVector.size()-enter_flag; i++){
    std::vector<std::string> parts;
    inputString = inputVector[i];
    boost::split(parts, inputString, boost::is_any_of(delimiters));
    boost::array<double, 3> x;
                int x_i = 0;
                for(int i = 0; i < parts.size(); i++){

                        if(parts[i][0]==NULL){
                                continue;
                        }
                        std::stringstream ss(parts[i]);
                        ss >> x[x_i];
                        x_i++;
                        if(x_i>=3) break;
                }
    if(x_i < 3) 
      while(x_i<3){
        x[x_i] = 0;
        x_i++;
      }
    boost::array<double,2> center;
    double radius;
    for(int i = 0; i<2; i++){
      center[i] = x[i];
    }
    radius = x[2];
    obstacle_info.center.push_back(center);
                obstacle_info.radius.push_back(radius);
  }
  
  std::cout<<"Total number of obstacles: "
     <<obstacle_info.center.size()<<std::endl;
  if(!obstacle_info.center.size())
    return false;
  else{
    std::string show;
    handle1.param<std::string>("path_planning/show_entered_obstacles",
        show,"No");
    if(!show.compare(0,3,"Yes"))
      DisplayRegions("entered obstacles",
          obstacle_info.center,
          obstacle_info.radius,"Jump");
    return true;
  }
}


void PathPlanner::ObstaclesPrep(){
// Scan map and obstacles to define subregions

  int obstacle_size = obstacle_info.center.size();
  boost::array<double,2> obs_center;
  double obs_radius;
  boost::array<double,2> next_pt;
  std::vector<boost::array<double,2> > obs_f,obs_b;
  std::vector<double> enter_dis, leave_dis;
  double distance;
  boost::array<double,2> start_pt = corners[0];

  for(int i = 0; i<obstacle_size; i++){
    obs_center = obstacle_info.center[i];
    obs_radius = obstacle_info.radius[i]+cruise_step/2;
    next_pt = GoNextPt(
      obs_center, cruise_tan[1], obs_radius
    );
    distance = ScanDis(start_pt,next_pt,cruise_tan[0]);
    obstacle_info.enter_dis.push_back(distance);
    obstacle_info.enter_pt.push_back(next_pt);

    next_pt = GoNextPt(
      obs_center, cruise_tan[0], obs_radius
    );
    distance = ScanDis(start_pt,next_pt,cruise_tan[0]);
    obstacle_info.leave_dis.push_back(distance);
    obstacle_info.leave_pt.push_back(next_pt);
  }

  obstacle_info.enter_order = SortOrders(obstacle_info.enter_dis);
  // sort out enter order based on enter dis
  for(int i = 0; i<obstacle_info.enter_order.size()-1; i++){
    if(obstacle_info.enter_dis[obstacle_info.enter_order[i]] == obstacle_info.enter_dis[obstacle_info.enter_order[i+1]]){
      int j = i+1;
      while(obstacle_info.enter_dis[obstacle_info.enter_order[i]] == obstacle_info.enter_dis[obstacle_info.enter_order[j]]
        &&j<obstacle_info.enter_order.size()-1){
        j++;
      }
      if(obstacle_info.enter_dis[obstacle_info.enter_order[i]] != obstacle_info.enter_dis[obstacle_info.enter_order[j]])
        j--;

      std::vector<double> new_dis;
      for(int ii = i; ii<=j; ii++){
        int obs_num = obstacle_info.enter_order[ii];
        boost::array<double,2> next_pt = obstacle_info.enter_pt[obs_num];
        double sco_dis = ScanDis(start_pt,next_pt,scan_tan[0]);
        new_dis.push_back(sco_dis);
      }
      std::vector<int> new_order = SortOrders(new_dis);
      std::vector<int> temp_order;
      int ii,ik;
      for(ii = i, ik = 0; ii<=j; ii++, ik++){
        int local_order = new_order[ik];
        int global_order = obstacle_info.enter_order[i+local_order];
        temp_order.push_back(global_order);
      }
      for(ii = i, ik = 0; ii<=j; ii++, ik++){
        obstacle_info.enter_order[ii] = temp_order[ik];
      }
    }
  }
  // sort enter order again based on the scan dis in case two or more obs have the same enter dis

//  for(int i = 0; i<obstacle_info.enter_order.size();i++){
//    std::cout<<"enter order: "<<obstacle_info.enter_order[i]<<std::endl;
//  }
//  std::cout<<std::endl;

  std::vector<int> right_check;
  obstacle_info.enter_stack.push_back(obstacle_info.enter_order[0]);
  Obs_VisitEntry(obstacle_info.enter_order[0],"New",right_check.size());
  right_check.push_back(obstacle_info.enter_order[0]);
  while(right_check.size()>0){
    int next_obs;
    int next_left;
    int next_right;
    int next_new;
    int curr_obs;
    bool left_flag,right_flag,stack_flag;
    double curr_enter, curr_leave, next_enter, next_curr;

    curr_obs = right_check[right_check.size()-1];
    curr_enter = obstacle_info.enter_dis[curr_obs];
    curr_leave = obstacle_info.leave_dis[curr_obs];
    int curr_loc;
    for(int i = 0; i<obstacle_info.enter_order.size(); i++){
      if(obstacle_info.enter_order[i]==curr_obs){
        curr_loc = i;
        break;
      }
    }

    left_flag = false;
    right_flag = false;
    for(int i = curr_loc; i<obstacle_info.center.size(); i++){
      next_obs = obstacle_info.enter_order[i];
      stack_flag = false;
      for(int stack_i = 0; stack_i<obstacle_info.enter_stack.size(); stack_i++){
        if(next_obs == obstacle_info.enter_stack[stack_i]){
          stack_flag = true;
          break;
        }
      }
      if(stack_flag)continue;
      next_enter = obstacle_info.enter_dis[next_obs];
      next_curr = ScanDis(obstacle_info.enter_pt[next_obs],
              obstacle_info.enter_pt[curr_obs],
              scan_tan[0]);
      if((next_enter>=curr_enter)
          &&(next_enter<=curr_leave)){
        if(next_curr>0){
          left_flag = true;
          next_left = next_obs;
          break;
        }
        else if(!right_flag){
          if(right_check.size()>1){
            int curr_back = right_check[right_check.size()-2];
            double curr_back_dis = obstacle_info.leave_dis[curr_back];
            double next_curr_back = ScanDis(obstacle_info.enter_pt[next_obs],
                    obstacle_info.enter_pt[curr_back],
                    scan_tan[0]);
            if((next_curr_back>0)&&(next_enter<curr_back_dis)){
              right_flag = true;
              next_right = next_obs;
            }
          }
          else{
            right_flag = true;
            next_right = next_obs;
          }
        }
      }
      else if(next_enter>curr_leave){
        next_new = next_obs;
        break;
      }
    }
    if(left_flag){
      obstacle_info.enter_stack.push_back(next_left);
      Obs_VisitEntry(next_left,"Left",right_check.size());
      right_check.push_back(next_left);
//      std::cout<<"Left Flag Invoked~! with obs "<<next_left<<std::endl;
//      std::cout<<"Right check size: "<<right_check.size()<<"\n"<<std::endl;
    }
    else if(right_flag){
      obstacle_info.enter_stack.push_back(next_right);
      Obs_VisitEntry(next_right,"Right",right_check.size());
      right_check.pop_back();
      right_check.push_back(next_right);
//      std::cout<<"Right Flag Invoked~! with obs "<<next_right<<std::endl;
//      std::cout<<"Right check size: "<<right_check.size()<<"\n"<<std::endl;
    }
    else if(right_check.size()>1){
      right_check.pop_back();
//      std::cout<<"Pure Pop back, after popback, ";
//      std::cout<<"Right check size: "<<right_check.size()<<"\n"<<std::endl;
    }
    else if(obstacle_info.enter_stack.size()<obstacle_info.center.size()){
      obstacle_info.enter_stack.push_back(next_new);
      Obs_VisitEntry(next_new,"New",right_check.size());
      right_check.pop_back();
      right_check.push_back(next_new);
//      std::cout<<"New Flag Invoked~! with obs "<<next_new<<std::endl;
//      std::cout<<"Right check size: "<<right_check.size()<<"\n"<<std::endl;
    }
    else{
      right_check.pop_back();
//      std::cout<<"Visit stack closing...\n"<<std::endl;
    }
  }
  std::cout<<"ObstaclePrep is completed!\n"<<std::endl;

}

void PathPlanner::Obs_VisitEntry(int obs, std::string type, int location){

  int flag = 0;

  if(!type.compare(0,3,"New")) flag = 0;
  if(!type.compare(0,3,"Lef")) flag = -1;
  if(!type.compare(0,3,"Rig")) flag = 1;

  if(flag==0)
    location = 0;
  if(flag==-1)
    location = location;
  if(flag==1)
    location = (location-1);

  boost::array<int,2> visit_pt1,visit_pt2;

  visit_pt1[0] = obs;
  visit_pt1[1] = 0;

  visit_pt2[0] = obs;
  visit_pt2[1] = 1;

  std::vector<boost::array<int,2> >::iterator it;
  it = obstacle_info.visit_stack.end();

  obstacle_info.visit_stack.insert(it-location,visit_pt1);
  it = obstacle_info.visit_stack.end();
  obstacle_info.visit_stack.insert(it-location,visit_pt2);

//  std::cout<<"Updated stack:\n";
//  for(int i =0; i<obstacle_info.visit_stack.size();i++){
//    std::cout<<"stack "<<i+1<<" : "<<obstacle_info.visit_stack[i][0]<<" , "<<obstacle_info.visit_stack[i][1]<<".\n";
//  }
//  std::cout<<std::endl;

}

std::vector<int> PathPlanner::SortOrders(
  std::vector<double> input){

  std::vector<int> output;
  std::vector<int>::iterator it;
  std::vector<double> sort_number;
  std::vector<double>::iterator sit;
  int size = input.size();
  output.push_back(0);
  sort_number.push_back(input[0]);
  if(input.size()==1) return output;

  for(int i = 1; i<size; i++){
    int j = 0;
    while(input[i]<sort_number[j]&&j<i){
      j++;
    }
      sit = sort_number.begin();
      sit = sort_number.insert(sit+j,input[i]);
      it = output.begin();
      it = output.insert(it+j,i);
  }

  std::reverse(output.begin(),output.end());
  // reverse the output from descend to be ascend
  return output;
}

double PathPlanner::ScanDis(
  boost::array<double,2> start_pt,
  boost::array<double,2> end_pt,
  double vert_tan){

  double obj_tan;
  obj_tan = std::atan2((end_pt[1]-start_pt[1]),
                   (end_pt[0]-start_pt[0]));

  double ang_diff = vert_tan-obj_tan;
  if(ang_diff<0) ang_diff = -ang_diff;

  double distance;
  distance = std::pow(
      (std::pow((end_pt[1]-start_pt[1]),2)
      +std::pow((end_pt[0]-start_pt[0]),2)),0.5);
  distance = distance * cos(ang_diff);

  return distance;
}

void PathPlanner::SortCorners(){

  std::vector<boost::array<double,2> > sort_corners;
  int corner_size = corners.size();
  int order[corner_size];
  for(int i = 0; i<corner_size; i++)
    order[i] = i;
  double tan_min;
  double tan_max;
  double tan;
  int min;
  int max;
  int pt_now;
  int pt_nex;
  double x_now,y_now;
  double x_nex,y_nex;
  double tan_log[corner_size];
  for(int i = 0; i<corner_size-1; i++){
    pt_now = order[i];
    for(int j = i+1; j<corner_size; j++){
      pt_nex = order[j];
      x_now = corners[pt_now][0];
      y_now = corners[pt_now][1];
      x_nex = corners[pt_nex][0];
      y_nex = corners[pt_nex][1];

      tan = std::atan2((y_nex-y_now),(x_nex-x_now));
      tan_log[j] = tan;
    }
    tan_max = -M_PI;
    tan_min = M_PI;
    for(int j = i+1; j<corner_size; j++){
      if(tan_log[j]>=tan_max){
        tan_max = tan_log[j];
        max = j;
      }
      if(tan_log[j]<=tan_min){
        tan_min = tan_log[j];
        min = j;
      }
    }
    if(tan_max-tan_min<M_PI){
      int temp = order[i+1];
      order[i+1] = order[max];
      order[max] = temp;
    }
    else{
      tan_max = -M_PI;
      for(int j = i+1; j<corner_size; j++){
        if(tan_log[j]<=0&&tan_log[j]>=tan_max){
          tan_max = tan_log[j];
          max = j;
        }
      }
      int temp = order[i+1];
      order[i+1] = order[max];
      order[max] = temp;
    } 
  }

  for(int i = 0; i<corner_size; i++){
    sort_corners.push_back(corners[order[i]]);
  }

  corners = sort_corners;
  std::cout<<"\nSorting out entered corners..."
     <<std::endl;
}


void PathPlanner::DefinePath(){

  SortCorners();
  std::vector<boost::array<double,2> > sort_corners;
  DisplayPoints("sorted corners", corners, "Jump");
  int start_pt;
  int next_pt;
  handle1.param("path_planning/start_corner_number",
      start_pt,1);
  std::cout<<"Using corner "<<start_pt
     <<" as the start point..."
     <<std::endl;
  start_pt--;
  for(int i = 0; i<corners.size(); i++){
    next_pt = start_pt + clockwise*i;
    if(next_pt<0)
      next_pt = corners.size()+next_pt;
    if(next_pt>=corners.size())
      next_pt = next_pt-corners.size();
    sort_corners.push_back(corners[next_pt]);
  }

  corners = sort_corners;
  std::string show;
  handle1.param<std::string>("path_planning/show_corner_order",
      show,"No");
  if(!show.compare(0,3,"Yes"))
    DisplayPoints("corners in order",sort_corners,"Jump");
  
}

void PathPlanner::ScanMap(){

        double fscan_tan = std::atan2((corners[1][1]-corners[0][1]),
                   (corners[1][0]-corners[0][0]));
        double bscan_tan = fscan_tan-M_PI;
  double fcruise_tan = fscan_tan-(M_PI/2)*clockwise;
  double bcruise_tan = fcruise_tan-M_PI;
  while(bcruise_tan<-M_PI) bcruise_tan+=2*M_PI;
  while(bcruise_tan>M_PI) bcruise_tan-=2*M_PI;
        while(bscan_tan>M_PI) bscan_tan = bscan_tan-2*M_PI;
        while(bscan_tan<-M_PI) bscan_tan = bscan_tan+2*M_PI;
        while(fcruise_tan>M_PI) fcruise_tan = fcruise_tan-2*M_PI;
        while(fcruise_tan<-M_PI) fcruise_tan = fcruise_tan+2*M_PI;
        scan_tan[0] = fscan_tan;
        scan_tan[1] = bscan_tan;
  cruise_tan[0] = fcruise_tan;
  cruise_tan[1] = bcruise_tan;

  int size_ob = obstacle_info.center.size();
  if(size_ob>0) ObstaclesPrep();
  double tempDis;
  MaxDis = 0;
  for(int i = 1; i<corners.size(); i++){
    tempDis = ScanDis(corners[0],corners[i],cruise_tan[0]);
    if(MaxDis<=tempDis)
      MaxDis = tempDis;
  }
  std::cout<<"ScanMap completed!\n"<<std::endl;
}

void PathPlanner::PathPlanning(){

  ScanMap();
  boost::array<double,2> start_pt, next_pt;
  bool scan_d = 0;// scan direction, 0: forward, 1: backward 
  bool check_flag = 1;
  int cf2_i;
  int check_limit = 44;
  double tempDis = 0;
  next_pt = GoNextPt(corners[0], cruise_tan[0], vehicle_width/2);

  int obs_counter = 0;
  int obs_total = obstacle_info.center.size();
  std::vector<int> obs_stack;
  boost::array<int,2> vi_spt;
  boost::array<double,2> vi_pt, circle_pt;
  bool obs_flag = false;
  double lineDis = 0;
  int type;
  int obs_circle;
  int vi_i=0;
  bool repetition = false;
  bool circle_flag = false;

//  for(int i =0; i<obstacle_info.visit_stack.size(); i++){
//    std::cout<<"stack "<<i+1<<":\n";
//    std::cout<<"obstacle_info:"<<obstacle_info.visit_stack[i][0]<<", "<<obstacle_info.visit_stack[i][1]<<"\n"<<std::endl;
//  }

  if(obstacle_info.center.size()>0){
    vi_spt = obstacle_info.visit_stack[vi_i];
    vi_pt = obstacle_info.enter_pt[vi_spt[0]];
    type = vi_spt[1]; // 0: bottom, 1: Top
    lineDis = ScanDis(corners[0],vi_pt,cruise_tan[0]);
    vi_i++;
//    std::cout<<"check point: ("<<vi_pt[0]<<", "<<vi_pt[1]<<")."<<std::endl;
//    std::cout<<"Obstacle "<<vi_i<<std::endl;
//    std::cout<<"Distance: "<<lineDis<<std::endl;
  }
  int re_i = 1;
  while(tempDis<MaxDis-cruise_step/2){
//    std::cout<<"Re "<<re_i<<std::endl;
    re_i++;

                cf2_i = 0;
                while((!IsPtInside(next_pt,corners))&&(cf2_i<check_limit)){
//      std::cout<<"streching"<<std::endl;
                        next_pt = GoNextPt(
                                next_pt, scan_tan[scan_d], scan_step
                                );
                        cf2_i++;
                }
//    std::cout<<"streching number"<<cf2_i<<std::endl;
                while(IsPtInside(next_pt,corners)){
//      std::cout<<"Scanning"<<std::endl;     
      //std::cout<<"Path Point:("<<next_pt[0]<<", "<<next_pt[1]<<")."<<std::endl;
                        path.push_back(next_pt);
      if(circle_flag&&(!repetition)){

        double cirDis = ScanDis(next_pt,circle_pt,scan_tan[0]);
//        if(cirDis<0.5)
//          std::cout<<"cirDis: "<<cirDis<<"\n";
        if(cirDis-scan_step<=zero_tolerance&&cirDis>-zero_tolerance){
//          std::cout<<"cirDis: "<<cirDis<<"\n";
//          std::cout<<"CIRCLE, BABE~! : "<<re_i<<std::endl;
//          std::cout<<"Path Point Before Circle:("<<path[path.size()-1][0]<<", "<<path[path.size()-1][1]<<")."<<std::endl;
//          std::cout<<"start darwing circles:"<<std::endl;
          DrawCirclePath(obstacle_info.visit_stack[vi_i-2][0]);
          circle_flag = false;
//          std::cout<<"circle finished"<<std::endl;
//          std::cout<<"Path Point After Circle:("<<path[path.size()-1][0]<<", "<<path[path.size()-1][1]<<").\n"<<std::endl;
        }

      }
                        next_pt = GoNextPt(
                                path[path.size()-1],scan_tan[scan_d],scan_step
                                );
                }
    
          scan_d = 1 - scan_d;
                next_pt = GoNextPt(
                        path[path.size()-1], cruise_tan[0], cruise_step
                        );
    tempDis = ScanDis(corners[0],path[path.size()-1],cruise_tan[0]);
//    if(tempDis>59&&tempDis<62){
//      double cirDis = ScanDis(next_pt,circle_pt,scan_tan[0]);
//      std::cout<<"tempDis: "<<tempDis<<"\n"
//         <<"circle_flag: "<<circle_flag<<"\n"
//         <<"repetition: "<<repetition<<"\n"
//         <<"cirDis: "<<cirDis<<" (scan_step: "<<scan_step<<"\n"
//         <<std::endl;
//    }
//    std::cout<<"Temp Distance: "<<tempDis<<"(Max:"<<MaxDis-cruise_step/2<<")"<<std::endl;
//    std::cout<<"lineDistance:"<<lineDis<<std::endl;
//    std::cout<<"path point: ("<<path[path.size()-1][0]<<", "<<path[path.size()-1][1]<<")."<<std::endl;
//    std::cout<<"next point: ("<<next_pt[0]<<", "<<next_pt[1]<<")."<<std::endl;


    if(repetition){
      next_pt = path[path.size()-1];
      repetition = false;
//      std::cout<<"repeat at tempDis = "<<tempDis<<std::endl;
    }
    else{ 
      if(obstacle_info.Circle_done.size()>0
        &&tempDis>obstacle_info.Circle_done[obstacle_info.Circle_done.size()-1]-cruise_step
  //      &&tempDis<obstacle_info.Circle_done[obstacle_info.Circle_done.size()-1]
        &&scan_d==0){
        double diff = obstacle_info.Circle_done[obstacle_info.Circle_done.size()-1]-tempDis;
      
        next_pt = GoNextPt(
          path[path.size()-1], cruise_tan[0], diff
          );
        repetition = true;
//        std::cout<<"circle repetition invoked!\n"<<std::endl;
//        std::cout<<"tempDis: "<<tempDis<<"\n";
//        std::cout<<"check line: "<<obstacle_info.Circle_done[obstacle_info.Circle_done.size()-1]-cruise_step<<"\n"<<std::endl;
        obstacle_info.Circle_done.pop_back();

//        std::cout<<"tempDis: "<<tempDis<<std::endl;
//        std::cout<<"scan_d: "<<scan_d<<std::endl;
        }

      if((tempDis>=lineDis-cruise_step)
        &&(tempDis<lineDis)
        &&(!circle_flag)){
  //      std::cout<<"Temp Dis: "<<tempDis<<std::endl;
  //      std::cout<<"Line Dis: "<<lineDis<<std::endl;
//        std::cout<<"Alert! look out for Line Distance: "<<lineDis<<"~!\n"
//           <<"The temp distance right now is : "<<tempDis<<"~!\n"
//           <<std::endl;
/*        bool pub_flag = true;
        std::cin.clear();
        while(pub_flag){
  
          Path_msgfill();
          Path_msgpub();
          if(std::cin.get()=='g') pub_flag = false;
        }
*/
        double diff = lineDis-tempDis;
      
//        std::cout<<"Scan direction: "<<scan_d<<"\n";
//        std::cout<<"Type : "<<type<<"\n"<<std::endl;

        next_pt = GoNextPt(
          path[path.size()-1], cruise_tan[0], diff
          );
        if(type==scan_d)
          repetition = true;
        else
          repetition = false;
        if(type){
          circle_flag = type;// type 1 then check for circle point
          circle_pt = vi_pt;
          obs_circle = obstacle_info.visit_stack[vi_i-2][0];
        }
  //      std::cout<<"repetition:"<<repetition<<std::endl;
  //      std::cout<<"circle_flag:"<<circle_flag<<std::endl;
        if(vi_i<obstacle_info.visit_stack.size()){
          vi_spt = obstacle_info.visit_stack[vi_i];
          type = vi_spt[1]; // 0: bottom, 1: Top, 2: back to bottom
          if(type==0)
            vi_pt = obstacle_info.enter_pt[vi_spt[0]];
          else
            vi_pt = obstacle_info.leave_pt[vi_spt[0]];
          lineDis = ScanDis(corners[0],vi_pt,cruise_tan[0]);
          vi_i++;
//          if(type){
//          std::cout<<"Obstacle "<<vi_i<<std::endl;
//          std::cout<<"Distance: "<<lineDis<<std::endl;
//          std::cout<<"Leave_dis: "<<obstacle_info.leave_dis[vi_spt[0]]<<std::endl;
//          }
//          Path_msgfill();
//          Path_msgpub();
        }
        else{
          lineDis = 2*MaxDis;
//          std::cout<<"Obstacle Out"<<std::endl;
        }
/*
        if(type==0){
          if(scan_d==1) // back scan direction
            repetition = false;
          if(scan_d==0) // forward scan direction which is not wanted
            repetition = true;
        }
        else if(type==1){ // Top point
          if(scan_d==1)
            repetition = true;
          if(scan_d==0)
            repetition = false;
        }
*/

      }//if check and update lineDis


    }//else not repetition

    // for closing the map
    if(tempDis>MaxDis-cruise_step*3/2){
      double diff = MaxDis-cruise_step/2-tempDis;
      next_pt = GoNextPt(
        path[path.size()-1], cruise_tan[0], diff
        );
    }
      
        }//ending path planning
//  std::cout<<"Ck out!"<<std::endl;
  PrintPath();

  std::string show;
  handle1.param<std::string>("path_planning/show_path",
      show,"No");
  if(!show.compare(0,3,"Yes"))
    DisplayPoints("path",path,"Jump");

}

void PathPlanner::DrawCirclePath(int obs){

//  std::cout<<"draw circle around obstacle "<<obs<<std::endl;
  boost::array<double,2> start_pt, end_pt, center;
  double radius;
  center = obstacle_info.center[obs];
  start_pt = obstacle_info.leave_pt[obs];
  end_pt = obstacle_info.enter_pt[obs];
  radius = obstacle_info.radius[obs]+cruise_step/2;
  double theta_step = scan_step/radius;
  boost::array<double,2> next_pt;
  double theta = 0;
//  std::cout<<"obs center:("<<center[0]<<", "<<center[1]<<")."<<std::endl;
//  std::cout<<"obs radius: "<<radius<<std::endl;
//  std::cout<<"obs start point:("<<start_pt[0]<<", "<<start_pt[1]<<")."<<std::endl;
//  std::cout<<"obs end point:("<<end_pt[0]<<", "<<end_pt[1]<<")."<<std::endl;
//  std::cout<<"theta step: "<<theta_step<<std::endl;
  int loop_i = 0;
  while(EuclideanDist(path[path.size()-1],end_pt)>scan_step){
    next_pt = GoNextPt(start_pt,scan_tan[0],sin(theta)*radius);
    next_pt = GoNextPt(next_pt,cruise_tan[1],(1-cos(theta))*radius);
    path.push_back(next_pt);
    theta+=theta_step;
//    loop_i++;
//    std::cout<<"loop "<<loop_i<<std::endl;
  }
//  std::cout<<"loop ending"<<std::endl;
  path.push_back(end_pt);
//  std::cout<<"Finished circle drawing"<<std::endl;
//  path.push_back();
  obstacle_info.Circle_done.push_back(obstacle_info.leave_dis[obs]);
  
}

double PathPlanner::EuclideanDist(boost::array<double,2> first_pt, boost::array<double,2> second_pt){

  double dist;
  double x1,x2,y1,y2;
  x1 = first_pt[0];
  y1 = first_pt[1];
  x2 = second_pt[0];
  y2 = second_pt[1];
  dist = pow(pow(x1-x2,2)+pow(y1-y2,2),0.5);

  return dist;
}


bool PathPlanner::PrintPath(){

  std::ofstream path_file;
  std::string path_file_path;
  handle1.param<std::string>(
      "path_planning/path_file_path",
      path_file_path,
      "/home/blaster-ws/Desktop/path.txt"
      );
  std::string s;
  handle1.param<std::string>("path_planning/print_to_file",s,"No");
  if(!s.compare(0,3,"Yes")){
    path_file.open(path_file_path.c_str());
    if(!path_file.fail()){
      std::cout<<"Printing path to "
         <<path_file_path<<" ...\n"<<std::endl;
    }
    else{
      std::cout<<"Fail to create the output path file!"
         <<std::endl;
      return false;
    }

    for(int i = 0; i<path.size(); i++){
      path_file<<path[i][0]<<" "<<path[i][1]<<"\n";
    }
  
    path_file.close();
    return true;
  }
  else{
    std::cout<<"\nPath won't be print to file!\n"<<std::endl;
  }
}

void PathPlanner::Path_msgfill(){

  handle1.param<std::string>(
    "path_planning/path_frame_id",
    path_msg.header.frame_id,
    "odom");
  path_msg.poses.resize(path.size());

  for(int i = 0; i<path.size(); i++){
    path_msg.poses[i].pose.position.x = path[i][0];
    path_msg.poses[i].pose.position.y = path[i][1];
    path_msg.poses[i].pose.position.z = 0;
  }

}

void PathPlanner::Path_msgpub()
{
  if (path_emitter.getNumSubscribers() > 0)
    {
      path_emitter.publish(path_msg);
    }
}

bool PathPlanner::run(){

  ParamSetup();
  cornerEntry_flag = CornerEntry();
  if(cornerEntry_flag){
    
    if(!ObstacleEntry())
      std::cout<<"No obstacles entered!"
         <<std::endl;
    DefinePath();
    PathPlanning();
    Path_msgfill();
    std::cout<<"\nThe total path point number: "
       <<path.size()<<"\n"<<std::endl;
    std::cout<<"Start publishing path topic...\n"
       <<std::endl;
    Path_msgpub();
    return true;
  }
  else
    return false;

}


bool PathPlanner::DisplayPoints(std::string title,
    std::vector<boost::array<double,2> > points,
    std::string Ask){

  if(!Ask.compare(0,3,"Ask")){
    std::cout<<"\nEnter Yes to display the "
       <<title<<"\n"
       <<"Or hit Enter to continue(Yes/Enter):";
    std::string inputString;
    std::getline(std::cin,inputString);
  
    if(inputString.compare(0,3,"Yes"))
      return 0;
  }
  std::cout<<"\n"<<title<<":\n";
  for(int i = 0; i < points.size(); i++){
    std::cout<<"Corner "<<i+1<<": "
       <<"("<<points[i][0]
       <<", "<<points[i][1]<<")"
       <<std::endl;
  }
  std::cout<<"\n";
  
  return 1; 
}

bool PathPlanner::DisplayRegions(std::string title,
    std::vector<boost::array<double,2> > centers,
    std::vector<double> radius,
    std::string Ask){

  if(!Ask.compare(0,3,"Ask")){
    std::cout<<"\nEnter Yes to display the "
       <<title<<"\n"
       <<"Or hit Enter to continue(Yes/Enter):";
    std::string inputString;
    std::getline(std::cin,inputString);
  
    if(inputString.compare(0,3,"Yes"))
      return 0;
  }
  std::cout<<"\n"<<title<<":\n";
  for(int i = 0; i < centers.size(); i++){
    std::cout<<"Center "<<i+1<<": "
       <<"("<<centers[i][0]
       <<", "<<centers[i][1]<<")"
       <<", radius: "<<radius[i]
       <<std::endl;
  }
  std::cout<<"\n";
  
  return 1; 
}


boost::array<double,2> 
PathPlanner::GoNextPt(boost::array<double,2> start_pt, 
double direction, double distance){

  boost::array<double,2> next_pt;
  next_pt[0] = start_pt[0] + std::cos(direction)*distance;
  next_pt[1] = start_pt[1] + std::sin(direction)*distance;

  return next_pt;
}
   
bool PathPlanner::IsPtInside(boost::array<double,2> Ckpt,
std::vector<boost::array<double,2> > corners){

  double x_ck = Ckpt[0];
  double y_ck = Ckpt[1];

  for(int i = 0; i<corners.size(); i++){
    int i_pre, i_nex;
    i_pre = i - 1;
    i_nex = i + 1;
    if(i_pre<0) i_pre = i_pre+corners.size();
    if(i_nex>=corners.size()) i_nex = 0;
    if(clockwise == -1){
      int temp = i_pre;
      i_pre = i_nex;
      i_nex = temp;
    }

    double x0 = corners[i][0];
    double y0 = corners[i][1];
    double x_pre = corners[i_pre][0];
    double y_pre = corners[i_pre][1];
    double x_nex = corners[i_nex][0];
    double y_nex = corners[i_nex][1];
    double tan_pre = atan2((y_pre-y0),(x_pre-x0));
    double tan_nex = atan2((y_nex-y0),(x_nex-x0));
    double tan_ck = atan2((y_ck-y0),(x_ck-x0));

    if(tan_pre-tan_nex>=M_PI){
      tan_nex = tan_nex+2*M_PI;
      if(tan_ck<0)
        tan_ck = tan_ck+2*M_PI;
    }
    if(tan_ck>tan_nex||tan_ck<tan_pre){
      return false;
    }
  }

  double slack = cruise_step/2-scan_step/2; // could be vehicle_width;
  boost::array<double,2> center;
  double r_c;
  for(int i = 0; i<obstacle_info.center.size(); i++){
    center = obstacle_info.center[i];
    r_c = obstacle_info.radius[i] + slack;
    if(EuclideanDist(Ckpt,center)<r_c){
      return false;
    //  return InOrOut;
    }
  }

  return true;
}


bool IsMember(std::string* str, char obj){
  std::string strL;
  strL = *str;

  for(int i = 0; i < strL.size(); i++){
    if(strL[i] == obj)
      return 1;
    
  }
  return 0;
}











