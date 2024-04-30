cmake_minimum_required(VERSION 3.5)
project(
  rr-environment
  VERSION 1.0
  LANGUAGES CXX)

set(BUILD_TESTING OFF)
set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_MPL2_ONLY ON)
set(EIGEN_BUILD_PKGCONFIG OFF)
set(EIGEN_BUILD_DOC OFF)
FetchContent_MakeAvailable(Eigen)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${json_SOURCE_DIR}/include)
include_directories(${YAML_CPP_SOURCE_DIR}/include)
include_directories( EIGEN3_INCLUDE_DIR )
include_directories(${INCLUDE_DIR})

file(GLOB RR_AGENT_SOURCES *.cpp )
add_executable(rr-environment ${SOURCES} ${RR_AGENT_SOURCES})
target_link_libraries(rr-environment PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(rr-environment PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library
target_link_libraries(rr-environment PUBLIC Eigen3::Eigen)