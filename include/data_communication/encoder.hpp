#ifndef AS2_NODE_TEMPLATE_HPP_
#define AS2_NODE_TEMPLATE_HPP_

#include <rclcpp/rclcpp.hpp>
#include "as2_core/names/actions.hpp"
#include "as2_core/names/services.hpp"
#include "as2_core/names/topics.hpp"
#include "as2_core/node.hpp"

#include <chrono>
#include <fstream>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class Encoder : public as2::Node {
public:
  Encoder();
  ~Encoder();

  void setupEncoder();

  using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

  CallbackReturn on_configure(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_shutdown(const rclcpp_lifecycle::State&) override;

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_encoder_;

  void callback_record(const std_msgs::msg::String& msg);
  void writting_file();

  std::string subscriber_channel_;
  std::vector<std::string> data_register_;
  std::string file_path_encoder_;
};

#endif  // AS2_NODE_TEMPLATE_HPP_