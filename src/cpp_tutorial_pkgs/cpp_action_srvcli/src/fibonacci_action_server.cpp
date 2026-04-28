#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "action_tutorials_interfaces/action/fibonacci.hpp"


class FibonacciActionServer : public rclcpp::Node
{
public:
  using Fibonacci = action_tutorials_interfaces::action::Fibonacci;
  using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

  explicit FibonacciActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions())
  : Node("fibonacci_action_server", options)
  {
    // Create action server of Fibonacci type using "/fibonacci" action with 3 callback methods
    // - Note: Callback methods need to return quickly
    this->action_server_ = rclcpp_action::create_server<Fibonacci>(
      this,
      "fibonacci",
      [this](const rclcpp_action::GoalUUID& uuid, std::shared_ptr<const Fibonacci::Goal> goal)
        {return this->handle_goal(uuid, goal);},
      [this](const std::shared_ptr<GoalHandleFibonacci> goal_handle)
        {return this->handle_cancel(goal_handle);},
      [this](const std::shared_ptr<GoalHandleFibonacci> goal_handle)
        {this->handle_accepted(goal_handle);}
    );
  }


private:
  // Callback decides if goal is accepted or rejected
  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID& uuid, // Goal ID
    std::shared_ptr<const Fibonacci::Goal> goal) // Goal message 
  {
    RCLCPP_INFO(this->get_logger(), "Received goal request with order %d", goal->order);
    (void)uuid; // Suppress unused warning

    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  // Callback decides if a goal is attempted to be cancelled
  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void)goal_handle; // Suppress unused warning

    return rclcpp_action::CancelResponse::ACCEPT;
  }

  // Accepts and processes a new goal
  void handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    // Spins up a new thread to return quickly and avoid blocking executer. Execution process occurs
    // in new thread using execute() method
    std::thread{
      [this, goal_handle]()
        {this->execute(goal_handle);}
    }.detach();
  }

  // Processes one sequence number of the Fibonacci sequence every second publishing a feedback
  // update for each step. When finished processing, it marks the goal_handle as succeeded, and
  // quits
  void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Executing goal");

    rclcpp::Rate loop_rate(1); // Create rate limiter set to 1 Hz

    const auto goal = goal_handle->get_goal();

    auto feedback = std::make_shared<Fibonacci::Feedback>();

    auto& sequence = feedback->partial_sequence;
    sequence.push_back(0);
    sequence.push_back(1);

    auto result = std::make_shared<Fibonacci::Result>();

    for (int i=1; (i<goal->order) && rclcpp::ok(); ++i) {
      // Check if there is a cancel request
      if (goal_handle->is_canceling()) {
        result->sequence = sequence;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        
        return;
      }

      sequence.push_back(sequence[i] + sequence[i-1]); // Update sequence

      goal_handle->publish_feedback(feedback);
      RCLCPP_INFO(this->get_logger(), "Publish feedback");

      loop_rate.sleep(); // Sleep for however long  is needed for iteration to take 1s up until here
    }

    // Set goal state to SUCCEED and give client result msg
    if (rclcpp::ok()) {
      result->sequence = sequence;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
  }

  rclcpp_action::Server<Fibonacci>::SharedPtr action_server_;
};


int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FibonacciActionServer>());
  rclcpp::shutdown();
  return 0;
}
