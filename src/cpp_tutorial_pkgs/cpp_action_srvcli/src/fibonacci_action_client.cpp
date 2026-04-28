#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "action_tutorials_interfaces/action/fibonacci.hpp"


class FibonacciActionClient : public rclcpp::Node
{
public:
  using Fibonacci = action_tutorials_interfaces::action::Fibonacci;
  using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

  explicit FibonacciActionClient(const rclcpp::NodeOptions& options = rclcpp::NodeOptions())
  : Node("fibonacci_action_client", options)
  {
    // Create new action client which uses the /fibonacci action
    this->client_ptr_ = rclcpp_action::create_client<Fibonacci>(
      this,
      "fibonacci");
    
    // Timer of 500ms call to send_goal() callback
    // - Note: Will only be called once. send_goal() will cancel the timer
    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      [this]() {this->send_goal();}
    );
  }


  void send_goal()
  {
    this->timer_->cancel(); // Cancel timer

    if (!this->client_ptr_->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = Fibonacci::Goal();
    goal_msg.order = 10;

    RCLCPP_INFO(this->get_logger(), "Sending goal");

    // Create goal response, feedback, and result callbacks
    auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();

    send_goal_options.goal_response_callback = [this](
      const GoalHandleFibonacci::SharedPtr& goal_handle)
    {
      this->goal_response_callback(goal_handle);
    };
    
    send_goal_options.feedback_callback = [this](
      GoalHandleFibonacci::SharedPtr goal_handle,
      const std::shared_ptr<const Fibonacci::Feedback> feedback)
    {
      this->feedback_callback(goal_handle, feedback);
    };

    send_goal_options.result_callback = [this](const GoalHandleFibonacci::WrappedResult& result) {
      this->result_callback(result);
    };
    
    // Send goal to action
    this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
  }

private:
  // Callback occurs when goal is rejected or accepted
  void goal_response_callback(const GoalHandleFibonacci::SharedPtr& goal_handle)
  {
    // Checks if goal was accepted or rejected by the action server
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
  }

  // Callback occurs for every new feedback from action
  void feedback_callback(
    GoalHandleFibonacci::SharedPtr /* goal_handle */,
    const std::shared_ptr<const Fibonacci::Feedback> feedback)
  {
    std::stringstream ss;
    ss << "Next number in sequence received: ";
    for (auto number : feedback->partial_sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
  }

  // Callback occurs when result status is ready
  void result_callback(const GoalHandleFibonacci::WrappedResult& result)
  {
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }
    // If goal succeeded log action result
    std::stringstream ss;
    ss << "Result received: ";
    for (auto number : result.result->sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
    rclcpp::shutdown(); // Shutdown ROS2 communication
  }

  rclcpp_action::Client<Fibonacci>::SharedPtr client_ptr_;
  rclcpp::TimerBase::SharedPtr timer_;
};  // class FibonacciActionClient


int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FibonacciActionClient>());
  return 0;
}
