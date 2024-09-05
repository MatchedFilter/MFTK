cmake_minimum_required(VERSION 3.16)

project(SimpleMFTKWindow)

file(GLOB_RECURSE SIMPLEMFTKWINDOW_SRC_HDRS src/*.h)
file(GLOB_RECURSE SIMPLEMFTKWINDOW_SRCS src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --pedantic-errors")


add_executable(${PROJECT_NAME}
                ${SIMPLEMFTKWINDOW_SRC_HDRS}
                ${SIMPLEMFTKWINDOW_SRCS}
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_include_directories(${PROJECT_NAME} PUBLIC
    vendor/SDL2/include
    vendor/MFTK/include
)

target_link_directories(${PROJECT_NAME} PUBLIC vendor/MFTK/lib)
target_link_directories(${PROJECT_NAME} PUBLIC vendor/SDL2/lib)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2-2.0d SDL2_ttf-2.0d MFTK)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY vendor/SDL2/lib/ DESTINATION bin)
