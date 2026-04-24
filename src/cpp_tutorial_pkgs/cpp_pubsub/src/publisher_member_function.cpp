#include <chrono>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


using namespace std::literals::chrono_literals;

// Create node
class MinimalPublisher: public rclcpp::Node
{
public:
  // Constructor
  MinimalPublisher()
  : Node("minimal_publisher"), count(0) // Initializer list
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10); // Create publisher
    
    // Create timer
    timer_ = this->create_wall_timer(
      500ms,
      [this]() { timer_callback(); } // use lambda instead of binder
    );
  }

private:
  // Create callback for timer
  void timer_callback() {
    // Create and populate msg
    std_msgs::msg::String msg;
    msg.data = "Hello World: " + std::to_string(count++);

    publisher_->publish(msg); // Publish msg

    RCLCPP_INFO(this->get_logger(), "Publishing: \"%s\"", msg.data.c_str());
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  
  int count;
};


int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv); // Initialize ROS2 communication
  std::shared_ptr<MinimalPublisher> node = std::make_shared<MinimalPublisher>(); // Create node
  rclcpp::spin(node); // Spin node
  rclcpp::shutdown(); // Shutdown ROS2 communication

  return 0;
}