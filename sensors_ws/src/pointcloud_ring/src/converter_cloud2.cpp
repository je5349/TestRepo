/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2009, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: converter.cpp 33249 2010-03-11 02:09:24Z rusu $
 *
 */

#include <ros/ros.h>
#include <boost/thread.hpp>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <pointcloud_ring/point_cloud_conversion.h>
#include <stdint.h>
#include <vector>
#include <time.h>

using namespace std;

// Not doing any conversion
// It is converting pointcloud2 to ring in the the same format
class PointCloudConverter 
{
  private:
    boost::mutex m_mutex_;
    // ROS
    ros::NodeHandle nh_;
    ros::Subscriber sub_points2_;
    ros::Publisher pub_points2_; 

    

    int queue_size_;
    string points2_in_, points2_out_;

  protected: 
    int ring_layer;

  public:
    PointCloudConverter () : nh_ ("~"), queue_size_ (100), 
                             points2_in_ ("/points2_in"), 
                             points2_out_ ("/points2_out")
    {
      // Subscribe to the cloud topic using both the old message format and the new
      sub_points2_ = nh_.subscribe (points2_in_, queue_size_, &PointCloudConverter::cloud_cb_points2, this);
      pub_points2_ = nh_.advertise<sensor_msgs::PointCloud2> (points2_out_, queue_size_);
      
      ROS_INFO ("PointCloudConverter initialized to transform from PointCloud2 (%s) to PointCloud2 (%s).", nh_.resolveName (points2_in_).c_str (), nh_.resolveName (points2_out_).c_str ());
    
    ros::NodeHandle private_nh_("~");
    private_nh_.param("ring_layer", ring_layer, 7);
      
    }
    
    
    // This function is for Pointcloud2 to Pointcloud1
    inline std::string
      getFieldsList (const sensor_msgs::PointCloud2 &cloud)
    {
      std::string result;
      for (size_t i = 0; i < cloud.fields.size () - 1; ++i)
        result += cloud.fields[i].name + " ";
      result += cloud.fields[cloud.fields.size () - 1].name;

      return (result);
     }


    // convert pointcloud2 depend on ring number
    // converting from pointcloud2 to pointcloud1
    void
      cloud_cb_points2 (const sensor_msgs::PointCloud2 msg)
    {
      if (pub_points2_.getNumSubscribers () <= 0)
      {
        //ROS_DEBUG ("[point_cloud_converter] Got a PointCloud2 with %d points on %s, but no subscribers.", msg->width * msg->height, nh_.resolveName (points2_in_).c_str ());
        return;
      }

      // This is to take pointcloud2 corresponding to a certain ring layer

      sensor_msgs::PointCloud2 new_msg;
      
      new_msg.header = msg.header;
      new_msg.height = msg.height;
      new_msg.fields = msg.fields;
      new_msg.is_bigendian = msg.is_bigendian;
      new_msg.point_step = msg.point_step;
      new_msg.is_dense = msg.is_dense;


      vector <uint8_t> new_data;
      // int ring_layer = 7; // Turn into parameter
      int step = msg.point_step;
      int count=0;

      nh_.getParam("ring_layer", ring_layer);

/////////////////////////////////////////////



      for (int i=0; i < msg.row_step; i = i+32)
      {

        if(msg.data[i + 20] == ring_layer)  // The ring value is at the 20th element
        {
          for (int j=0; j < step; j++)
          {
            new_data.push_back(msg.data[i+j]);
          }

        count++;  
        }

      }



      new_msg.data = new_data;
      new_msg.row_step = new_data.size();
      new_msg.width = new_data.size()/step;


      new_data.clear();


      ROS_DEBUG ("[point_cloud_converter] Got a PointCloud2 with %d points (%s) on %s.", new_msg.width * new_msg.height, getFieldsList (new_msg).c_str (), nh_.resolveName (points2_in_).c_str ());
      

       pub_points2_.publish (new_msg);
 
    }


};

/* ---[ */
int
  main (int argc, char** argv)
{
  // ROS init
  ros::init (argc, argv, "point_cloud_converter", ros::init_options::AnonymousName);

  PointCloudConverter p;
  ros::spin ();

  return (0);
}
