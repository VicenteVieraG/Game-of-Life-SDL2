add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${GAME})
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2::SDL2)


target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE ./
    PRIVATE ${CMAKE_BINARY_DIR}/configured_files/include
)