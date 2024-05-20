cmake_minimum_required(VERSION 3.5)
project(
  rr-neruel
  VERSION 1.0
  LANGUAGES CXX)

set(CPACK_PACKAGE_CONTACT "azzmosphere@gmail.com")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_VERSION 1.0.0)
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Control System For Unmanned Vehicles")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/azzmosphere/rr_neruel")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "wiringpi, wiringpi (>= 3.2)")
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/rrobot")

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
list(APPEND CMAKE_MODULE_PATH ${nlohmann_json})


FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()


# Install Eigen
message(CHECK_START "Fetching Eigen3")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

FetchContent_Declare(
  Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG master
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
# note: To disable eigen tests,
# you should put this code in a add_subdirectory to avoid to change
# BUILD_TESTING for your own project too since variables are directory
# scoped
set(BUILD_TESTING OFF)
set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_MPL2_ONLY ON)
set(EIGEN_BUILD_PKGCONFIG OFF)
set(EIGEN_BUILD_DOC OFF)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/include)
FetchContent_MakeAvailable(Eigen)

list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${json_SOURCE_DIR}/include)
include_directories(${YAML_CPP_SOURCE_DIR}/include)
include_directories( EIGEN3_INCLUDE_DIR )
include_directories( ${INCLUDE_DIR} )

 # Common files, for all programs
file(GLOB SOURCES src/main/common/*.cpp)

# rr-agent code.
add_subdirectory(src/main/rr-agent)
add_subdirectory(src/main/rr-environment)

enable_testing()

add_library(agent_test_code STATIC 
  ${SOURCES}
  src/main/rr-agent/rr_nn.cpp
  src/main/rr-agent/rr_nn.hpp
)


target_link_libraries(agent_test_code PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(agent_test_code PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library
target_link_libraries(agent_test_code PUBLIC Eigen3::Eigen)


add_executable(rr_nn_test src/test/test_rr_nn.cpp)
target_link_libraries(
  rr_nn_test agent_test_code
)

include_directories(${json_SOURCE_DIR}/include)
include_directories(${YAML_CPP_SOURCE_DIR}/include)
include_directories( EIGEN3_INCLUDE_DIR )
include_directories(src/main)

add_test(
  NAME rr_nn_test
  COMMAND $<TARGET_FILE:rr_nn_test>
)

add_executable(test_hbridge src/test/test_hbridge.cpp)
target_link_libraries(test_hbridge PUBLIC /usr/lib/libwiringPi.so)

install(TARGETS rr-environment RUNTIME DESTINATION bin)

include(CPack)