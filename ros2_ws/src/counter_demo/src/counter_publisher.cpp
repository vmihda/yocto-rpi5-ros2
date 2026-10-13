#include <chrono>
#include <cstdint>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int32.hpp"
#include "std_srvs/srv/set_bool.hpp"

using namespace std::chrono_literals;
using SetBool = std_srvs::srv::SetBool;

// Publishes an increasing counter 1, 2, 3... on the "counter" topic.
// The "counter/enable" service stops (data=false) and resumes (data=true) it.
class CounterPublisher : public rclcpp::Node
{
public:
  CounterPublisher()
  : Node("counter_publisher")
  {
    publisher_ = create_publisher<std_msgs::msg::UInt32>("counter", 10);
    timer_ = create_wall_timer(1s, [this]() {on_timer();});
    service_ = create_service<SetBool>(
      "counter/enable",
      [this](const std::shared_ptr<SetBool::Request> request,
      std::shared_ptr<SetBool::Response> response) {
        on_enable(request, response);
      });
  }

private:
  void on_timer()
  {
    std_msgs::msg::UInt32 msg;
    msg.data = ++count_;
    RCLCPP_INFO(get_logger(), "Publishing: %u", msg.data);
    publisher_->publish(msg);
  }

  void on_enable(
    const std::shared_ptr<SetBool::Request> request,
    std::shared_ptr<SetBool::Response> response)
  {
    if (request->data) {
      // reset() restarts a cancelled timer; the counter value is kept
      if (timer_->is_canceled()) {
        timer_->reset();
      }
      response->message = "counter running";
    } else {
      timer_->cancel();
      response->message = "counter stopped at " + std::to_string(count_);
    }
    response->success = true;
    RCLCPP_INFO(get_logger(), "%s", response->message.c_str());
  }

  rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Service<SetBool>::SharedPtr service_;
  uint32_t count_{0};
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CounterPublisher>());
  rclcpp::shutdown();
  return 0;
}
