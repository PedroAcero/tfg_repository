#include "as2_node_template/as2_node_template.hpp"

Decoder::Decoder() : as2::Node("read_and_publish") {};

//Decoder::Decoder() : as2::Node("read_and_publish"), file_path_decoder_("/home/pedro/Desktop/pruebas/registro.txt") {};

Decoder::~Decoder(){};

void Decoder::setupDecoder(){

    publisher_decoder_ = this->create_publisher<std_msgs::msg::String>("decoder_topic", 10);

    timer_decoder_= this->create_timer(std::chrono::seconds(1), [this]() { this->callback_reading(); });
    timer_publisher_ = this->create_timer(std::chrono::milliseconds(1500), [this]() { this->callback_publisher(); });

};


void Decoder::callback_publisher() {
    
    RCLCPP_INFO(this->get_logger(), "A mi me llega: %s \n", file_stack_.front().c_str());
    RCLCPP_INFO(this->get_logger(), "Me llega con un tamaño: %d, \n", static_cast<int>(file_stack_.size()));
    file_stack_.erase(file_stack_.begin());

    if (static_cast<int>(file_stack_.size()) > 1) {

        std_msgs::msg::String msg;
        msg.data = file_stack_.front();

        publisher_decoder_->publish(msg);
        file_stack_.erase(file_stack_.begin());
    }

}


void Decoder::callback_reading(){

    auto current_time_ = std::chrono::steady_clock::now();
    auto time_elapsed_ = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_ - last__decoder_time_);

    if(time_elapsed_ >= std::chrono::milliseconds(timeout_decoder_)){

        std::ifstream file(file_path_decoder_);

        if (file.is_open()) {
            std::string line;

            while (std::getline(file, line)) {

                file_stack_.push_back(line); // Almacena cada línea en el vector

                RCLCPP_INFO(this->get_logger(), "Saving data: %s, \n", line.c_str());
                RCLCPP_INFO(this->get_logger(), "Tamaño del vector: %d, \n", static_cast<int>(file_stack_.size()));
                   
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            file.close();

            // Reabre el archivo en modo de escritura y sobrescribe las líneas que queremos conservar.
            std::ofstream outfile(file_path_decoder_);

            outfile << line << std::endl;

            outfile.close();

        } else {
            
            RCLCPP_ERROR(this->get_logger(), "No se pudo abrir el archivo.");
        
        }       
    }

    last__decoder_time_ = current_time_;

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