# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

set(DEBUG_MODE OFF)

# Project name and language
project(MyProject LANGUAGES CXX)

# Set the C++ standard (e.g., C++17 or C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set the main file
if (DEBUG_MODE)
    #set DEBUG flag
    add_definitions(-D__DEBUG__=1)  
else()
    add_definitions(-D__DEBUG__=0)  
    
endif()

# Set the source directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(MAIN_FILE ${CMAKE_SOURCE_DIR}/examples/main.cpp)

# Find all .cpp files in the src directory
file(GLOB SOURCES "${SRC_DIR}/*.cpp")
file(GLOB EXMP_SOURCES "${EXMP_DIR}/*.cpp")
# Include the src directory for headers
include_directories(${SRC_DIR})

# Add an executable target
add_executable(driver_code ${SOURCES} ${EXMP_SOURCES}  ${MAIN_FILE})
