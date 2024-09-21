//
// Created by carme on 21/09/2024.
//

#include "GUI.h"
namespace PAG {
    GUI* GUI::instancia = nullptr;

    GUI::GUI() {
    }
    void GUI::inicializarImGUI(GLFWwindow* w) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext ();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        // Aquí w es el puntero a la ventana GLFW (GLFWwindow*)
        ImGui_ImplGlfw_InitForOpenGL ( w, true );
        ImGui_ImplOpenGL3_Init ();

    }

    GUI &GUI::getInstancia() {
        if (!instancia)
            instancia = new GUI;
        return *instancia;
    }

    GUI::~GUI() {
    }

    void GUI::setVentana() {
        ImGui::SetNextWindowPos ( ImVec2 (10, 10), ImGuiCond_Once );

    }

    void GUI::newFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }

    void GUI::render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
    }

    void cerrarVentana() {
        if ( ImGui::Begin ( "Mensajes" ) )
        { // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
            // Pintamos los controles
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End ();

    }
}

