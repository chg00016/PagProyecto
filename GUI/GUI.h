//
// Created by carme on 21/09/2024.
//

#ifndef GUI_H
#define GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_stdlib.h>

#include <vector>

#include "../Camara/Camara.h"
#include "imfilebrowser.h"

namespace PAG{
    enum direccionCamara {
        izquierda = 0,
        derecha,
        arriba,
        abajo,
        reset
    };

    enum direccionMovimientoModelo {
        movimiento1 = 0,
        movimiento2,
        movimiento3,
        movimiento4,
        movimiento5,
        movimiento6,
        resetDireccion
    };

    enum modeloMovimiento {
        translacion = 0,
        rotacion,
        escalado
    };

    class GUI {

    private:
        static GUI* instancia;
        GUI();
        ImVec4 color;
        std::vector<std::string> mensajes;
        //PR4
        std::string nombreShader = "";
        bool buttonPressed = false;
        //PR5
        movimientoCamara movimientoCam = TILT;
        direccionCamara direccionMovimiento = reset;
        float barraZoom;
        void panVentana();
        void tiltVentana();
        void dollyVentana();
        void craneVentana();
        void orbitVentana();
        void zoomVentana();
        //PR6
        ImGui::FileBrowser fileBrowser;
        bool destruirModeloSelecionado = false;
        direccionMovimientoModelo direccionMovModelo = resetDireccion;
        modeloMovimiento movimientoModelo = translacion;
        int numeroModelos = 0;
        int modeloSeleccionado = -1;
        void translacionVentana();
        void rotacionVentana();
        void escaladoVentana();
        void seleccionarMovModelo(const std::string& movimiento);
        //PR7
        bool mallaTriangulos = false;
        float componenteDifuso[3];
        float componeneteAmbiente[3];
        float componenteEspecular[3];
        float componenteBrillo;
        //PR8
        float luzDifusa[3];
        float luzAmbiente[3];
        float luzEspecular[3];
        float gamma;
        float s;
        int numeroLuces = 0;
        int luzSeleccionada = -1;
        void LuzFocalSetup();
        void LuzDireccionalPuntualSetup();
        void LuzAmbienteSetup();
    public:
        static GUI& getInstancia();
        virtual ~GUI();
        void setVentana();
        void inicializarImGUI(GLFWwindow* w);
        void newFrame();
        void render();
        void manipularVentana();
        ImVec4 getColor();
        void setColor(float r, float g, float b, float a) ;
        void liberarRecursos();
        void addmensaje(const std::string& mensaje);
        //PR4
        bool getbuttonPressed();
        void setButtonPressed(bool buttonPressed);
        std::string getNombreShader();
        //PR5
        void seleccionarCamara(const std::string& movimiento);
        movimientoCamara getMovimientoCamara();
        direccionCamara getDireccionCamara();
        void setBarraZoom(float barraZoom);
        void resetBotonCamara();
        float getBarraZoom();
        //PR6
        modeloMovimiento getModeloMovimiento() const;
        direccionMovimientoModelo getDireccionMovModelo() const;
        int getModeloSeleccionado() const;
        int getNumeroModelos() const;
        bool destruirModelo() const;
        void resetBotonDestruirModeloSeleccionado();
        void setModeloSeleccionado(int modeloSeleccionado);
        void setNumerosModelos(int numeroModelos);
        void resetBotonesModelo();
        //Seleccion de fichero modelo
        bool ModeloFicheroSeleccionado() const;
        std::string getModeloFichero();
        void borrarModeloFichero();
        //PR7
        float getComponenteBrillo() const;
        const float* getComponenteDifuso() const;
        const float* getComponenteAmbiente() const;
        const float* getComponenteEspecular() const;
        void setComponenteBrillo(float brillo);
        void setComponenteDifuso(float x, float y, float z);
        void setComponenteAmbiente(float x, float y, float z);
        void setComponenteEspecular(float x, float y, float z);
        void materialSubWindow();
        void moveConfigSubWindow();
        bool getmallaTriangulos() const;
        //PR8
        int getLuzSeleccionada() const;
        int getNumeroLuces() const;
        void setLuzSeleccionada(int luzSeleccionada);
        void setNumeroLuces(int numeroLuces);
    };
}

#endif //GUI_H