cmake_minimum_required(VERSION 3.8)
project(tessellation LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(vendor)

set(SOURCES
    src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    C_STANDARD      99
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    include
    vendor/glad/include
    vendor/glfw/include
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    glad
    glfw
)