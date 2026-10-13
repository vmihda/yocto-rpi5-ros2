cmake_minimum_required(VERSION 3.8)
project(counter_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(counter_publisher src/counter_publisher.cpp)
ament_target_dependencies(counter_publisher rclcpp std_msgs std_srvs)

add_executable(counter_subscriber src/counter_subscriber.cpp)
ament_target_dependencies(counter_subscriber rclcpp std_msgs)

add_executable(counter_control src/counter_control.cpp)
ament_target_dependencies(counter_control rclcpp std_srvs)

install(TARGETS
  counter_publisher
  counter_subscriber
  counter_control
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
