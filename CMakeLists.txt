cmake_minimum_required(VERSION 3.20)

project(Intent_Recogniser CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# Add dependencies
add_subdirectory(googletest)

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS "include/*.hpp")
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "src/*.cpp")

include_directories(include)

add_executable(Intent_Recogniser ${Headers} ${Sources})
add_library(Intent_RecogniserLib STATIC ${Headers} ${Sources})
add_subdirectory(unittest)
