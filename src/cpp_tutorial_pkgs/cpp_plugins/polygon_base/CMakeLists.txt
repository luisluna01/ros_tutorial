cmake_minimum_required(VERSION 3.8)
project(polygon_base)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)

# Create INTERFACE library
# - Used for gathering requirements (e.g. link dependencies or include paths) for anything linking
#   against it
# - Target has no compiled binary
add_library(${PROJECT_NAME} INTERFACE)

# Create alias polygon_base::polygon_base for 'polygon_base' library
# - [Namespace]::[Name] is CMake convention for imported library targets
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Ensures anything linking against 'polygon_base' is compiled with at least C99 and C++17
# - INTERFACE here means to consumers, not this project (Since it has no compilation of its own)
target_compile_features(${PROJECT_NAME} INTERFACE c_std_99 cxx_std_17)

# Specifies which header directories are needed to compile 'polygon_base'
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # During build time
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}> # During installation
)

# Anything linking against 'polygon_base' get pluginlib and usage requirements
target_link_libraries(${PROJECT_NAME} INTERFACE ${pluginlib_TARGETS})

install(DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Installs CMake config file and installs it to share/ directory for downstream packages to
# recreate target
install(EXPORT export_${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION share/${PROJECT_NAME}/cmake
)

add_executable(area_node src/area_node.cpp)

target_include_directories(area_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(area_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(area_node
  "pluginlib"
)

install(TARGETS area_node
  DESTINATION lib/${PROJECT_NAME})

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

# Export include directory that downstream packages should add to their compiler include path
ament_export_include_directories(
  include
)

# Export target to downstream packages
ament_export_targets(
  export_${PROJECT_NAME}
)

ament_package()
