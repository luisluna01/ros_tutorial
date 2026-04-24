import sys

import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts


class MinimalClientAsync(Node):

    def __init__(self):
        super().__init__('minimal_client_async')
        self.client = self.create_client(AddTwoInts, 'add_two_ints')

        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
    
    def send_request(self, a_, b_):
        self.request = AddTwoInts.Request()
        self.request.a = a_
        self.request.b = b_

        return self.client.call_async(self.request)


def main():
    arg1 = int(sys.argv[1])
    arg2 = int(sys.argv[2])

    rclpy.init()
    
    client_node = MinimalClientAsync()
    
    future = client_node.send_request(arg1, arg2)
    
    rclpy.spin_until_future_complete(client_node, future)
    response = future.result()
    client_node.get_logger().info(f'Result of add_two_ints: for {arg1} + {arg2} = {response.sum}')
    
    client_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()