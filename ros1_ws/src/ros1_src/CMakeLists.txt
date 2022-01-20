cmake_minimum_required(VERSION 3.0.2)
project(ros1_src)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(
  FILES
  UdpPacket.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(udp_receive ${PROJECT_SOURCE_DIR}/src/udp_receive.cpp)
add_executable(udp_send_receive ${PROJECT_SOURCE_DIR}/src/udp_send_receive.cpp)

target_link_libraries(udp_receive ${catkin_LIBRARIES})
target_link_libraries(udp_send_receive ${catkin_LIBRARIES})
