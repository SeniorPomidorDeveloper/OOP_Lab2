if(BUILD_TEST)
    enable_testing()
    include(CTest)
    add_executable(tests main.cpp)
    target_link_libraries(tests dice gtest)

    include(GoogleTest)
    gtest_discover_tests(tests)
    add_custom_command(TARGET tests
                       POST_BUILD
                       COMMAND make -f ../../tests/makefile -s
                       COMMENT "Start GenCov"
                       USES_TERMINAL)
endif()