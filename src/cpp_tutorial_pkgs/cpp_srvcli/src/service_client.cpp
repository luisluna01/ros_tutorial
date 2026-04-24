/*
This file creates a service client node similar to how the python version in the ROS2 tutorials
creates it. It does not do it exactly how it is done in the C++ tutorial. This implementation is
easier for me to understand.
*/
#include <chrono>
#include <cstdlib>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


using namespace std::chrono_literals;
using AddTwoInts = example_interfaces::srv::AddTwoInts;

class MinimalClientAsync : public rclcpp::Node
{
public:
  MinimalClientAsync() : Node("minimal_client_async")
  {
    client = this->create_client<AddTwoInts>("add_two_ints");

    while (!client->wait_for_service(1s)) {
      RCLCPP_WARN(this->get_logger(), "Service not available, waiting again...");
    }
  }

  rclcpp::Client<AddTwoInts>::FutureAndRequestId send_request(int64_t arg1, int64_t arg2) {
    // Create and populate service request
    auto request = std::make_shared<AddTwoInts::Request>();
    request->a = arg1;
    request->b = arg2;

    return client->async_send_request(request); // Send request asynchronously
  }


private:
  rclcpp::Client<AddTwoInts>::SharedPtr client;
};


int main(int argc, char** argv) {
  rclcpp::init(argc, argv);

  // If user did not provide 2 arguements, return error
  if (argc != 3){
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
    rclcpp::shutdown();
    return 1;
  }

  auto node = std::make_shared<MinimalClientAsync>();
  auto future = node->send_request(atoll(argv[1]), atoll(argv[2]));

  // Check if successful
  if (rclcpp::spin_until_future_complete(node, future) == rclcpp::FutureReturnCode::SUCCESS) {
    AddTwoInts::Response::SharedPtr response = future.get(); // Store service response
    RCLCPP_INFO_STREAM(node->get_logger(), "Sum: " << response->sum);
  }
  else {
    RCLCPP_ERROR(node->get_logger(), "Failed to call service: /add_two_ints");
  }

  rclcpp::shutdown();

  return 0;
}