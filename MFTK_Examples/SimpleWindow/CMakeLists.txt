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

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

target_link_directories(${PROJECT_NAME} PUBLIC vendor/MFTK/lib)

target_link_libraries(${PROJECT_NAME} PUBLIC
    MFTK
    ${SDL2_LIBRARIES}
    SDL2_ttf
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${SDL2_INCLUDES}
    ${SDL2_TTF_INCLUDES}
    vendor/MFTK/include
)


target_include_directories(${PROJECT_NAME} PRIVATE src)


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY vendor/MFTK/resources DESTINATION bin/)
