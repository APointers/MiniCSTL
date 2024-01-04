# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(CSTL C)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

# Set CMAKE_INSTALL_PREFIX to the build directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "Install path prefix" FORCE)

# Add all source files in the src directory to the executable
aux_source_directory(src/ dir_src)
aux_source_directory(test/ dir_test)

# Set the output directory for the executable and result binary
set(INSTALL_DIR "${CMAKE_BINARY_DIR}/install/")

# Add the main executable target
add_executable(${PROJECT_NAME} ${dir_src} ${dir_test})

# Include the libuv include directory for headers
target_include_directories(${PROJECT_NAME} PRIVATE src/)

# Install the executable to the build directory
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR})