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

    void callback_file();
    void callback_publisher();

    std::vector<std::string> file_stack_; //Vector lo más adecuado para luego procesar datos, mejor que queue?
    std::string file_path_decoder_ = "/home/pedro/Desktop/pruebas/registro.txt";
    //std::chrono::steady_clock::time_point last__decoder_time_;
    //int timeout_decoder_ = 5000;

};





#endif  // AS2_NODE_TEMPLATE_HPP_