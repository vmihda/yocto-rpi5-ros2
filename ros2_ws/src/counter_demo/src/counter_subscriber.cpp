#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int32.hpp"

// Prints every value received on the "counter" topic
class CounterSubscriber : public rclcpp::Node
{
public:
  CounterSubscriber()
  : Node("counter_subscriber")
  {
    subscription_ = create_subscription<std_msgs::msg::UInt32>(
      "counter", 10,
      [this](const std_msgs::msg::UInt32 & msg) {
        RCLCPP_INFO(get_logger(), "Received: %u", msg.data);
      });
  }

private:
  rclcpp::Subscription<std_msgs::msg::UInt32>::SharedPtr subscription_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CounterSubscriber>());
  rclcpp::shutdown();
  return 0;
}
