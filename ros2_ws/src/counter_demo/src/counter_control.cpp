#include <chrono>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

using namespace std::chrono_literals;
using SetBool = std_srvs::srv::SetBool;

// Calls the counter/enable service once: "start" resumes the counter, "stop" stops it
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  // Drop --ros-args ... so that only our own arguments are left
  const std::vector<std::string> args = rclcpp::remove_ros_arguments(argc, argv);
  if (args.size() != 2 || (args[1] != "start" && args[1] != "stop")) {
    std::fprintf(stderr, "Usage: ros2 run counter_demo counter_control start|stop\n");
    rclcpp::shutdown();
    return 1;
  }

  auto node = rclcpp::Node::make_shared("counter_control");
  auto client = node->create_client<SetBool>("counter/enable");

  if (!client->wait_for_service(5s)) {
    RCLCPP_ERROR(node->get_logger(), "Service /counter/enable is not available");
    rclcpp::shutdown();
    return 1;
  }

  auto request = std::make_shared<SetBool::Request>();
  request->data = (args[1] == "start");

  auto future = client->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node, future, 5s) !=
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_ERROR(node->get_logger(), "No response from /counter/enable");
    rclcpp::shutdown();
    return 1;
  }

  const auto response = future.get();
  RCLCPP_INFO(node->get_logger(), "%s", response->message.c_str());

  rclcpp::shutdown();
  return response->success ? 0 : 1;
}
