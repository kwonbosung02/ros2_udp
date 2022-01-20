
#include <ros/ros.h>

#include <chrono>
#include <memory>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#include <more_interfaces/defines.h>
#include <UdpPacket.h>


#define BUFSIZE 10

using namespace std::chrono_literals;

int frequency = 4000;

std::string print_str(float arr[]);

int main(int argc, char **argv){
    
    ros::init(argc, argv, "udp_receive");
    ros::NodeHandle nh;

    int serverFd, clientFd;
    struct sockaddr_in serverAddr, clientAddr;
    float recvBuffer[BUFSIZE];
    int clientAddrSize;
    ssize_t receivedBytes;

    ros::Publisher pub = nh.advertise<ros1_src::UdpPacket>("udp_receive", 1000);

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(UDP_RECEIVE_PORT);

    if((serverFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        ROS_INFO("Fail to open socket");
        return -1;
    }

    if(bind(serverFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){
        ROS_INFO("Fail to bind server addr");
        return -1;
    }

    ROS_INFO("loop start");
    ros::Rate loop_rate(frequency);

    while (ros::ok()){
        receivedBytes = recvfrom(serverFd, recvBuffer, BUFSIZE * 4, 0, (struct sockaddr*)&clientAddr, (unsigned int *)&clientAddrSize);
        
        if(receivedBytes == 0) continue;
        else if(receivedBytes < 0){
            ROS_INFO("error");
            return -1;
        }
        std::string result = print_str(recvBuffer);
        ROS_INFO(result.c_str());

        
        auto message = ros1_src::UdpPacket();
        ros::Time current_time = ros::Time::now();
        message.send_data = current_time.toSec();

        pub.publish(message);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

std::string print_str(float arr[]){
    std::string s = "[";
    for(int i = 0; i < BUFSIZE; i++){
        s = s + std::to_string(arr[i]) + " ";
    }
    s += "]";

    return s;
}
