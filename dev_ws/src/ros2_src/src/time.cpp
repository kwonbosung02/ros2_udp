#include <fstream>
#include <iostream>

#include "rclcpp/rclcpp.hpp"

using namespace std;
int main(void){
    fstream File("io.txt");
    if(!File){
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"No File Exist");
        return;
    }

}