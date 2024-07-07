cmake_minimum_required(VERSION 3.10)
    
# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(main C)
# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# List all source files
set(SOURCE_FILES src/set1.c src/test.c)

# Add executable
add_executable(test ${SOURCE_FILES})

# Add include directories for target
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/include)
