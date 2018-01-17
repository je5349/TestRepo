// Generated by gencpp from file geobot_navigation_rupes/PathResponse.msg
// DO NOT EDIT!


#ifndef GEOBOT_NAVIGATION_RUPES_MESSAGE_PATHRESPONSE_H
#define GEOBOT_NAVIGATION_RUPES_MESSAGE_PATHRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace geobot_navigation_rupes
{
template <class ContainerAllocator>
struct PathResponse_
{
  typedef PathResponse_<ContainerAllocator> Type;

  PathResponse_()
    : path1(0.0)
    , path2(0.0)  {
    }
  PathResponse_(const ContainerAllocator& _alloc)
    : path1(0.0)
    , path2(0.0)  {
  (void)_alloc;
    }



   typedef float _path1_type;
  _path1_type path1;

   typedef float _path2_type;
  _path2_type path2;




  typedef boost::shared_ptr< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> const> ConstPtr;

}; // struct PathResponse_

typedef ::geobot_navigation_rupes::PathResponse_<std::allocator<void> > PathResponse;

typedef boost::shared_ptr< ::geobot_navigation_rupes::PathResponse > PathResponsePtr;
typedef boost::shared_ptr< ::geobot_navigation_rupes::PathResponse const> PathResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace geobot_navigation_rupes

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geobot_navigation_rupes': ['/home/administrator/sensors_ws/src/geobot_navigation_rupes/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b40a6ad35cdcf00149f9f8ec0f355bf3";
  }

  static const char* value(const ::geobot_navigation_rupes::PathResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb40a6ad35cdcf001ULL;
  static const uint64_t static_value2 = 0x49f9f8ec0f355bf3ULL;
};

template<class ContainerAllocator>
struct DataType< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geobot_navigation_rupes/PathResponse";
  }

  static const char* value(const ::geobot_navigation_rupes::PathResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 path1\n\
float32 path2\n\
\n\
";
  }

  static const char* value(const ::geobot_navigation_rupes::PathResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.path1);
      stream.next(m.path2);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PathResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::geobot_navigation_rupes::PathResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::geobot_navigation_rupes::PathResponse_<ContainerAllocator>& v)
  {
    s << indent << "path1: ";
    Printer<float>::stream(s, indent + "  ", v.path1);
    s << indent << "path2: ";
    Printer<float>::stream(s, indent + "  ", v.path2);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GEOBOT_NAVIGATION_RUPES_MESSAGE_PATHRESPONSE_H
