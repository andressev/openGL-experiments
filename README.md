# OpenGL Experiments

Learning OpenGL on Windows using GLFW and GLAD, built with CMake + MSVC.

## Dependencies

| Library | Location | Purpose |
|---------|----------|---------|
| [GLFW](https://www.glfw.org/) | `external/glfw/` | Window & input |
| [GLAD](https://glad.dav1d.de/) | `external/Glad/` | OpenGL loader |

Both are vendored — no install needed.

## Build

Requires Visual Studio 2022 (for `cl.exe` and `vcvars`) and CMake 3.10+.

```powershell
# Configure (Debug)
cmake --preset x64-debug

# Build
cmake --build out/build/x64-debug

# Run
.\out\build\x64-debug\learnOpenGL\learnOpenGL.exe
```

Available presets: `x64-debug`, `x64-release`, `x86-debug`, `x86-release`.

## Project layout

```
learnOpenGL/   # source files
external/      # vendored GLFW & GLAD
explanations/  # notes and references
out/           # cmake build output (git-ignored)
```
