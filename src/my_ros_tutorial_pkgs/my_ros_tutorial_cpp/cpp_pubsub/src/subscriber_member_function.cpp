#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscriber_ = this->create_subscription<std_msgs::msg::String>(
      "topic",
      10,
      // Used lambda instead of binder 
      [this](const std_msgs::msg::String& msg) {
        subscriber_callback(msg);
      }
    );
  }


private:
  void subscriber_callback(const std_msgs::msg::String& msg) {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  std::shared_ptr<MinimalSubscriber> node = std::make_shared<MinimalSubscriber>(); // Create node
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}