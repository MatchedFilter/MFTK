cmake_minimum_required(VERSION 3.16)
project(MFTK)

file(GLOB_RECURSE MFTK_HDRS include/*.h)
file(GLOB_RECURSE MFTK_SRC_HDRS src/*.h)
file(GLOB_RECURSE MFTK_SRCS src/*.cpp)


add_library(${PROJECT_NAME} STATIC
                ${MFTK_HDRS}
                ${MFTK_SRC_HDRS}
                ${MFTK_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${SDL2_LIBRARIES}
    ${SDL2_ttf_LIBRARIES}
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${SDL2_INCLUDES}
    ${SDL2_ttf_INCLUDES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

install (TARGETS ${PROJECT_NAME} DESTINATION MFTK/lib)
install (DIRECTORY include DESTINATION MFTK)
install (DIRECTORY resources DESTINATION MFTK)
