#include "as2_node_template/as2_node_template.hpp"

Encoder::Encoder() : as2::Node("Subscribe_and_log") {};

Encoder::~Encoder(){};

void Encoder::setupEncoder(){

  timer_writting_ = this->create_timer(std::chrono::milliseconds(500), [this]() { this->writting_callback(); });

  subscription_topic_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&Encoder::callback_1s, this, std::placeholders::_1));


};



void Encoder::callback_1s(const std_msgs::msg::String & msg){
    //Callback que almacena en una variable toda la información 
  
  data_vector_.push_back(msg.data.c_str());

};


void Encoder::writting_callback(){
    //Este callback comprueba si tiene el archivo abierto para poder escribir la información almacenada en la pila

  auto current_time_ = std::chrono::steady_clock::now();
  auto time_elapsed_ = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_ - last_callback_time_);

  if(time_elapsed_ >= std::chrono::milliseconds(timeout_encoder_)){

    std::ofstream file(file_path_, std::ios_base::app);
  
    if (file.is_open())
    {
      RCLCPP_INFO(this->get_logger(), "Writting...");

      for (const auto& data : data_vector_) {
          file << data << std::endl;
          RCLCPP_INFO(this->get_logger(), "Datos almacenados con éxito \n");
      }
      file.close();
      data_vector_.clear();
    }
  }

  last_callback_time_ = current_time_;

}


using CallbackReturn =
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

CallbackReturn Encoder::on_configure(
    const rclcpp_lifecycle::State& _state) {
  // Set subscriptions, publishers, services, actions, etc. here.
  setupEncoder();
  return CallbackReturn::SUCCESS;
};

CallbackReturn Encoder::on_deactivate(
    const rclcpp_lifecycle::State& _state) {

  return CallbackReturn::SUCCESS;
};

CallbackReturn Encoder::on_shutdown(
    const rclcpp_lifecycle::State& _state) {
  // Clean other resources here.
  //  log_file_.close();
  return CallbackReturn::SUCCESS;
};