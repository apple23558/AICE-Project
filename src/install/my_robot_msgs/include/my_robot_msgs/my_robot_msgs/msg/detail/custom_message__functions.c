// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_robot_msgs:msg/CustomMessage.idl
// generated code does not contain a copyright notice
#include "my_robot_msgs/msg/detail/custom_message__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `sensor_readings`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
my_robot_msgs__msg__CustomMessage__init(my_robot_msgs__msg__CustomMessage * msg)
{
  if (!msg) {
    return false;
  }
  // is_active
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    my_robot_msgs__msg__CustomMessage__fini(msg);
    return false;
  }
  // sensor_readings
  if (!rosidl_runtime_c__double__Sequence__init(&msg->sensor_readings, 0)) {
    my_robot_msgs__msg__CustomMessage__fini(msg);
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    my_robot_msgs__msg__CustomMessage__fini(msg);
    return false;
  }
  return true;
}

void
my_robot_msgs__msg__CustomMessage__fini(my_robot_msgs__msg__CustomMessage * msg)
{
  if (!msg) {
    return;
  }
  // is_active
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // sensor_readings
  rosidl_runtime_c__double__Sequence__fini(&msg->sensor_readings);
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
}

bool
my_robot_msgs__msg__CustomMessage__are_equal(const my_robot_msgs__msg__CustomMessage * lhs, const my_robot_msgs__msg__CustomMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_active
  if (lhs->is_active != rhs->is_active) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // sensor_readings
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->sensor_readings), &(rhs->sensor_readings)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  return true;
}

bool
my_robot_msgs__msg__CustomMessage__copy(
  const my_robot_msgs__msg__CustomMessage * input,
  my_robot_msgs__msg__CustomMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // is_active
  output->is_active = input->is_active;
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // sensor_readings
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->sensor_readings), &(output->sensor_readings)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  return true;
}

my_robot_msgs__msg__CustomMessage *
my_robot_msgs__msg__CustomMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_msgs__msg__CustomMessage * msg = (my_robot_msgs__msg__CustomMessage *)allocator.allocate(sizeof(my_robot_msgs__msg__CustomMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_robot_msgs__msg__CustomMessage));
  bool success = my_robot_msgs__msg__CustomMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_robot_msgs__msg__CustomMessage__destroy(my_robot_msgs__msg__CustomMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_robot_msgs__msg__CustomMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_robot_msgs__msg__CustomMessage__Sequence__init(my_robot_msgs__msg__CustomMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_msgs__msg__CustomMessage * data = NULL;

  if (size) {
    data = (my_robot_msgs__msg__CustomMessage *)allocator.zero_allocate(size, sizeof(my_robot_msgs__msg__CustomMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_robot_msgs__msg__CustomMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_robot_msgs__msg__CustomMessage__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
my_robot_msgs__msg__CustomMessage__Sequence__fini(my_robot_msgs__msg__CustomMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      my_robot_msgs__msg__CustomMessage__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

my_robot_msgs__msg__CustomMessage__Sequence *
my_robot_msgs__msg__CustomMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_robot_msgs__msg__CustomMessage__Sequence * array = (my_robot_msgs__msg__CustomMessage__Sequence *)allocator.allocate(sizeof(my_robot_msgs__msg__CustomMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_robot_msgs__msg__CustomMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_robot_msgs__msg__CustomMessage__Sequence__destroy(my_robot_msgs__msg__CustomMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_robot_msgs__msg__CustomMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_robot_msgs__msg__CustomMessage__Sequence__are_equal(const my_robot_msgs__msg__CustomMessage__Sequence * lhs, const my_robot_msgs__msg__CustomMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_robot_msgs__msg__CustomMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_robot_msgs__msg__CustomMessage__Sequence__copy(
  const my_robot_msgs__msg__CustomMessage__Sequence * input,
  my_robot_msgs__msg__CustomMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_robot_msgs__msg__CustomMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_robot_msgs__msg__CustomMessage * data =
      (my_robot_msgs__msg__CustomMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_robot_msgs__msg__CustomMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_robot_msgs__msg__CustomMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_robot_msgs__msg__CustomMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
