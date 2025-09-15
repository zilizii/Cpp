cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB SOURCES src/*.cpp)

add_executable(prog ${SOURCES})

# Optionally, link libraries
# target_link_libraries(MyExecutable PRIVATE <library_name>)
