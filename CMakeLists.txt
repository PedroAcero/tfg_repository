cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME tfg_repository)
project(${PROJECT_NAME})

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# set Release as default
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# find dependencies
set(PROJECT_DEPENDENCIES
  ament_cmake
  rclcpp
  as2_core
  as2_msgs
  std_srvs
  std_msgs
)

foreach(DEPENDENCY ${PROJECT_DEPENDENCIES})
  find_package(${DEPENDENCY} REQUIRED)
endforeach()

include_directories(
  include
  include/${PROJECT_NAME}
  #uncomment if using Eigen3
  #{EIGEN3_INCLUDE_DIRS} 
)

set(SOURCE_CPP_FILES 
  src/as2_node_template.cpp
  src/encoder_function.cpp
  src/decoder_function.cpp
)

add_executable(${PROJECT_NAME}_pubsub_node src/as2_node_template_node.cpp ${SOURCE_CPP_FILES})
ament_target_dependencies(${PROJECT_NAME}_pubsub_node ${PROJECT_DEPENDENCIES})

add_executable(${PROJECT_NAME}_encoder_node src/encoder_function_node.cpp ${SOURCE_CPP_FILES})
ament_target_dependencies(${PROJECT_NAME}_encoder_node ${PROJECT_DEPENDENCIES})

add_executable(${PROJECT_NAME}_decoder_node src/decoder_function_node.cpp ${SOURCE_CPP_FILES})
ament_target_dependencies(${PROJECT_NAME}_decoder_node ${PROJECT_DEPENDENCIES})


if(BUILD_TESTING)
  find_package(ament_cmake_cppcheck REQUIRED)
  find_package(ament_cmake_clang_format REQUIRED)
  
  ament_cppcheck(src/ include/ tests/)
  ament_clang_format(src/ include/ tests/ --config ${CMAKE_CURRENT_SOURCE_DIR}/.clang-format)
endif()

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})

install(TARGETS
  ${PROJECT_NAME}_pubsub_node
  ${PROJECT_NAME}_encoder_node
  ${PROJECT_NAME}_decoder_node
  DESTINATION lib/${PROJECT_NAME})
    
ament_package()
