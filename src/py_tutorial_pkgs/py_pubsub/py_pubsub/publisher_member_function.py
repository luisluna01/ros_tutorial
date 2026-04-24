import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('minimal_publisher')

        self.publisher_ = self.create_publisher(String, 'topic', 10)
        self.timer_ = self.create_timer(0.5, self.timer_callback)
        
        self.count = 0
    
    def timer_callback(self):
        self.msg = String()

        self.msg.data = f"hello world: {self.count}"
        self.count += 1

        self.get_logger().info(f'publishing "{self.msg.data}"')
        
        self.publisher_.publish(self.msg)


def main(args=None):
    rclpy.init(args=args)
    node = MinimalPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()