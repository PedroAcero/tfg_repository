#include "data_communication/decoder.hpp"

Decoder::Decoder() : as2::Node("read_and_publish") {};

Decoder::~Decoder(){};

void Decoder::setupDecoder(){

    publisher_decoder_ = this->create_publisher<std_msgs::msg::String>("decoder_topic", 10);

    timer_decoder_= this->create_timer(std::chrono::milliseconds(3000), [this]() { this->callback_file(); });
    timer_publisher_ = this->create_timer(std::chrono::milliseconds(100), [this]() { this->callback_publisher(); });

};


void Decoder::callback_publisher() {

    std::ifstream file(file_path_decoder_);

    if(file.is_open()){
        if (!file_stack_.empty()) {
            std_msgs::msg::String msg;
            msg.data = file_stack_.front();
            publisher_decoder_->publish(msg);
            file_stack_.erase(file_stack_.begin());
        } else {
            //RCLCPP_ERROR(this->get_logger(), "Esperando nuevos datos...");
        }
    }

};



void Decoder::callback_file(){

    std::ifstream infile(file_path_decoder_);

    if (!infile.is_open()) {
        RCLCPP_ERROR(this->get_logger(), "No se pudo abrir el archivo para lectura.");
        return;
    }

    std::string line;

    if (std::getline(infile, line)) {   //Leo la primera linea
            while (!line.empty()) {
                RCLCPP_INFO(this->get_logger(), "He almacenado: %s", line.c_str());
                file_stack_.push_back(line);
                std::getline(infile, line); //Paso a la siguiente linea
            }
    }

    infile.close();

    // Abre el archivo en modo escritura, lo que eliminará todo el contenido anterior
    std::ofstream outfile(file_path_decoder_, std::ofstream::out | std::ofstream::trunc);
    if (!outfile.is_open()) {
        RCLCPP_ERROR(this->get_logger(), "No se pudo abrir el archivo para escritura.");
        return;
    }

    if (!file_stack_.empty()){
        RCLCPP_INFO(this->get_logger(), "Eliminando...");
    }

    outfile.close();

};


using CallbackReturn =
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

CallbackReturn Decoder::on_configure(
    const rclcpp_lifecycle::State& _state) {
  // Set subscriptions, publishers, services, actions, etc. here.
  setupDecoder();
  return CallbackReturn::SUCCESS;
};

CallbackReturn Decoder::on_deactivate(
    const rclcpp_lifecycle::State& _state) {

  return CallbackReturn::SUCCESS;
};

CallbackReturn Decoder::on_shutdown(
    const rclcpp_lifecycle::State& _state) {
  // Clean other resources here.
  //  log_file_.close();
  return CallbackReturn::SUCCESS;
};