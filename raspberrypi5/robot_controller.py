import json

import rclpy
from rclpy.node import Node
from teleop_interface.msg import Teleop
import serial


class RobotController(Node):
    def __init__(self, name):
        super().__init__(name)

        self.subscription = self.create_subscription(
            Teleop,
            'teleop_robot_cmds',
            self.listener_callback,
            10
        )

        self.speed = 255
        self.duration = 100

        self.direction_to_int = {"forward": 0, "backward": 1,"left": 2, "right": 3, "stop": 4}

        self.serial_port = serial.Serial('/dev/ttyUSB1', 115200)

    def listener_callback(self, msg):
        self.get_logger().info(f'Msg received: {msg.direction}')

        direction_ = int(self.direction_to_int[msg.direction])

        request_ = {"speed": self.speed, "duration": self.duration, "direction": direction_}

        print(f'{json.dumps(request_)}')

        self.serial_port.write(f'{json.dumps(request_)}\n'.encode())


def main(args=None):
    rclpy.init(args=args)
    robot_controller = RobotController('robot_controller_node')
    rclpy.spin(robot_controller)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
