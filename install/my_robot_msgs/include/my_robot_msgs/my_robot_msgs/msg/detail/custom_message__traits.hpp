// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_robot_msgs:msg/CustomMessage.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__TRAITS_HPP_
#define MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_robot_msgs/msg/detail/custom_message__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace my_robot_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CustomMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: is_active
  {
    out << "is_active: ";
    rosidl_generator_traits::value_to_yaml(msg.is_active, out);
    out << ", ";
  }

  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: sensor_readings
  {
    if (msg.sensor_readings.size() == 0) {
      out << "sensor_readings: []";
    } else {
      out << "sensor_readings: [";
      size_t pending_items = msg.sensor_readings.size();
      for (auto item : msg.sensor_readings) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CustomMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: is_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_active: ";
    rosidl_generator_traits::value_to_yaml(msg.is_active, out);
    out << "\n";
  }

  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: sensor_readings
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.sensor_readings.size() == 0) {
      out << "sensor_readings: []\n";
    } else {
      out << "sensor_readings:\n";
      for (auto item : msg.sensor_readings) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CustomMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace my_robot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use my_robot_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_robot_msgs::msg::CustomMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_robot_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_robot_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_robot_msgs::msg::CustomMessage & msg)
{
  return my_robot_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_robot_msgs::msg::CustomMessage>()
{
  return "my_robot_msgs::msg::CustomMessage";
}

template<>
inline const char * name<my_robot_msgs::msg::CustomMessage>()
{
  return "my_robot_msgs/msg/CustomMessage";
}

template<>
struct has_fixed_size<my_robot_msgs::msg::CustomMessage>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<my_robot_msgs::msg::CustomMessage>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<my_robot_msgs::msg::CustomMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__TRAITS_HPP_
