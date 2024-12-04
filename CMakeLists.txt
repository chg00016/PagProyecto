cmake_minimum_required(VERSION 3.29)
project(PagProyecto)

set(CMAKE_CXX_STANDARD 20)

file(GLOB IMGUI_SRC_FILES imgui/src/*.cpp)
file(GLOB GLAD_SRC_FILES GLAD/src/*.c)

add_executable(PagProyecto main.cpp
        Renderer/Renderer.cpp
        Renderer/Renderer.h
        GUI/GUI.cpp GUI/GUI.h ${IMGUI_SRC_FILES}
        ${GLAD_SRC_FILES}
        Shader/Shader.cpp
        Shader/Shader.h
        Shader/ShaderPrograms.cpp
        Shader/ShaderPrograms.h
        Camara/Camara.cpp
        Camara/Camara.h
        Modelo/Modelo.cpp
        Modelo/Modelo.h
        GUI/imfilebrowser.h
        Material/Material.cpp
        Material/Material.h
        Luz/Luz.cpp
        Luz/Luz.h
        Luz/luzAplicador/luzAplicador.h
        Luz/LuzAplicador/LuzAmbienteAplicador/LuzAmbienteAplicador.cpp
        Luz/LuzAplicador/LuzAmbienteAplicador/LuzAmbienteAplicador.h
        Luz/LuzAplicador/LuzDireccionalAplicador/LuzDireccionalAplicador.cpp
        Luz/LuzAplicador/LuzDireccionalAplicador/LuzDireccionalAplicador.h
        Luz/LuzAplicador/LuzFocalAplicador/LuzFocalAplicador.cpp
        Luz/LuzAplicador/LuzFocalAplicador/LuzFocalAplicador.h
        Luz/LuzAplicador/LuzPuntualAplicador/LuzPuntualAplicador.cpp
        Luz/LuzAplicador/LuzPuntualAplicador/LuzPuntualAplicador.h
        Luz/PropiedadesLuz.h)

target_include_directories( ${PROJECT_NAME} PUBLIC imgui/headers )
target_include_directories( ${PROJECT_NAME} PUBLIC GLAD/include )

find_package(assimp)
find_package(opengl_system)
find_package(glm)
find_package(glfw3)
# Then, link your executable or library with the corresponding package targets:

target_link_libraries(PagProyecto
        assimp::assimp
        opengl::opengl
        glm::glm
        glfw)