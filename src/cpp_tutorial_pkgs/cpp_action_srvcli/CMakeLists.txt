cmake_minimum_required(VERSION 3.8)
project(cpp_action_srvcli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(action_tutorials_interfaces REQUIRED)

add_executable(fibonacci_action_server
  src/fibonacci_action_server.cpp
)

add_executable(fibonacci_action_client
  src/fibonacci_action_client.cpp
)

ament_target_dependencies(fibonacci_action_server
  rclcpp
  rclcpp_action
  action_tutorials_interfaces
)

ament_target_dependencies(fibonacci_action_client
  rclcpp
  rclcpp_action
  action_tutorials_interfaces
)

install(TARGETS
  fibonacci_action_server
  fibonacci_action_client
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
