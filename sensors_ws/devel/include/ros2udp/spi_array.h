// Generated by gencpp from file ros2udp/spi_array.msg
// DO NOT EDIT!


#ifndef ROS2UDP_MESSAGE_SPI_ARRAY_H
#define ROS2UDP_MESSAGE_SPI_ARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ros2udp
{
template <class ContainerAllocator>
struct spi_array_
{
  typedef spi_array_<ContainerAllocator> Type;

  spi_array_()
    : spi_array()  {
      spi_array.assign(0);
  }
  spi_array_(const ContainerAllocator& _alloc)
    : spi_array()  {
  (void)_alloc;
      spi_array.assign(0);
  }



   typedef boost::array<int16_t, 200>  _spi_array_type;
  _spi_array_type spi_array;




  typedef boost::shared_ptr< ::ros2udp::spi_array_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros2udp::spi_array_<ContainerAllocator> const> ConstPtr;

}; // struct spi_array_

typedef ::ros2udp::spi_array_<std::allocator<void> > spi_array;

typedef boost::shared_ptr< ::ros2udp::spi_array > spi_arrayPtr;
typedef boost::shared_ptr< ::ros2udp::spi_array const> spi_arrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros2udp::spi_array_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros2udp::spi_array_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ros2udp

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'ros2udp': ['/home/administrator/sensors_ws/src/ros2udp/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ros2udp::spi_array_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros2udp::spi_array_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros2udp::spi_array_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros2udp::spi_array_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros2udp::spi_array_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros2udp::spi_array_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros2udp::spi_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a07e4f811e0030cb667022828fa40185";
  }

  static const char* value(const ::ros2udp::spi_array_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa07e4f811e0030cbULL;
  static const uint64_t static_value2 = 0x667022828fa40185ULL;
};

template<class ContainerAllocator>
struct DataType< ::ros2udp::spi_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros2udp/spi_array";
  }

  static const char* value(const ::ros2udp::spi_array_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros2udp::spi_array_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int16[200] spi_array\n\
";
  }

  static const char* value(const ::ros2udp::spi_array_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros2udp::spi_array_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.spi_array);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct spi_array_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros2udp::spi_array_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros2udp::spi_array_<ContainerAllocator>& v)
  {
    s << indent << "spi_array[]" << std::endl;
    for (size_t i = 0; i < v.spi_array.size(); ++i)
    {
      s << indent << "  spi_array[" << i << "]: ";
      Printer<int16_t>::stream(s, indent + "  ", v.spi_array[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS2UDP_MESSAGE_SPI_ARRAY_H
