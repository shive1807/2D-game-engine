cmake_minimum_required(VERSION 3.20)

project(Nova2D
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find GLFW
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Create the engine executable
add_executable(Nova2D
    main.cpp
    src/Engine/Application.cpp
    src/Engine/Input.cpp
    src/Engine/Renderer.cpp

)

target_include_directories(Nova2D PRIVATE
    src
    src/Engine
)

# Link GLFW
target_link_libraries(Nova2D PRIVATE 
    glfw
    OpenGL::GL
)

# Enable useful compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(Nova2D PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()