#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../include/more_interfaces/defines.h"

#include "rclcpp/rclcpp.hpp"
#include "ros2_src/msg/udp_packet.hpp"

#define BUFSIZE         (120)

using namespace std::chrono_literals;

class UdpReceivePublisher : public rclcpp::Node
{
public : UdpReceivePublisher() : Node("udp_receive_server"), count_(0) {
        UdpReceivePublisher(UDP_MY_IP, UDP_RECEIVE_PORT);
    }

    UdpReceivePublisher(std::string ip, int port_num) : Node("udp_receive_server"), count_(0)
    {
        publisher_ = this->create_publisher<ros2_src::msg::UdpPacket>("udp_receive", 10);

        memset(&serverAddr, 0, sizeof(serverAddr));

        // set address and port num
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddr.sin_port = htons(port_num);

        // open socket
        if((serverFd=socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            RCLCPP_INFO(this->get_logger(), "Fail to open socket");
            return;
        }

        // bind info to socket
        if(bind(serverFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            RCLCPP_INFO(this->get_logger(), "Fail to bind server address " + ip);
            return;
        }

        RCLCPP_INFO(this->get_logger(), "loop started");


        // publish udp data indefinitely
        while(1) {
            // receive packet
            receivedBytes = recvfrom(serverFd, recvBuffer, BUFSIZE, 0, (struct sockaddr*)&clientAddr, (unsigned int *)&clientAddrSize);
            rclcpp::Time current_time = rclcpp::Node::now();
            long cur = current_time.nanoseconds();
            RCLCPP_INFO(this->get_logger(),std::to_string(cur));

            if(receivedBytes == 0)  continue;     
            else if(receivedBytes < 0){
                RCLCPP_INFO(this->get_logger(), "Comm error. return.");

                return;
            }

            // make topic
            auto message = ros2_src::msg::UdpPacket();
            message.send_data = std::to_string(cur);
            message.ip = std::string(inet_ntoa(clientAddr.sin_addr));
            message.port_num = port_num;
            RCLCPP_INFO(this->get_logger(),"publish message");
            publisher_->publish(message);
        
        }
    }


private:
    rclcpp::Publisher<ros2_src::msg::UdpPacket>::SharedPtr publisher_;
    size_t count_;

    int serverFd, clientFd;
    struct sockaddr_in serverAddr, clientAddr;
    float recvBuffer[BUFSIZE];
    int clientAddrSize;
    ssize_t receivedBytes;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<UdpReceivePublisher>());
    rclcpp::shutdown();
    return 0;
}