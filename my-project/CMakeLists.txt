cmake_minimum_required( VERSION 2.8 )

project(my_project)

set(PROJECT_SOURCE_DIR, src)
add_subdirectory(src)

enable_testing ()
add_subdirectory (test)

