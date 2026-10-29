
cmake_minimum_required(VERSION 3.20)

project(Nova2D
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# GLAD OpenGL function loader
add_library(glad STATIC
    external/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

# Nova2D engine executable
add_executable(Nova2D
    main.cpp
    src/Engine/Application.cpp
    src/Engine/Input.cpp
    src/Engine/Renderer.cpp
    src/Engine/Shader.cpp
)

target_include_directories(Nova2D PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine
)

# Link dependencies
target_link_libraries(Nova2D PRIVATE
    glfw
    OpenGL::GL
    glad
)

# Compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(Nova2D PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
