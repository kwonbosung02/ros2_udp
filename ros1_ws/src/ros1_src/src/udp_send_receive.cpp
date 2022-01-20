#include <chrono>
#include <memory>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include <more_interfaces/defines.h>

#include <ros/ros.h>
#include <UdpPacket.h>


using namespace std::chrono_literals;
using namespace std;

ofstream writeFile;
int frequency = 10;

void udp_receive_packet(const ros1_src::UdpPacket::ConstPtr& msg){
    ros::Time current_time = ros::Time::now();
    writeFile << "Sub: " << std::to_string(current_time.toSec()) << "\n";
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "udp_send_receive");
    ros::NodeHandle nh;

    writeFile.open("io.txt");

    ros::Rate loop_rate(frequency);
    ros::Publisher pub = nh.advertise<ros1_src::UdpPacket>("udp_send", 1000);
    ros::Subscriber sub = nh.subscribe("udp_receive", 1000, udp_receive_packet);
    
    while(ros::ok()){

       
        ros::Time current_time = ros::Time::now();

        auto message = ros1_src::UdpPacket();
        string time_ = std::to_string(current_time.toSec());
        message.send_data = time_;
        writeFile << "Pub: " << time_ << "\n";
        pub.publish(message);
        
        ROS_INFO("check");
        ros::spinOnce();
        loop_rate.sleep();
        

    }
}