cmake_minimum_required(VERSION 3.23)
project(Vector_lib)

#------------------------------------
#   settings
#------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(MYCOMPILE_FLAGS "-g")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
# set(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

add_subdirectory(src)
add_subdirectory(tests)