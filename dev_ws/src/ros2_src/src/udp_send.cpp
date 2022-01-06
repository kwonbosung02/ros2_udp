#include <chrono>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../include/more_interfaces/defines.h"

#include "rclcpp/rclcpp.hpp"
#include "ros2_src/msg/udp_packet.hpp"



class UdpSendSubscriber : public rclcpp::Node
{
public:
    UdpSendSubscriber() : Node("udp_send_server") {
        subscription_ = this->create_subscription<ros2_src::msg::UdpPacket>(
                "udp_send", 10, std::bind(&UdpSendSubscriber::send_udp_packet, this, std::placeholders::_1));
        
        RCLCPP_INFO(this->get_logger(), "Wait for packet...");

        if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            RCLCPP_INFO(this->get_logger(), "Fail to open socket");
            return;
        }

    }

private:
    void send_udp_packet(const ros2_src::msg::UdpPacket::SharedPtr msg) const
    {
        struct sockaddr_in servAddr;
        memset(&servAddr, 0, sizeof(servAddr));

        servAddr.sin_family = AF_INET;
        inet_aton(msg->ip.c_str(), (struct in_addr*)&servAddr.sin_addr.s_addr);
        servAddr.sin_port = htons(msg->port_num);
        
        float sending_data[120];

        for(int i = 0; i < 120; i++){
            sending_data[i] = i+ 1.001;
        }

        if ( sendto(sockfd, sending_data, sizeof(sending_data),0, (struct sockaddr *) &servAddr, sizeof(servAddr)) != sizeof(sending_data)){
            RCLCPP_INFO(this->get_logger(), "Fail to send socket");
            return;
        }
        RCLCPP_INFO(this->get_logger(), msg->send_data.c_str());
 
    }
    rclcpp::Subscription<ros2_src::msg::UdpPacket>::SharedPtr subscription_;

    int sockfd;
};

int main(int argc, char * argv[])
{

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<UdpSendSubscriber>());
    rclcpp::shutdown();


    return 0;
}