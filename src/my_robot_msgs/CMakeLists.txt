cmake_minimum_required(VERSION 3.8)
project(my_robot_msgs)

if(CMAKE_COMPILER_VERSION VERSION_LESS 8)
  find_package(ament_cmake REQUIRED)
else()
  find_package(ament_cmake REQUIRED)
endif()

find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/CustomMessage.msg"
  DEPENDENCIES std_msgs geometry_msgs
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()