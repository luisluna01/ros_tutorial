import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from action_tutorials_interfaces.action import Fibonacci


class FibonacciActionClient(Node):
    def __init__(self):
        super().__init__('fibonacci_action_client')
        self._action_client = ActionClient(self, Fibonacci, 'fibonacci') # Use /fibonacci action

    
    def send_goal(self, order):
        goal_msg = Fibonacci.Goal() # Intialize action goal msg
        goal_msg.order = order

        # Wait for action server to be available
        self._action_client.wait_for_server()

        # Sends a goal and returns a future that can later be waited on
        # - A future is an object representing the result of an asynchronous operation that hasn't
        #   completed. Its a placeholder for a value that will be recieved later
        # - The future resolves when the action server accepts or rejects the goal request
        self._send_goal_future = self._action_client.send_goal_async(
            goal_msg, # Goal message to be sent to action
            feedback_callback=self.feedback_callback) # Add callback for every action feedback

        # Registers a callback to be executed when task is done
        # - In this case when the goal request is accepted or rejected
        self._send_goal_future.add_done_callback(self.goal_response_callback)

    
    def goal_response_callback(self, future):
        goal_handle = future.result()

        # Return early if goal was rejected
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return
        
        self.get_logger().info('Goal accepted :)')

        # Request result and return result future
        # - Similarly to sending a goal, the future is complete when the result is ready
        self._get_result_future = goal_handle.get_result_async()

        # Register a callback to be executed when the task is done
        # - In this case when the result is ready
        self._get_result_future.add_done_callback(self.get_result_callback)


    def get_result_callback(self, future):
        result = future.result().result
        
        self.get_logger().info(f'Result: {result.sequence}')

        rclpy.shutdown() # Shutdown ROS2 for a clean exit
    

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback

        # Log feedback messages
        self.get_logger().info(f'Recieved feedback: {feedback.partial_sequence}')
    

def main(args=None):
    rclpy.init(args=args)

    action_client = FibonacciActionClient()

    action_client.send_goal(10)

    rclpy.spin(action_client)


if __name__ == '__main__':
    main()
