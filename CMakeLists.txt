cmake_minimum_required(VERSION 3.20)

project(IntentFinderTool CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "main.cpp")

include_directories(intentRecogniser/include)

add_subdirectory(googletest)
add_subdirectory(unittest)
add_subdirectory(intentRecogniser)

add_executable(IntentFinderTool ${Sources})
target_link_libraries(IntentFinderTool PUBLIC
	IntentRecogniserLib
)