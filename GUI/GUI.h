//
// Created by carme on 21/09/2024.
//

#ifndef GUI_H
#define GUI_H
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


namespace PAG{
    class GUI {
    private:
        static GUI* instancia;
        GUI();
    public:
        static GUI& getInstancia();
        virtual ~GUI();
        void setVentana();
        void inicializarImGUI(GLFWwindow* w);
        void newFrame();
        void render();
        void cerrarVentana();

    };

}




#endif //GUI_H
