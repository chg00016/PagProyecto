//
// Created by carme on 21/09/2024.
//

#ifndef GUI_H
#define GUI_H
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <array>
#include <vector>
#include <string>

namespace PAG{

    class GUI {

    private:
        static GUI* instancia;
        GUI();
        ImVec4 color;
        std::vector<std::string> mensajes;
    public:
        static GUI& getInstancia();
        virtual ~GUI();
        void setVentana();
        void inicializarImGUI(GLFWwindow* w);
        void newFrame();
        void render();
        void manipularVentana();
        void setTamanoVentana();
        void setPosicionVentana();
        ImVec4 getColor();
        void setColor(float r, float g, float b, float a) ;
        void liberarRecursos();
        void addmensaje(const std::string& mensaje);
    };

}




#endif //GUI_H
