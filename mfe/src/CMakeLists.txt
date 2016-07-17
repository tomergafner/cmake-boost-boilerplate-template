set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)

message("The directory to include ${PROJECT_INC_DIR}")
include_directories(${PROJECT_INC_DIR})

add_library (mfe_common_lib mfe_common.cpp)
