//
// Created by carme on 21/09/2024.
//

#ifndef GUI_H
#define GUI_H
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>
#include <imgui_stdlib.h>
#include "../Camara/Camara.h"

namespace PAG{

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
        movimientoCamara movimientoCam;
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
    };

}




#endif //GUI_H
