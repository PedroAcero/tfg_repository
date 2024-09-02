// Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/subscription_options.hpp"

#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_msgs/msg/u_int8_multi_array.hpp"

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rclcpp/qos.hpp"
#include "sensor_msgs/msg/battery_state.hpp"
#include "tf2_msgs/msg/tf_message.hpp"

class MinimalSubscriberWithTopicStatistics : public rclcpp::Node {
public:
  MinimalSubscriberWithTopicStatistics()
      : Node("minimal_subscriber_with_topic_statistics"), count_(0),
        msg_size_(0) {
    rclcpp::QoS qos(
        rclcpp::QoSInitialization::from_rmw(rmw_qos_profile_sensor_data));
    qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
    // manually enable topic statistics via options
    auto options = rclcpp::SubscriptionOptions();
    options.topic_stats_options.state = rclcpp::TopicStatisticsState::Enable;

    // configure the collection window and publish period (default 1s)
    options.topic_stats_options.publish_period = std::chrono::seconds(10);

    // configure the topic name (default '/statistics')
    // options.topic_stats_options.publish_topic = "/topic_statistics"

    this->declare_parameter("topic_name", "topic");
    std::string topic_name_ = this->get_parameter("topic_name").as_string();

    if (topic_name_ == "/drone0/self_localization/pose") {

      auto callback =
          [this](const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
            this->pose_stamped_callback(msg);
          };

      subscription_ =
          this->create_subscription<geometry_msgs::msg::PoseStamped>(
              topic_name_, qos, callback, options);

    } else if (topic_name_ == "/drone0/sensor_measurements/battery") {

      auto callback =
          [this](const sensor_msgs::msg::BatteryState::SharedPtr msg) {
            this->battery_state_callback(msg);
          };

      subscription_ = this->create_subscription<sensor_msgs::msg::BatteryState>(
          topic_name_, qos, callback, options);

    } else if (topic_name_ == "/tf") {

      auto callback = [this](const tf2_msgs::msg::TFMessage::SharedPtr msg) {
        this->tf2_callback(msg);
      };

      subscription_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
          topic_name_, qos, callback, options);
    } else {

      auto callback =
          [this](const std_msgs::msg::UInt8MultiArray::SharedPtr msg) {
            this->topic_callback(msg);
          };

      subscription_ = this->create_subscription<std_msgs::msg::UInt8MultiArray>(
          topic_name_, 10, callback, options);

      publisher_received_ =
          this->create_publisher<std_msgs::msg::String>("received_data", 10);
    }
  }

private:
  void topic_callback(const std_msgs::msg::UInt8MultiArray::SharedPtr msg) {
    ++count_;
    msg_size_ = msg->data.size();

    RCLCPP_INFO(this->get_logger(), "I heard a message of size: '%zu' bytes",
                msg_size_);
    publish_received();
  }

  void publish_received() {
    auto message = std_msgs::msg::String();
    message.data = "Total messages received: " + std::to_string(count_) +
                   "\nData size received: " + std::to_string(msg_size_) +
                   " bytes";
    publisher_received_->publish(message);
  }

  void
  pose_stamped_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {

    ++count_;
    // Estimar el tamaño del mensaje PoseStamped
    msg_size_ = sizeof(msg->pose.position.x) + sizeof(msg->pose.position.y) +
                sizeof(msg->pose.position.z) + sizeof(msg->pose.orientation.x) +
                sizeof(msg->pose.orientation.y) +
                sizeof(msg->pose.orientation.z) +
                sizeof(msg->pose.orientation.w);

    RCLCPP_INFO(this->get_logger(), " %zu PoseStamped() messages received!!",
                count_);
    RCLCPP_INFO(this->get_logger(), "\nData size: %zu", msg_size_);
  }

  void
  battery_state_callback(const sensor_msgs::msg::BatteryState::SharedPtr msg) {

    ++count_;
    // Estimar el tamaño del mensaje BatteryState
    msg_size_ =
        sizeof(msg->voltage) + sizeof(msg->current) + sizeof(msg->percentage);

    RCLCPP_INFO(this->get_logger(), "%zu BatteryState() messages received!!",
                count_);
    RCLCPP_INFO(this->get_logger(), "\nData size: %zu", msg_size_);
  }

  void tf2_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {

    ++count_;
    // Estimar el tamaño del mensaje TFMessage
    msg_size_ = 0;
    for (const auto &transform : msg->transforms) {
      msg_size_ += sizeof(transform.transform.translation.x) +
                   sizeof(transform.transform.translation.y) +
                   sizeof(transform.transform.translation.z) +
                   sizeof(transform.transform.rotation.x) +
                   sizeof(transform.transform.rotation.y) +
                   sizeof(transform.transform.rotation.z) +
                   sizeof(transform.transform.rotation.w);
    }

    RCLCPP_INFO(this->get_logger(), "%zu tf2 messages received!!", count_);
    RCLCPP_INFO(this->get_logger(), "\nData size: %zu", msg_size_);
  }

  // rclcpp::Subscription<std_msgs::msg::UInt8MultiArray>::SharedPtr
  // subscription_;
  rclcpp::SubscriptionBase::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_received_;
  size_t count_;
  size_t msg_size_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriberWithTopicStatistics>());
  rclcpp::shutdown();
  return 0;
}
