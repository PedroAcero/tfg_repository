#ifndef AS2_NODE_TEMPLATE_HPP_
#define AS2_NODE_TEMPLATE_HPP_

#include <rclcpp/rclcpp.hpp>
#include "as2_core/names/actions.hpp"
#include "as2_core/names/services.hpp"
#include "as2_core/names/topics.hpp"
#include "as2_core/node.hpp"

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class PubSub : public as2::Node {
 public:
  PubSub();
  ~PubSub();

  void setupNode();

  int count_;

  using CallbackReturn =
      rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

  CallbackReturn on_configure(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_shutdown(const rclcpp_lifecycle::State&) override;

  private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    
    rclcpp::TimerBase::SharedPtr timer_;
    void timer_callback();
    void topic_callback(const std_msgs::msg::String & msg);
};
 

#endif  // AS2_NODE_TEMPLATE_HPP_
