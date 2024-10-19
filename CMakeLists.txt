cmake_minimum_required(VERSION 3.29)
project(PagProyecto)

set(CMAKE_CXX_STANDARD 20)
file(GLOB IMGUI_SRC_FILES imgui/*.cpp)
add_executable(PagProyecto main.cpp
        Renderer/Renderer.cpp
        Renderer/Renderer.h
        GUI/GUI.cpp GUI/GUI.h ${IMGUI_SRC_FILES}
        Shader/Shader.cpp
        Shader/Shader.h
        Shader/ShaderPrograms.cpp
        Shader/ShaderPrograms.h
        Camara/Camara.cpp
        Camara/Camara.h)
target_include_directories( ${PROJECT_NAME} PUBLIC imgui )
find_package(opengl_system)
find_package(glm)
find_package(glfw3)
find_package(glad)

# Then, link your executable or library with the corresponding package targets:

target_link_libraries(PagProyecto
        
        opengl::opengl
        glm::glm

        glfw
        glad::glad)