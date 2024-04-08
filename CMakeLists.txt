cmake_minimum_required(VERSION 3.5)
project(
  rr-neruel
  VERSION 1.0
  LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
list(APPEND CMAKE_MODULE_PATH ${nlohmann_json})

file(GLOB SOURCES src/main/*.cpp src/main/*.hpp)

add_executable(rr-neruel ${SOURCES})
target_link_libraries(rr-neruel PRIVATE nlohmann_json::nlohmann_json)
include_directories(${json_SOURCE_DIR}/include)