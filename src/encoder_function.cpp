#include "data_communication/encoder.hpp"

Encoder::Encoder() : as2::Node("Subscribe_and_log"){};

Encoder::~Encoder(){};

void Encoder::setupEncoder() {
  subscription_encoder_ = this->create_subscription<std_msgs::msg::String>(
      subscriber_channel_, 10, std::bind(&Encoder::callback_record, this, std::placeholders::_1));
};

void Encoder::callback_record(const std_msgs::msg::String& msg) {
  // Callback que almacena en una variable toda la información en una pila
  RCLCPP_INFO(this->get_logger(), "He guardado '%s'", msg.data.c_str());
  data_register_.push_back(msg.data.c_str());

  // Esta función no bloquea la entrada de datos, se pueden seguir almacenando datos en
  // data_register_ aunque no se haya terminado de ejecutar una llamada a writting_file()

  writting_file();
};

void Encoder::writting_file() {
  std::ofstream file(file_path_encoder_, std::ios_base::app);

  if (file.is_open())

  {
    if (data_register_.empty()) {
      RCLCPP_INFO(this->get_logger(), "Waiting for data...");
    } else {
      while (!data_register_.empty()) {
        file << data_register_.front() << std::endl;
        data_register_.erase(data_register_.begin());
      }
      RCLCPP_INFO(this->get_logger(), "Datos almacenados con éxito!! \n");
      file.close();
    }
  }
}

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

CallbackReturn Encoder::on_configure(const rclcpp_lifecycle::State& _state) {
  // Set subscriptions, publishers, services, actions, etc. here.

  this->declare_parameter("subscriber_channel", "topic");

  if (!this->get_parameter("subscriber_channel", subscriber_channel_)) {
    RCLCPP_ERROR(this->get_logger(),
                 "No se pudo obtener el parámetro 'subscriber_channel' desde el archivo YAML.");
    return CallbackReturn::ERROR;
  }

  this->declare_parameter<std::string>("file_path_encoder",
                                       "/home/pedro/Desktop/pruebas/registro.txt");

  if (!this->get_parameter("file_path_encoder", file_path_encoder_)) {
    RCLCPP_ERROR(this->get_logger(),
                 "No se pudo obtener el parámetro 'file_path_encoder' desde el archivo YAML.");
    return CallbackReturn::ERROR;
  }

  setupEncoder();

  return CallbackReturn::SUCCESS;
};

CallbackReturn Encoder::on_deactivate(const rclcpp_lifecycle::State& _state) {
  return CallbackReturn::SUCCESS;
};

CallbackReturn Encoder::on_shutdown(const rclcpp_lifecycle::State& _state) {
  // Clean other resources here.
  // Clear data_register_?
  return CallbackReturn::SUCCESS;
};