/*
This file creates a service server node similar to how the python version in the ROS2 tutorials
creates it. It does not do it exactly how it is done in the C++ tutorial. This implementation is
easier for me to understand.
*/
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using AddTwoInts = example_interfaces::srv::AddTwoInts;

class MinimalServer : public rclcpp::Node
{
public:
  // Constructor
  MinimalServer() : Node("minimal_server")
  {
    // Create service server
    server = this->create_service<AddTwoInts>("add_two_ints", 
      // Callback as a lambda function
      [this] (
        const AddTwoInts::Request::SharedPtr request,
        AddTwoInts::Response::SharedPtr response) { this->server_callback(request, response); });
  }


private:
  // Server callback
  void server_callback(
    const AddTwoInts::Request::SharedPtr request,
    AddTwoInts::Response::SharedPtr response)
  {
    // Populate service response
    response->sum = request->a + request->b;

    RCLCPP_INFO_STREAM(this->get_logger(),
      "Incoming request\na: " << request->a << " b: " << request->b);
    RCLCPP_INFO_STREAM(this->get_logger(), "sending back response: [" << response->sum << "]");
  }

  rclcpp::Service<AddTwoInts>::SharedPtr server;
};


int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<MinimalServer>();
  
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}