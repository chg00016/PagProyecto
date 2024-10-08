//
// Created by carmen on 20/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../Shader/ShaderPrograms.h"

namespace PAG {
    class Renderer {
    private:
        static Renderer* instancia;
        Renderer();
        glm::vec4 clearColor;
        //PR3
        GLuint idVAO = 0; // Identificador del vertex array object
        GLuint idVBO = 0; // Identificador del vertex buffer object
        GLuint idIBO = 0; // Identificador del index buffer object
        std::string codigoVS = "";
        std::string codigoFS = "";
        bool problemaShader = false;
        //GLuint noEntrelazadoidVBO[2];
        //PR4
        ShaderPrograms *shaders;
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
        //PR3
        void creaShaderProgram();
        void cargarShader(const std::string& ruta);
        void creaModelo();
        //PR4
        void setShaderProgram(ShaderPrograms& shaderPrograms);
        

    };
}




#endif //RENDERER_H
