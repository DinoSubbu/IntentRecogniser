cmake_minimum_required(VERSION 3.20)

project(IntentRecogniserLib CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS "include/*.hpp")
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "src/*.cpp")

include_directories(include)
add_library(IntentRecogniserLib STATIC ${Headers} ${Sources})

