// Generated by gencpp from file geobot_navigation/SetGoalResult.msg
// DO NOT EDIT!


#ifndef GEOBOT_NAVIGATION_MESSAGE_SETGOALRESULT_H
#define GEOBOT_NAVIGATION_MESSAGE_SETGOALRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace geobot_navigation
{
template <class ContainerAllocator>
struct SetGoalResult_
{
  typedef SetGoalResult_<ContainerAllocator> Type;

  SetGoalResult_()
    {
    }
  SetGoalResult_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }






  typedef boost::shared_ptr< ::geobot_navigation::SetGoalResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::geobot_navigation::SetGoalResult_<ContainerAllocator> const> ConstPtr;

}; // struct SetGoalResult_

typedef ::geobot_navigation::SetGoalResult_<std::allocator<void> > SetGoalResult;

typedef boost::shared_ptr< ::geobot_navigation::SetGoalResult > SetGoalResultPtr;
typedef boost::shared_ptr< ::geobot_navigation::SetGoalResult const> SetGoalResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::geobot_navigation::SetGoalResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace geobot_navigation

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'geobot_navigation': ['/home/administrator/sensors_ws/src/geobot_navigation/msg', '/home/administrator/sensors_ws/devel/share/geobot_navigation/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::geobot_navigation::SetGoalResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::geobot_navigation::SetGoalResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::geobot_navigation::SetGoalResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::geobot_navigation::SetGoalResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geobot_navigation/SetGoalResult";
  }

  static const char* value(const ::geobot_navigation::SetGoalResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
";
  }

  static const char* value(const ::geobot_navigation::SetGoalResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetGoalResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::geobot_navigation::SetGoalResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::geobot_navigation::SetGoalResult_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // GEOBOT_NAVIGATION_MESSAGE_SETGOALRESULT_H
