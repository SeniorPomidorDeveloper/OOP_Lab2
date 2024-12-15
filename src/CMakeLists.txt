add_executable(run main.cpp)
add_library(prog "program.cpp")
add_subdirectory(libs)
target_link_libraries(run prog dice)