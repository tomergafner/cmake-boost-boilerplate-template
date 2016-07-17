cmake_minimum_required( VERSION 2.8 )

project(mfe)

# Enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Werror -Wall")

set(PROJECT_SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(PROJECT_INC_DIR "${CMAKE_SOURCE_DIR}/inc")
message("THE SOURCE DIR IS ${PROJECT_SRC_DIR}")
add_subdirectory(src)
add_subdirectory(examples)

enable_testing ()
add_subdirectory (test)

