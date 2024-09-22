//
// Created by carmen on 20/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <iostream>
#include <ostream>

namespace PAG {
    class Renderer {
    private:
        static Renderer* instancia;
        Renderer();
        glm::vec4 clearColor;
    public:
        static Renderer& getInstancia();
        virtual ~Renderer();
        void refrescar();
        void inicializarOpenGL();
        void consultarOpenGL();
        void cambioTamViewport(GLFWwindow *window, int width, int height);
        void ruedaRaton(GLFWwindow *window, double xoffset, double yoffset);
        std::string getInforme();
        glm::vec4 getClearColor();
        void setClearColor(float r, float g, float b, float t);
        void render();
        

    };
}




#endif //RENDERER_H
