find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${PROJECT_INC_DIR}
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (test_mfe_common test_mfe_common.cpp)
target_link_libraries (test_mfe_common
                       mfe_common_lib # The library created out of the source directory except main.cpp
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME test_mfe_common COMMAND test_mfe_common)
