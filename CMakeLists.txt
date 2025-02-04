cmake_minimum_required(VERSION 3.10)
project(Voxel_Engine)

set(CMAKE_CXX_STANDARD 20)

# Find OpenGL
find_package(OpenGL REQUIRED)

add_subdirectory(libs/sdl2)
add_subdirectory(libs/glad)
add_subdirectory(libs/glm)
add_subdirectory(libs/spdlog)
add_subdirectory(libs/yaml-cpp)

# Recover all src files
file(GLOB_RECURSE SRC
        "src/*.h"
        "src/*.cpp"
)

# Because ImGUI doesn't have a Cmake file...
file(GLOB IMGUI_SRC
        "libs/imgui/*.h"
        "libs/imgui/*.cpp"
        "libs/imgui/backends/imgui_impl_sdl2*"
        "libs/imgui/backends/imgui_impl_opengl3*"
        "libs/imgui/misc/cpp/imgui_stdlib.*"
)

add_executable(Voxel_Engine ${IMGUI_SRC} ${SRC})

# Add include directories
target_include_directories(Voxel_Engine PRIVATE
        "src"
        "libs/sdl2/include/"
        "libs/glad/include/"
        "libs/glm/"
        "libs/spdlog/include/"
        "libs/yaml-cpp/include/"
        "libs/imgui/"
        "libs/imgui/backends/"
        "libs/imgui/misc/cpp"
)

target_compile_definitions(Voxel_Engine PRIVATE ASSET_DIRECTORY="${CMAKE_SOURCE_DIR}/assets/")

#Add precompiled headers
target_precompile_headers(Voxel_Engine PRIVATE src/pch.h)

# Link libraries to the project
target_link_libraries(Voxel_Engine PRIVATE ${OPENGL_LIBRARY} SDL2::SDL2 glad glm spdlog yaml-cpp)