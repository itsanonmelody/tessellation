cmake_minimum_required(VERSION 3.8)
project(tessellation LANGUAGES C)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(vendor)

set(SOURCES
    src/app.c
    src/main.c
    src/memory.c
    src/util.c

    src/core/log.c
    src/graphics/shader.c
)

set(GCC_COMPILE_OPTIONS -Wall)
set(GCC_LINK_OPTIONS    -Wall)

IF(BUILD_CONFIG STREQUAL "Debug")
    list(APPEND GCC_COMPILE_OPTIONS -g -DTSL_DEBUG)
    list(APPEND GCC_LINK_OPTIONS -g)
    list(APPEND SOURCES
        src/core/assert.c
    )
ENDIF()

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    C_STANDARD      99
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    include
    vendor/cglm/include
    vendor/glad/include
    vendor/glfw/include
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    cglm
    glad
    glfw
)
target_compile_options(
    ${PROJECT_NAME} PUBLIC
    ${GCC_COMPILE_OPTIONS}
)
target_link_options(
    ${PROJECT_NAME} PUBLIC
    ${GCC_LINK_OPTIONS}
)