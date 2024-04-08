cmake_minimum_required(VERSION 3.5)
project(
  rr-neruel
  VERSION 1.0
  LANGUAGES CXX)

file(GLOB SOURCES src/main/*.cpp src/main/*.hpp)

add_executable(rr-neruel ${SOURCES})