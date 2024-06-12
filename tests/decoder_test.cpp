#include "data_communication/decoder.hpp"
#include <gtest/gtest.h>
#include <memory>
// gmock

class DecoderTest : public Decoder, public ::testing::Test {
public:
  using Decoder::Decoder;

  using Decoder::callback_file;
  using Decoder::callback_publisher;

  using Decoder::file_path_decoder_;
  using Decoder::file_stack_;
  using Decoder::publish_ms_;
  using Decoder::publisher_channel_;
  using Decoder::reading_ms_;

  void TestBody() override {
    ASSERT_EQ(file_path_decoder_, "/home/pedro/Desktop/pruebas/registro.txt");
    ASSERT_EQ(publisher_channel_, "decoder_topic");
    EXPECT_EQ(file_stack_.size(), 1);
    EXPECT_EQ(file_stack_[0], "Test_Data_To_Decode");
  }

  std::shared_ptr<rclcpp::Node> node_;
};

TEST(DecoderTest, TestDecoder) {
  rclcpp::init(0, nullptr);
  DecoderTest decoder;

  rclcpp_lifecycle::State state;
  decoder.on_configure(state);

  std::ofstream file(decoder.file_path_decoder_);
  file << "Test_Data_To_Decode" << std::endl;

  decoder.callback_file();
  // decoder.callback_publisher();

  decoder.TestBody();

  rclcpp::shutdown();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}