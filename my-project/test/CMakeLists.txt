find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${PROJECT_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test1 my_test.cpp)
target_link_libraries (Test1
                       my_project_lib # The library created out of the source directory except main.cpp
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME MyTest COMMAND Test1)
