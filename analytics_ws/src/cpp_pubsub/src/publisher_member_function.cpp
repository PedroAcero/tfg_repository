// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_msgs/msg/u_int8_multi_array.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0), msg_size_(0) {

    this->declare_parameter("publish_frequency", 500);
    this->declare_parameter("message_size", 1024); // Tamaño en bytes
    this->declare_parameter("topic_name", "topic");

    int frequency_ms = this->get_parameter("publish_frequency").as_int();
    size_t message_size = this->get_parameter("message_size").as_int();
    std::string topic_name_ = this->get_parameter("topic_name").as_string();

    publisher_ =
        this->create_publisher<std_msgs::msg::UInt8MultiArray>(topic_name_, 10);
    publisher_expected_ =
        this->create_publisher<std_msgs::msg::String>("expected_data", 10);

    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(frequency_ms),
        std::bind(&MinimalPublisher::timer_callback, this));

    data_vector_.resize(message_size, 1);
  }

private:
  void timer_callback() {
    // auto message = std_msgs::msg::String();
    // message.data = "Hello, world! " + std::to_string(count_++);
    // msg_size_ = message.data.size();
    // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'",
    // message.data.c_str()); publisher_->publish(message);
    // expected_publisher();

    // auto message = std_msgs::msg::UInt8();
    // message.data = static_cast<uint8_t>(count_++);
    // msg_size_ = sizeof(message.data); // En bytes
    // RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data);
    // publisher_->publish(message);
    // expected_publisher();

    auto message = std_msgs::msg::UInt8MultiArray();
    message.data = data_vector_;
    RCLCPP_INFO(this->get_logger(), "Publishing message of size: %zu bytes",
                data_vector_.size());
    msg_size_ = message.data.size();
    publisher_->publish(message);
    expected_publisher();
  }

  void expected_publisher() {
    auto message = std_msgs::msg::String();
    message.data = "Expected number of messages: " + std::to_string(++count_) +
                   "\nExpected size of message:" + std::to_string(msg_size_);
    publisher_expected_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr publisher_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_expected_;

  size_t count_;
  size_t msg_size_;
  std::vector<uint8_t> data_vector_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
