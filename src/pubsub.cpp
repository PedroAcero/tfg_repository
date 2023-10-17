#include "data_communication/pubsub.hpp"

PubSub::PubSub() : as2::Node("publish_and_subscribe"){};

PubSub::~PubSub(){};

void PubSub::setupNode() {
  count_ = 0;

  timer_ = this->create_timer(std::chrono::milliseconds(100), [this]() { this->timer_callback(); });

  publisher_    = this->create_publisher<std_msgs::msg::String>("topic", 10);
  subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&PubSub::topic_callback, this, std::placeholders::_1));
};

void PubSub::timer_callback() {
  auto message = std_msgs::msg::String();
  message.data = "Hello, world! " + std::to_string(count_++);
  RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
  publisher_->publish(message);
};

void PubSub::topic_callback(const std_msgs::msg::String& msg) {
  RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
};

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

CallbackReturn PubSub::on_configure(const rclcpp_lifecycle::State& _state) {
  // Set subscriptions, publishers, services, actions, etc. here.
  setupNode();
  return CallbackReturn::SUCCESS;
};

CallbackReturn PubSub::on_deactivate(const rclcpp_lifecycle::State& _state) {
  // Clean up subscriptions, publishers, services, actions, etc. here.

  //~PubSub();

  return CallbackReturn::SUCCESS;
};

CallbackReturn PubSub::on_shutdown(const rclcpp_lifecycle::State& _state) {
  // Clean other resources here.
  count_ = 0;
  return CallbackReturn::SUCCESS;
};
