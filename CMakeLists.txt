cmake_minimum_required(VERSION 3.16)
project(MFTKTest)

file(GLOB_RECURSE MFTKTEST_SRC_HDRS src/*.h)
file(GLOB_RECURSE MFTKTEST_SRCS src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --pedantic-errors")

add_subdirectory(MFTK)

add_executable(${PROJECT_NAME}
                ${MFTKTEST_SRC_HDRS}
                ${MFTKTEST_SRCS}
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PUBLIC MFTK)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
