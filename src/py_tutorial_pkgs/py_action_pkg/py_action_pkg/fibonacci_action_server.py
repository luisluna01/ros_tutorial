import time

import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

from action_tutorials_interfaces.action import Fibonacci


class FibonacciActionServer(Node):
    def __init__(self):
        super().__init__('fibonacci_action_server') # Name of node
        
        # Use /fibonacci action
        self._action_server = ActionServer(self, Fibonacci, 'fibonacci', self.execute_callback)
    

    # Executes a goal once it is accepted
    def execute_callback(self, goal_handle):
        result_msg = Fibonacci.Result() # Initialize action result
        feedback_msg = Fibonacci.Feedback() # Intialize action feedback

        self.get_logger().info('Executing goal...')
        
        # Compute and publish feedback
        sequence = [0, 1]
        feedback_msg.partial_sequence = [0, 1]
        for i in range(1, goal_handle.request.order):
            # Append partial sequence for feedback
            feedback_msg.partial_sequence.append(
                feedback_msg.partial_sequence[i] + feedback_msg.partial_sequence[i-1]
            )

            self.get_logger().info(f'Feedback: {feedback_msg.partial_sequence}')

            goal_handle.publish_feedback(feedback_msg) # Publish feedback to action

            time.sleep(1) # For dramatic effect

        goal_handle.succeed() # Indicates goal was successful
        
        # Assign sequence and return as result
        result_msg.sequence = feedback_msg.partial_sequence
        return result_msg


def main (args=None):
    rclpy.init(args=args)

    fibonacci_action_server = FibonacciActionServer()
    
    rclpy.spin(fibonacci_action_server)


if __name__ == '__main__':
    main()
