cmake_minimum_required(VERSION 3.16)
project(MFTK)

file(GLOB_RECURSE MFTK_HDRS include/*.h)
file(GLOB_RECURSE MFTK_SRC_HDRS src/*.h)
file(GLOB_RECURSE MFTK_SRCS src/*.cpp)

add_subdirectory(vendor/SDL2)
add_subdirectory(vendor/SDL2_ttf)

add_library(${PROJECT_NAME} STATIC
                ${MFTK_HDRS}
                ${MFTK_SRC_HDRS}
                ${MFTK_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PUBLIC
    SDL2
    SDL2_ttf
)
install (DIRECTORY include/ DESTINATION MFTK/include)
install (TARGETS ${PROJECT_NAME} DESTINATION MFTK/lib)
install (DIRECTORY vendor/SDL2/include DESTINATION vendor/SDL2)
install (TARGETS SDL2 SDL2_ttf DESTINATION vendor/SDL2/lib)