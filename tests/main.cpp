#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// colcon test --packages-select tfg_repository --event-handler=console_direct+
// Librería gmock
// Por qué no funcionan los TEST_F?