cmake_minimum_required(VERSION 3.5)
project(
  rr-neruel
  VERSION 1.0
  LANGUAGES CXX)

# Cross compile flags for Raspberry Pi.  
# CMAKE_CXX_FLAGS       -arch armv6

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

file(GLOB SOURCES src/main/*.cpp src/main/*.hpp)

add_executable(rr-neruel ${SOURCES})
target_link_libraries(rr-neruel PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(rr-neruel PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library

include_directories(${json_SOURCE_DIR}/include)
include_directories(${YAML_CPP_SOURCE_DIR}/include)

#
# Something is breaking in the test class,  and really don't like the way this works anyway,  it is using ctest straight,  really want to use something like
# catch2,  but was failing on OSX with ARM64 for some reason :(.
# testing build
# add_library(nn STATIC 
#   src/main/ConfigReader.cpp
#   src/main/ConfigReader.hpp     
#   src/main/FileReader.hpp
#   src/main/Layer.hpp 
#   src/main/Logger.hpp
#   src/main/nn.cpp
#   src/main/nn.hpp
#   src/main/TrainingSet.hpp
#   src/main/TrainingSet.cpp
# )

# add_executable(nn_test_code src/test/test_nn.cpp)
# include_directories(nn_test_code src/main)

# target_link_libraries(nn PRIVATE 
#   nlohmann_json::nlohmann_json
#   PUBLIC yaml-cpp::yaml-cpp
# )
# target_link_libraries(
#   nn_test_code nn
# )

# enable_testing()

# add_test(
#   NAME nn_test_code
#   COMMAND $<TARGET_FILE:nn_test_code>
# )