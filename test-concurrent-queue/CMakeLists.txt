cmake_minimum_required(VERSION 3.15)

project(testQueue)

add_compile_options(-g -Wfatal-errors)

# add_compile_definitions(USE_SPINLOCK)
# add_compile_definitions(USE_SLEEP)
add_compile_definitions(REPEAT_NUMBER=100)

add_executable(test test.cpp)
target_link_libraries(test pthread)
