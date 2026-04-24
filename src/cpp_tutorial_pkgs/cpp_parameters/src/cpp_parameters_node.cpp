#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>


using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam() : Node("minimal_param_node")
  {
    // (Optional) Add a description
    auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
    param_desc.description = "This parameter is mine!";

    // Create parameter ("my_parameter") with default value ("world")
    // - Parameter type inferred from default value in this case a string
    this->declare_parameter("my_parameter", "world", param_desc);

    timer_ = this->create_wall_timer(1s, [this]() { timer_callback(); });
  }

  void timer_callback()
  {
    std::string my_param = this->get_parameter("my_parameter").as_string();

    RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());

    // Set param back to default "world" in the case a user changed param externally
    std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", "world")};
    this->set_parameters(all_new_parameters);
  }


private:
  rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  
  auto node = std::make_shared<MinimalParam>();

  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}