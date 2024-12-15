add_subdirectory(dice)
add_subdirectory(asciiArt)
add_subdirectory("string")

target_link_libraries(dice asciiArt mystring)