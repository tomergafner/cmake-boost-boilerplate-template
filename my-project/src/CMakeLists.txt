set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
add_library (my_project_lib api.cpp api.h)
add_executable(myapp main.cpp)
target_link_libraries(myapp my_project_lib)
