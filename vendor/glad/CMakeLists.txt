cmake_minimum_required(VERSION 3.8)
project(glad C)

include_directories(
    include
)

add_library(${PROJECT_NAME} STATIC src/glad.c)