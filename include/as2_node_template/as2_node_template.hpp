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
#include <fstream>

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

class Encoder : public as2::Node {
 public:
  Encoder();
  ~Encoder();

  void setupEncoder();


  using CallbackReturn =
      rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

  CallbackReturn on_configure(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_shutdown(const rclcpp_lifecycle::State&) override;

  private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_encoder_;
    
    rclcpp::TimerBase::SharedPtr timer_writting_;
    void callback_record_(const std_msgs::msg::String & msg);
    void callback_writting();

    std::vector<std::string> data_register_;
    std::string file_path_ = "/home/pedro/Desktop/pruebas/registro.txt";
    std::chrono::steady_clock::time_point last_encoder_time_;
    int timeout_encoder_ = 5000; //ms
};

class Decoder : public as2::Node {
 public:
  Decoder();
  ~Decoder();

  void setupDecoder();


  using CallbackReturn =
      rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

  CallbackReturn on_configure(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State&) override;
  CallbackReturn on_shutdown(const rclcpp_lifecycle::State&) override;

 private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_decoder_;
    rclcpp::TimerBase::SharedPtr timer_decoder_;
    rclcpp::TimerBase::SharedPtr timer_publisher_;

    void callback_publisher();
    void callback_reading();

    std::vector<std::string> file_stack_; //Cambiar vector por quizas un vector o un deque
    std::string file_path_decoder_ = "/home/pedro/Desktop/pruebas/registro.txt";
    std::chrono::steady_clock::time_point last__decoder_time_;
    int timeout_decoder_ = 5000;

};
 

#endif  // AS2_NODE_TEMPLATE_HPP_
