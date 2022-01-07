#include <chrono>
#include <memory>
#include <time.h>
#include <fstream>
#include <iostream>

#include "../include/more_interfaces/defines.h"

#include "rclcpp/rclcpp.hpp"
#include "ros2_src/msg/udp_packet.hpp"

using namespace std::chrono_literals;
using namespace std;

volatile int dummy;

class UdpSendRecieveNode : public rclcpp::Node
{
public:
    UdpSendRecieveNode()
            : Node("udp_send_server")
    {
        
        publisher_ = this->create_publisher<ros2_src::msg::UdpPacket>("udp_send", 10);

        subscription_ = this->create_subscription<ros2_src::msg::UdpPacket>(
                "udp_receive", 10, std::bind(&UdpSendRecieveNode::udp_receive_packet, this, std::placeholders::_1));

        // open file for logging
        writeFile.open("io.txt");

        dummy = 0;

        // generate send packet every tick
        timer_ = this->create_wall_timer(50ms, std::bind(&UdpSendRecieveNode::timer_callback, this));
        //50ms
    }

private:
    rclcpp::Publisher<ros2_src::msg::UdpPacket>::SharedPtr publisher_;
    rclcpp::Subscription<ros2_src::msg::UdpPacket>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;

    ofstream writeFile;
    ofstream writeFile_;
    void udp_receive_packet(const ros2_src::msg::UdpPacket::SharedPtr msg){
        int port_num = msg->port_num;
        std::stringuuj   bnbnmbmn
        
        
        
        
          
          
           ip = msg->ip;
        std::string data = msg->send_data;

        //RCLCPP_INFO(this->get_logger(), "[Received]\ndata: " + data + "\nip: " + ip + "\nport: " + std::to_string(port_num));

        // compare the packet time and receive time
        rclcpp::Time current_time_ = rclcpp::Node::now();
        //writeFile << data << " " << std::to_string(current_time.seconds()) << "\n";
        writeFile << "Sub: " << std::to_string(current_time_.seconds()) << "\n";

    }

    void timer_callback(){
           
        rclcpp::Time current_time = rclcpp::Node::now();
        auto message = ros2_src::msg::UdpPacket();
        message.send_data = std::to_string(current_time.seconds());
        message.ip = UDP_SERVER_IP;
        message.port_num = UDP_SEND_PORT;
        writeFile << "Pub: " << std::to_string(current_time.seconds()) << "\n";
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.send_data.c_str());
        

        publisher_->publish(message);
    
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<UdpSendRecieveNode>());
    rclcpp::shutdown();

    return 0;
}