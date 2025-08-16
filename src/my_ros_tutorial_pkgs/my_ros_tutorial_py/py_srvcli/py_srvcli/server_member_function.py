import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts


class MinimalServer(Node):
    
    def __init__(self):
        super().__init__('minimal_service')
        self.server = self.create_service(AddTwoInts, 'add_two_ints', self.server_callback)
    
    def server_callback(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info(f'Incoming request\na: {request.a} b: {request.b}')

        return response


def main():
    rclpy.init()
    server_node = MinimalServer()
    rclpy.spin(server_node)
    server_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()