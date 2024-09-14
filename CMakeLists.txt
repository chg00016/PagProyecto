cmake_minimum_required(VERSION 3.29)
project(PagProyecto)

set(CMAKE_CXX_STANDARD 20)

add_executable(PagProyecto main.cpp)
find_package(assimp)
find_package(opengl_system)
find_package(glm)
find_package(lodepng)
find_package(glfw3)
find_package(glad)
find_package(imgui)

# Then, link your executable or library with the corresponding package targets:

target_link_libraries(PagProyecto
        assimp::assimp
        opengl::opengl
        glm::glm
        lodepng::lodepng
        glfw
        glad::glad
        imgui::imgui)