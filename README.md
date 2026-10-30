# Nova2D

Nova2D is a small 2D game engine written from scratch in C++20 on top of OpenGL 3.3. It is meant to be the base for future games. For now it opens a window, runs a fixed game loop, and draws a transformed rectangle through an orthographic camera, using a hand-written matrix math library.

> **Status:** early development (v0.1.0). The engine renders a single hard-coded rectangle. There is no public API for games yet.

## Features

- **Application and game loop**: creates a GLFW window (1280×720, OpenGL 3.3 Core, vsync on). Each frame it polls events, updates input, ticks the timer, then calls `Update(deltaTime)` and `Render()`.
- **Timing** (`EngineTime`): frame delta and total elapsed time from `std::chrono::steady_clock`. Elapsed time, delta and FPS are printed to the console once per second.
- **Input** (`Input`): per-frame keyboard state, with `IsKeyPressed`, `IsKeyJustPressed` and `IskeyJustReleased`.
- **Math** (`Matrix4`): a column-major 4×4 matrix with multiplication, `Translation`, `RotationZ` (in degrees), `Scale` and `Orthographic` projection. Its memory layout matches what OpenGL expects, so it can be uploaded directly.
- **Transform**: position, rotation and scale, combined into a model matrix (`T * R * S`).
- **Camera**: a 2D orthographic camera measured in world units (16 × 9 by default) that gives a view matrix and a projection matrix.
- **Rendering**: `Shader` compiles and links GLSL programs and reports errors. `Rectangle` owns a VAO/VBO and draws itself with an MVP matrix (`projection * view * model`). `Renderer::Clear` clears the screen.

## Project structure

```
.
├── CMakeLists.txt          # Build targets: glad, Nova2D, Matrix4Test
├── main.cpp                # Entry point: creates and runs Nova::Application
├── src/Engine/
│   ├── Application.*       # Window, OpenGL context, main loop, lifetime
│   ├── EngineTime.h        # Delta and elapsed time
│   ├── Input.*             # Keyboard state polling
│   ├── Matrix4.*           # 4x4 matrix math
│   ├── Transform.*         # Position / rotation / scale -> model matrix
│   ├── Camera.*            # Orthographic 2D camera
│   ├── Shader.*            # GLSL compile / link wrapper
│   ├── Rectangle.*         # Renderable quad with its own shader and transform
│   └── Renderer.*          # Render commands (Clear)
├── external/glad/          # OpenGL 3.3 function loader (vendored)
└── tests/
    └── Matrix4Test.cpp     # Math tests (projection, model, view, MVP)
```

All engine code is in the `Nova` namespace.

## Requirements

- A C++20 compiler (Clang or GCC)
- CMake 3.20 or newer
- [GLFW](https://www.glfw.org/) 3.3 or newer
- OpenGL 3.3 support (GLAD is included in the repo)

On macOS with Homebrew:

```sh
brew install cmake glfw
```

On Debian/Ubuntu:

```sh
sudo apt install cmake libglfw3-dev libgl1-mesa-dev
```

## Building and running

```sh
cmake -S . -B build
cmake --build build

./build/Nova2D        # run the engine
./build/Matrix4Test   # run the math tests
```

When it starts, the engine opens a window titled **"Nova2D - Application"**. It draws a light-blue rectangle rotated 45°, on a dark background, seen through a camera offset to `(0.5, 0)`. Close the window to quit.

## Tests

`Matrix4Test` is a small self-contained test runner with no framework. It checks:

- Orthographic projection matrix
- Model matrix (translation × rotation × scale)
- Camera view matrix
- Camera projection matrix
- Full MVP matrix

It prints `[PASS]`/`[FAIL]` for each test, plus any mismatched matrix entries. It exits with a non-zero status if any test fails.

## Coordinate system

- World units are arbitrary. By default the camera shows a 16 × 9 area centered on its position, so `(0, 0)` is the center of the screen when the camera is at the origin.
- +X is right, +Y is up, and positive rotation is counter-clockwise.
- Vertices go through `gl_Position = u_MVP * vec4(position, 0, 1)`, where `MVP = projection * view * model`.

## Roadmap ideas

- Let games define their own `Update`/`Render` instead of editing `Application`
- Sprites and textures, plus batched rendering
- Mouse input and window resize handling (keep the camera aspect ratio in sync)
- Add the test target to CTest
