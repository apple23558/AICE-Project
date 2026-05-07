// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_robot_msgs:msg/CustomMessage.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__BUILDER_HPP_
#define MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_robot_msgs/msg/detail/custom_message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_CustomMessage_pose
{
public:
  explicit Init_CustomMessage_pose(::my_robot_msgs::msg::CustomMessage & msg)
  : msg_(msg)
  {}
  ::my_robot_msgs::msg::CustomMessage pose(::my_robot_msgs::msg::CustomMessage::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_msgs::msg::CustomMessage msg_;
};

class Init_CustomMessage_sensor_readings
{
public:
  explicit Init_CustomMessage_sensor_readings(::my_robot_msgs::msg::CustomMessage & msg)
  : msg_(msg)
  {}
  Init_CustomMessage_pose sensor_readings(::my_robot_msgs::msg::CustomMessage::_sensor_readings_type arg)
  {
    msg_.sensor_readings = std::move(arg);
    return Init_CustomMessage_pose(msg_);
  }

private:
  ::my_robot_msgs::msg::CustomMessage msg_;
};

class Init_CustomMessage_name
{
public:
  explicit Init_CustomMessage_name(::my_robot_msgs::msg::CustomMessage & msg)
  : msg_(msg)
  {}
  Init_CustomMessage_sensor_readings name(::my_robot_msgs::msg::CustomMessage::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_CustomMessage_sensor_readings(msg_);
  }

private:
  ::my_robot_msgs::msg::CustomMessage msg_;
};

class Init_CustomMessage_is_active
{
public:
  Init_CustomMessage_is_active()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CustomMessage_name is_active(::my_robot_msgs::msg::CustomMessage::_is_active_type arg)
  {
    msg_.is_active = std::move(arg);
    return Init_CustomMessage_name(msg_);
  }

private:
  ::my_robot_msgs::msg::CustomMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_msgs::msg::CustomMessage>()
{
  return my_robot_msgs::msg::builder::Init_CustomMessage_is_active();
}

}  // namespace my_robot_msgs

#endif  // MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__BUILDER_HPP_
