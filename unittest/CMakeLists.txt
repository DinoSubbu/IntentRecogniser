cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "*.cpp")

add_executable(Unittest ${Sources})
target_link_libraries(Unittest PUBLIC
    gtest_main
    Intent_RecogniserLib
)

add_test(
    NAME Unittest
    COMMAND Unittest
)