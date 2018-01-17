   /** include the libraries you need in your planner here */
   /** for global path planner interface */
   #include <ros/ros.h>
   #include <geometry_msgs/PoseStamped.h>
   #include <angles/angles.h>
   #include <geobot_navigation/GetPlan.h>
  #include <geobot_navigation/navsat_conversions.h>
   #include <tf/transform_listener.h>
  #include <boost/algorithm/string.hpp>
  #include <boost/array.hpp>
  #include "geometry_msgs/Point.h"
  #include "geometry_msgs/Pose.h"
 #include <nav_msgs/Path.h> 


  
   using std::string;
   
  #ifndef GLOBAL_PLANNER_H
  #define GLOBAL_PLANNER_H


     class obstacle_set{

      public:
        std::vector<boost::array<double,2> > center;
        std::vector<double> radius;
        std::vector<boost::array<double,2> > enter_pt;
        std::vector<boost::array<double,2> > leave_pt;
        std::vector<double> enter_dis;
        std::vector<double> leave_dis;
        std::vector<int> enter_order;
        std::vector<int> enter_stack;
        std::vector<boost::array<int,2> > visit_stack;
        std::vector<double> Circle_done;
      };



    class PathPlanner{
    public:
      PathPlanner();
      double vehicle_length;
      double vehicle_width;
      double vehicle_height;
      double scan_step;
      double cruise_step;
      std::vector<boost::array<double,2> > corners;
      obstacle_set obstacle_info;
      std::vector<boost::array<double,2> > path;
            double scan_tan[2];
      double cruise_tan[2];
      nav_msgs::Path path_msg;
      bool cornerEntry_flag;
      int clockwise;
      double zero_tolerance;
      double MaxDis;
      void ParamSetup();
      bool CornerEntry();
      bool ObstacleEntry();
      void SubRegionsGeneration();
      void DefinePath();
      void ScanMap();
      void PathPlanning();
      void Path_msgfill();
      void Path_msgpub();
      bool PrintPath();
      bool run();
      
      void SortCorners();
      void ObstaclesPrep();// called in ScanMap();
      void DrawCirclePath(int obs);
      void Obs_VisitEntry(int obs, std::string type, int location);
      std::vector<int> SortOrders(
        std::vector<double> input);
      double EuclideanDist(boost::array<double,2> first_pt, boost::array<double,2> second_pt);
      double ScanDis(
        boost::array<double,2> start_pt,
        boost::array<double,2> end_pt,
        double vert_tan);
      bool DisplayPoints(std::string title,
        std::vector<boost::array<double,2> > points,
        std::string Ask);
      bool DisplayRegions(std::string title,
        std::vector<boost::array<double,2> > centers,
        std::vector<double> radius,
        std::string Ask);
      bool IsPtInside(boost::array<double,2> Ckpt,
        std::vector<boost::array<double,2> > corners);
      bool PrintPath(std::vector<boost::array<double,2> > path);
      boost::array<double,2>
        GoNextPt(boost::array<double,2> start_pt,
        double direction, double distance);
    protected:
      ros::NodeHandle handle1;
      ros::Publisher path_emitter;
    };

  
    namespace geobot_global_planner {
   
    class GlobalPlannerUtil {


    private:
      ros::NodeHandle nh;
      ros::Publisher planPublisher_;
      // ros::NodeHandle nhPriv("~");
      ros::ServiceServer makeplan_;
      tf::TransformListener listener;

      PathPlanner path_planner_obj;
      string utmZone;
      string trajectory_filepath_world_;

    public:

      GlobalPlannerUtil();
      bool makePlan(geobot_navigation::GetPlan::Request &req, geobot_navigation::GetPlan::Response &resp);
      
    };

    };

  #endif
