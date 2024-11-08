//
// Created by carmen on 20/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/vec4.hpp>
#include <fstream>

#include "../Shader/ShaderPrograms.h"
#include "../Camara/Camara.h"
#include "../GUI/GUI.h"
#include "../Modelo/Modelo.h"

namespace PAG {
    class Camara;

    class Renderer {
    private:
        static Renderer* instancia;
        Renderer();
        glm::vec4 clearColor;
        //PR3
        std::string codigoVS = "";
        std::string codigoFS = "";
        bool problemaShader = false;
        //PR4
        ShaderPrograms *shaders;
        //PR5
        Camara* camara;
        bool clickIzquierdo;
        double *ratonPosX, *ratonPosY;
        movimientoCamara TipoMovCamara;
        //PR6
        std::vector<Modelo> modelos;
        int modeloSeleccionado = -1;
        modeloMovimiento movimientoModelo;
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
        //PR5
        void moverRaton(GLFWwindow* window,double xoffset, double yoffset);
        void setClickIzquierdo(bool clickIzquierdo);
        void setTipoMovCamara(movimientoCamara tipoMovCamara);
        void setDireccionCamara(direccionCamara dir);
        Camara& getCamara();
        //PR6
        void crearModelo(const std::string& ruta);
        void destruirModeloSeleccionado();
        int getModeloSeleccionado() const;
        void setModeloSeleccionado(int seleccion);
        int getNumeroModelos() const;
        void setMovimientoModelo(modeloMovimiento movimiento);
        void setDireccionMovModelo(direccionMovimientoModelo direccion);
    };
}

#endif //RENDERER_H
