set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)

FIND_PACKAGE(Boost COMPONENTS system filesystem program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${PROJECT_INC_DIR})

add_executable(black_sholes black_sholes.cpp)
target_link_libraries(black_sholes mfe_common_lib ${Boost_LIBRARIES})
