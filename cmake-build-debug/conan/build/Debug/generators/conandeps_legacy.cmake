message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(lodepng)
find_package(assimp)
find_package(glm)
find_package(imgui)
find_package(glad)
find_package(glfw3)
find_package(opengl_system)

set(CONANDEPS_LEGACY  lodepng::lodepng  assimp::assimp  glm::glm  imgui::imgui  glad::glad  glfw  opengl::opengl )