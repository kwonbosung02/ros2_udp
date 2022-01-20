#include <chrono>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <ros/ros.h>
#include <more_interfaces/defines.h>
#include <UdpPacket.h>

int sockfd;
int frequency = 10;
int cnt =  0;
std::string data;

void send_udp_packet(const ros1_src::UdpPacket::ConstPtr& msg){

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_aton(SIM_IP, (struct in_addr*)&servAddr.sin_addr.s_addr);
    servAddr.sin_port = htons(UDP_SEND_PORT);

    float sending_data[120];

    for(int i = 0; i < 120; i++){
        sending_data[i] = i + 1.001 + cnt;
    }
    
    if( sendto(sockfd, sending_data, sizeof(sending_data), 0, (struct sockaddr *) &servAddr, sizeof(servAddr)) != sizeof(sending_data)){
        ROS_INFO("Fail to send socket");
        return ;
    }
    ROS_INFO("sent");
    cnt++;

}
int main(int argc, char **argv){
    ros::init(argc, argv, "udp_send");
    ros::NodeHandle nh;

    ROS_INFO("waiting...");

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        ROS_INFO("Fail to open socket");
        return -1;
    }
    
    ros::Subscriber sub = nh.subscribe("udp_send", 1000, send_udp_packet);
    ros::spin();
    return 0;
}