// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_robot_msgs:msg/CustomMessage.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__STRUCT_H_
#define MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"
// Member 'sensor_readings'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/CustomMessage in the package my_robot_msgs.
typedef struct my_robot_msgs__msg__CustomMessage
{
  bool is_active;
  rosidl_runtime_c__String name;
  rosidl_runtime_c__double__Sequence sensor_readings;
  geometry_msgs__msg__Pose pose;
} my_robot_msgs__msg__CustomMessage;

// Struct for a sequence of my_robot_msgs__msg__CustomMessage.
typedef struct my_robot_msgs__msg__CustomMessage__Sequence
{
  my_robot_msgs__msg__CustomMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_robot_msgs__msg__CustomMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_ROBOT_MSGS__MSG__DETAIL__CUSTOM_MESSAGE__STRUCT_H_
