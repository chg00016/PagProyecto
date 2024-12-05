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
#include "../Luz/Luz.h"

namespace PAG {
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
        //PR7
        bool mallaTriangulos = false;
        //PR8
        int luzSeleccionada = -1;
        std::array<Luz, 4> luces;
    public:
        static Renderer& getInstancia();
        virtual ~Renderer();
        void refrescar();
        void inicializarOpenGL();
        void cambioTamViewport(GLFWwindow *window, int width, int height);
        void ruedaRaton(GLFWwindow *window, double xoffset, double yoffset);
        std::string getInforme();
        glm::vec4 getClearColor();
        void setClearColor(float r, float g, float b, float t);
        //PR3
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
        bool setModeloSeleccionado(int seleccion);
        int getNumeroModelos() const;
        void setMovimientoModelo(modeloMovimiento movimiento);
        void setDireccionMovModelo(direccionMovimientoModelo direccion);
        //PR7
        const glm::vec3& getDifusaModelo();
        const glm::vec3& getAmbienteModelo();
        const glm::vec3& getEspecularModelo();
        float getBrilloModelo();
        void setMallaTriangulos(bool mallaTriangulos);
        void setDifusaModelo(const float* dif);
        void setAmbienteModelo(const float* amb);
        void setEspecularModelo(const float* espec);
        void setBrilloModelo(float brillo);

        //PR8
        const glm::vec3& getLuzDifusa();
        const glm::vec3& getLuzAmbiente();
        const glm::vec3& getLuzEspecular();
        float getLuzGamma();
        float getLuzAtenuacion();
        int getLuzSeleccionada() const;
        void setLuzDifusa(const float* diff);
        void setLuzAmbiente(const float* amb);
        void setLuzEspecular(const float* espec);
        void setLuzGamma(float gamma);
        void setLuzAtenuacion(float s);
        bool setLuzSeleccionada(int seleccionada);
    };
}

#endif //RENDERER_H