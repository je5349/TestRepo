#include <ros/ros.h>
#include "nav_msgs/GetMap.h"
#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "message_filters/subscriber.h"
#include "tf/message_filter.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/Point.h"
#include <vector>

using namespace std;

class pathplan
{
	public:
		pathplan(); // constructor

		void init();

		void testmap(float &origin_x,float &origin_y,int &width, int &height, int &resolution);

		void hueristic_cost(const nav_msgs::OccupancyGrid& test_map_);

		void expand(vector<int> &step);

		void Astar(const nav_msgs::OccupancyGrid& test_map_); // start astar

		void poss_path();

		void intermediate_goal();

		int diagonalcost(int &x,int &y);

	private:
		ros::NodeHandle node_;

		ros::Publisher test_map; // test occupancy grid map for testing path plan algorithm

		ros::Publisher path;

		ros::Subscriber sub_;

		nav_msgs::Path *Astar_path_;

		nav_msgs::OccupancyGrid *test_map_;

		//A* variables
        geometry_msgs::Point goal_;

		geometry_msgs::Point int_goal_;

		vector<float> *hueristic_cost_;

        vector< vector<int> > *openset;

        vector< vector<int> > closedset; //also known as closed list

       	vector< vector<int> > *poss_path_;

        vector< vector<int> > temp_step;

        vector< vector<int> > optimal_path;

//        vector<vector<int> > movement;
//
//        vector< vector<int> > movement_cost;

           int movement[10][10];
           float movement_cost[10][10];


};

