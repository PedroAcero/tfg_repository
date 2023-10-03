#include "data_communication/encoder.hpp"

Encoder::Encoder() : as2::Node("Subscribe_and_log") {};

Encoder::~Encoder(){};

void Encoder::setupEncoder(){

  //timer_writting_ = this->create_timer(std::chrono::milliseconds(3500), [this]() { this->callback_writting(); });

  subscription_encoder_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&Encoder::callback_record, this, std::placeholders::_1));
//Modificar topic para que lea del canal que desees

};


void Encoder::callback_record(const std_msgs::msg::String & msg){
  //Callback que almacena en una variable toda la información en una pila
  RCLCPP_INFO(this->get_logger(), "He guardado '%s'", msg.data.c_str());
  data_register_.push_back(msg.data.c_str());

  writting_file(); //Esta función no bloquea la entrada de datos, se pueden seguir almacenando datos en 
                   //data_register_ aunque no se haya terminado de ejecutar una llamada a writting_file()
};


void Encoder::writting_file(){  
 
  std::ofstream file(file_path_, std::ios_base::app);
  
  if (file.is_open()){

    if(data_register_.empty()){
      RCLCPP_INFO(this->get_logger(), "Waiting for data...");
    } else {
      while (!data_register_.empty()) {
        file << data_register_.front() << std::endl;
        data_register_.erase(data_register_.begin()); //No funciona data_register_.pop_front(), que elimina tambien el primer elemento
      }
      RCLCPP_INFO(this->get_logger(), "Datos almacenados con éxito!! \n");
      file.close();
    }

  }
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
  // Clear data_register_?
  return CallbackReturn::SUCCESS;
};