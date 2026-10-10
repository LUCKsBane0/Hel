cmake_minimum_required(VERSION 3.16)

project(hel VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>")

# Vulkan is supplied by the Vulkan SDK. CMake uses VULKAN_SDK automatically
# when it is set by the SDK installer.
find_package(Vulkan REQUIRED)

# Build the vendored SDL3 source without its tests or examples.
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/vendored/SDL EXCLUDE_FROM_ALL)

# Dear ImGui does not provide a CMake target, so compile its core together
# with the SDL3 platform backend and Vulkan renderer backend.
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/vendored/imgui")

add_library(hel_imgui STATIC
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp"
)
add_library(hel::imgui ALIAS hel_imgui)

target_include_directories(hel_imgui
    PUBLIC
        "${IMGUI_DIR}"
        "${IMGUI_DIR}/backends"
)
target_compile_features(hel_imgui PUBLIC cxx_std_20)
target_link_libraries(hel_imgui
    PUBLIC
        SDL3::SDL3
        Vulkan::Vulkan
)

add_executable(hel
    src/main.cpp
    src/Application.cpp
)

target_include_directories(hel PRIVATE include)
target_compile_features(hel PRIVATE cxx_std_20)
target_link_libraries(hel
    PRIVATE
        SDL3::SDL3
        Vulkan::Vulkan
        hel::imgui
)

if(MSVC)
    target_compile_options(hel PRIVATE /W4 /permissive- /utf-8)
else()
    target_compile_options(hel PRIVATE -Wall -Wextra -Wpedantic)
endif()
