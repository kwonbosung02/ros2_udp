// Generated by gencpp from file ros1_src/UdpPacket.msg
// DO NOT EDIT!


#ifndef ROS1_SRC_MESSAGE_UDPPACKET_H
#define ROS1_SRC_MESSAGE_UDPPACKET_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ros1_src
{
template <class ContainerAllocator>
struct UdpPacket_
{
  typedef UdpPacket_<ContainerAllocator> Type;

  UdpPacket_()
    : send_data()  {
    }
  UdpPacket_(const ContainerAllocator& _alloc)
    : send_data(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _send_data_type;
  _send_data_type send_data;





  typedef boost::shared_ptr< ::ros1_src::UdpPacket_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros1_src::UdpPacket_<ContainerAllocator> const> ConstPtr;

}; // struct UdpPacket_

typedef ::ros1_src::UdpPacket_<std::allocator<void> > UdpPacket;

typedef boost::shared_ptr< ::ros1_src::UdpPacket > UdpPacketPtr;
typedef boost::shared_ptr< ::ros1_src::UdpPacket const> UdpPacketConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros1_src::UdpPacket_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros1_src::UdpPacket_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::ros1_src::UdpPacket_<ContainerAllocator1> & lhs, const ::ros1_src::UdpPacket_<ContainerAllocator2> & rhs)
{
  return lhs.send_data == rhs.send_data;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::ros1_src::UdpPacket_<ContainerAllocator1> & lhs, const ::ros1_src::UdpPacket_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace ros1_src

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::ros1_src::UdpPacket_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros1_src::UdpPacket_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros1_src::UdpPacket_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros1_src::UdpPacket_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros1_src::UdpPacket_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros1_src::UdpPacket_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros1_src::UdpPacket_<ContainerAllocator> >
{
  static const char* value()
  {
    return "66f15e8e1feaafef5c45e0cc00410a21";
  }

  static const char* value(const ::ros1_src::UdpPacket_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x66f15e8e1feaafefULL;
  static const uint64_t static_value2 = 0x5c45e0cc00410a21ULL;
};

template<class ContainerAllocator>
struct DataType< ::ros1_src::UdpPacket_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros1_src/UdpPacket";
  }

  static const char* value(const ::ros1_src::UdpPacket_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros1_src::UdpPacket_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string send_data\n"
"#uint8 len\n"
"##string ip\n"
"#uint16 port_num\n"
;
  }

  static const char* value(const ::ros1_src::UdpPacket_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros1_src::UdpPacket_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.send_data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct UdpPacket_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros1_src::UdpPacket_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros1_src::UdpPacket_<ContainerAllocator>& v)
  {
    s << indent << "send_data: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.send_data);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS1_SRC_MESSAGE_UDPPACKET_H
