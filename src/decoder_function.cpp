#include "data_communication/decoder.hpp"

Decoder::Decoder() : as2::Node("read_and_publish"){};

Decoder::~Decoder(){};

void Decoder::setupDecoder() {
  publisher_decoder_ = this->create_publisher<std_msgs::msg::String>(publisher_channel_, 10);

  timer_decoder_   = this->create_timer(std::chrono::milliseconds(reading_ms_),
                                        [this]() { this->callback_file(); });
  timer_publisher_ = this->create_timer(std::chrono::milliseconds(publish_ms_),
                                        [this]() { this->callback_publisher(); });
};

void Decoder::callback_publisher() {
  std::ifstream file(file_path_decoder_);

  if (file.is_open()) {
    if (!file_stack_.empty())

    {
      // RCLCPP_INFO(this->get_logger(), "Publicando...");
      std_msgs::msg::String msg;
      msg.data = file_stack_.front();
      publisher_decoder_->publish(msg);
      file_stack_.erase(file_stack_.begin());
    } else {
      // RCLCPP_ERROR(this->get_logger(), "Esperando nuevos datos...");
    }
  }
};

void Decoder::callback_file() {
  std::ifstream infile(file_path_decoder_);

  if (!infile.is_open()) {
    RCLCPP_ERROR(this->get_logger(), "No se pudo abrir el archivo para lectura.");
    return;
  }

  std::string line;

  if (std::getline(infile, line)) {  // Leo la primera linea
    while (!line.empty()) {
      RCLCPP_INFO(this->get_logger(), "He almacenado: %s", line.c_str());
      file_stack_.push_back(line);
      std::getline(infile, line);  // Paso a la siguiente linea
    }
  }

  infile.close();

  // Abre el archivo en modo escritura, lo que eliminará todo el contenido anterior
  std::ofstream outfile(file_path_decoder_, std::ofstream::out | std::ofstream::trunc);
  if (!outfile.is_open()) {
    RCLCPP_ERROR(this->get_logger(), "No se pudo abrir el archivo para escritura.");
    return;
  }

  if (!file_stack_.empty()) {
    RCLCPP_INFO(this->get_logger(), "Eliminando...");
  }

  outfile.close();
};

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

CallbackReturn Decoder::on_configure(const rclcpp_lifecycle::State& _state) {
  // Set subscriptions, publishers, services, actions, etc. here.

  this->declare_parameter("publisher_channel", "decoder_topic");

  if (!this->get_parameter("publisher_channel", publisher_channel_)) {
    RCLCPP_ERROR(this->get_logger(),
                 "No se pudo obtener el parámetro 'publisher_channel' desde el archivo YAML.");
    return CallbackReturn::ERROR;
  }

  this->declare_parameter<std::string>("file_path_decoder",
                                       "/home/pedro/Desktop/pruebas/registro.txt");

  if (!this->get_parameter("file_path_decoder", file_path_decoder_)) {
    RCLCPP_ERROR(this->get_logger(),
                 "No se pudo obtener el parámetro 'file_path_decoder' desde el archivo YAML.");
    return CallbackReturn::ERROR;
  }

  this->declare_parameter("reading_ms", 3000);  // Valor predeterminado de 3000 ms
  this->declare_parameter("publish_ms", 100);   // Valor predeterminado de 100 ms

  if (!this->get_parameter("reading_ms", reading_ms_) ||
      !this->get_parameter("publish_ms", publish_ms_)) {
    RCLCPP_INFO(
        this->get_logger(),
        "No se pudo obtener uno o ambos parámetros, utilizando los valores predeterminados.");
  }

  setupDecoder();

  return CallbackReturn::SUCCESS;
};

CallbackReturn Decoder::on_deactivate(const rclcpp_lifecycle::State& _state) {
  return CallbackReturn::SUCCESS;
};

CallbackReturn Decoder::on_shutdown(const rclcpp_lifecycle::State& _state) {
  // Clean other resources here.
  //  log_file_.close();
  return CallbackReturn::SUCCESS;
};