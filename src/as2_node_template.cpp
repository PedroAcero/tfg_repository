#include "as2_node_template.hpp"

As2NodeTemplate::As2NodeTemplate() : as2::Node("as2_node_template") {}

using CallbackReturn =
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

CallbackReturn As2NodeTemplate::on_configure(
    const rclcpp_lifecycle::State& _state) {
  // Set subscriptions, publishers, services, actions, etc. here.

  return CallbackReturn::SUCCESS;
};

CallbackReturn As2NodeTemplate::on_deactivate(
    const rclcpp_lifecycle::State& _state) {
  // Clean up subscriptions, publishers, services, actions, etc. here.
  return CallbackReturn::SUCCESS;
};

CallbackReturn As2NodeTemplate::on_shutdown(
    const rclcpp_lifecycle::State& _state) {
  // Clean other resources here.

  return CallbackReturn::SUCCESS;
};
