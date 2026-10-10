# Hel Engine

Hel is a 3D game engine using Vulkan, SDL3, and Dear ImGui.

## Build

Install the Vulkan SDK and make sure its installer has set `VULKAN_SDK`. SDL3
and Dear ImGui are built from the sources under `lib/vendored`.

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\bin\Debug\hel.exe
```

With a single-configuration generator such as Ninja, pass a build type when
configuring and run the executable directly from the matching output folder:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
.\build\bin\Debug\hel.exe
```
