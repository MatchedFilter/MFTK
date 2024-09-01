cmake_minimum_required(VERSION 3.16)
project(MFTK)

file(GLOB_RECURSE MFTK_HDRS include/*.h)
file(GLOB_RECURSE MFTK_SRC_HDRS src/*.h)
file(GLOB_RECURSE MFTK_SRCS src/*.cpp)


add_library(${PROJECT_NAME}
                ${MFTK_HDRS}
                ${MFTK_SRC_HDRS}
                ${MFTK_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2-static SDL2main)