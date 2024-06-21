add_library(${GRID} STATIC Grid.cpp)

target_link_libraries(${GRID} PUBLIC ${CELL})