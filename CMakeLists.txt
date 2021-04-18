cmake_minimum_required(VERSION 3.20)

# Project name
project(Intent_Recogniser CXX)

set(CMAKE_CXX_STANDARD 17)

#enable_testing()

# Add dependencies
#add_subdirectory(googletest)

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS "include/*.hpp")
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "src/*.cpp")
set(EXECUTABLE_OUTPUT_PATH "build/")

add_executable(Intent_Recogniser ${Headers} ${Sources})

#add_subdirectory(unittest)
