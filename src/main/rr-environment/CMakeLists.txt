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

# Adding wiring pi configuraton
FetchContent_Declare(
  wiring-pi
  GIT_REPOSITORY https://github.com/WiringPi/WiringPi.git
  GIT_TAG master # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_GetProperties(wiring-pi)
# find_library(wiringPi_LIB wiringPi)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${json_SOURCE_DIR}/include)
include_directories(${YAML_CPP_SOURCE_DIR}/include)
include_directories( EIGEN3_INCLUDE_DIR )
include_directories(${INCLUDE_DIR})

file(
    GLOB RR_ENV_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/components/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/*.hpp
)
add_executable(rr-environment ${SOURCES} ${RR_ENV_SOURCES})
target_link_libraries(rr-environment PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(rr-environment PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library
target_link_libraries(rr-environment PUBLIC Eigen3::Eigen)
target_link_libraries(rr-environment PUBLIC /usr/lib/libwiringPi.so)





# if(NOT wiring-pi_POPULATED)
#   message(STATUS "Fetching  wiring-pi...")
#   FetchContent_Populate( wiring-pi)
#   add_subdirectory(${wiring-pi_SOURCE_DIR} ${wiring-pi_BINARY_DIR})
# endif()