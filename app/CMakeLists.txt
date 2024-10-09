add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${GAME})

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE ./
    PRIVATE ${CMAKE_BINARY_DIR}/configured_files/include
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SDL2_PATH}
    $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    COMMENT "SDL2.dll copied to build/bin"
)