# CMake version setting
cmake_minimum_required(VERSION 3.13)

## default is dynamic link
## you can make it, when you make build directories option, is below,
## -DBUILD_SHARED_LIBS=ON

# project name and language setting
project(test_cmake CXX)

# making static library
#add_library(staticlib test.cpp)

# making dynamic library
#add_library(dynamiclib SHARED test.cpp)

# build exe setting
add_executable(main main.cpp)

# link setting
#target_link_libraries(test.o dynamiclib)
