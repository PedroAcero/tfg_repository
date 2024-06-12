#include "data_communication/encoder.hpp"
#include <gtest/gtest.h>
#include <memory>

class EncoderTest : public Encoder, public ::testing::Test {
public:
  using Encoder::Encoder;

  using Encoder::data_register_;
  using Encoder::file_path_encoder_;
  using Encoder::subscriber_channel_;
  using Encoder::subscription_encoder_;

  using Encoder::callback_record;
  using Encoder::writting_file;

  void TestBody() override {
    ASSERT_EQ(file_path_encoder_, "/home/pedro/Desktop/pruebas/registro.txt");
    ASSERT_EQ(subscriber_channel_, "topic");
    EXPECT_EQ(line, "Test_Data");
  }

  std::shared_ptr<rclcpp::Node> node_;
  std::string line;
};

TEST(EncoderTest, TestEncoder) {
  // Test para comprobar que esté bien configurado
  rclcpp::init(0, nullptr);
  EncoderTest encoder;

  rclcpp_lifecycle::State state;
  encoder.on_configure(state);

  // Enviar mensaje por callback_record para ver si se almacena en el archivo
  std_msgs::msg::String msg;
  msg.data = "Test_Data";

  encoder.callback_record(msg);

  std::ifstream file(encoder.file_path_encoder_);
  std::getline(file, encoder.line);

  encoder.TestBody();

  std::ofstream outfile(encoder.file_path_encoder_, std::ofstream::out | std::ofstream::trunc);
  rclcpp::shutdown();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  rclcpp::shutdown();
  return RUN_ALL_TESTS();
}