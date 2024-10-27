#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;

class ArmControllerNode : public rclcpp::Node
{
public:
    ArmControllerNode() : Node("arm_controller_node")
    {
        joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "joint_states", 10, std::bind(&ArmControllerNode::jointStateCallback, this, std::placeholders::_1));
        
        position_command_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/position_controller/command", 10);
        
        timer_ = this->create_wall_timer(
            500ms, std::bind(&ArmControllerNode::publishPositionCommand, this));
    }

private:

    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Current Joint Positions:");
        for (size_t i = 0; i < msg->name.size(); ++i)
        {
            RCLCPP_INFO(this->get_logger(), "Joint: %s, Position: %f", msg->name[i].c_str(), msg->position[i]);
        }
    }

    void publishPositionCommand()
    {
        auto command_msg = std_msgs::msg::Float64MultiArray();

        command_msg.data = {0.2, 0.2, 0.2, 0.2};

        RCLCPP_INFO(this->get_logger(), "Publishing position command.");
        position_command_publisher_->publish(command_msg);
    }

    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr position_command_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ArmControllerNode>());
    rclcpp::shutdown();
    return 0;
}

