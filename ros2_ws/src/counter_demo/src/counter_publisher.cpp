#include <chrono>
#include <cstdint>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int32.hpp"

using namespace std::chrono_literals;

// Publishes an increasing counter 1, 2, 3... on the "counter" topic
class CounterPublisher : public rclcpp::Node
{
public:
  CounterPublisher()
  : Node("counter_publisher")
  {
    publisher_ = create_publisher<std_msgs::msg::UInt32>("counter", 10);
    timer_ = create_wall_timer(1s, [this]() {on_timer();});
  }

private:
  void on_timer()
  {
    std_msgs::msg::UInt32 msg;
    msg.data = ++count_;
    RCLCPP_INFO(get_logger(), "Publishing: %u", msg.data);
    publisher_->publish(msg);
  }

  rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  uint32_t count_{0};
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CounterPublisher>());
  rclcpp::shutdown();
  return 0;
}
