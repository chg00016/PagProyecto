//
// Created by carme on 21/09/2024.
//

#include "GUI.h"

#include <iostream>
#include <ostream>

#include "../Camara/Camara.h"

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

    void GUI::liberarRecursos() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext ();

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

    void GUI::addmensaje(const std::string& mensaje) {
        this->mensajes.push_back(mensaje);
    }

    ImVec4 GUI::getColor() {
        return color;
    }

    void GUI::setColor(float r, float g, float b, float a) {
        color = ImVec4(r, g, b, a);
    }

    void GUI::manipularVentana() {

        //Primera ventana
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        if ( ImGui::Begin ( "Mensajes" ) ){ // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            for(int i= 0; i< mensajes.size();i++) {
                ImGui::Text(mensajes[i].c_str());
            }

        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End ();

        //Segunda ventana
        ImGui::SetNextWindowPos(ImVec2(10, 0), ImGuiCond_Once);
        if ( ImGui::Begin ( "Fondo" ) ){ // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::ColorPicker4("Actual", (float*)&color,
                             ImGuiColorEditFlags_PickerHueWheel |
                                 ImGuiColorEditFlags_DisplayRGB |
                                 ImGuiColorEditFlags_DisplayHSV |
                                 ImGuiColorEditFlags_DisplayHex
                               | ImGuiColorEditFlags_NoAlpha);
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End ();

        //PR4
        //Tercera ventana
        ImGui::SetNextWindowPos(ImVec2(20, 0), ImGuiCond_Once);
        if ( ImGui::Begin ( "Shader" ) ){ // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::InputText( "##", &nombreShader, ImGuiInputTextFlags_AutoSelectAll );
            buttonPressed = ImGui::Button ( "Load" );
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End ();

        //PR5
        ImGui::SetNextWindowPos(ImVec2(40, 0), ImGuiCond_Once);
        if(ImGui::Begin("Camera")) {
            ImGui::SetWindowFontScale(1.0f);

            const char* cameraMoveStr[] = {"Tilt","Pan","Crane", "Dolly", "Orbit", "Zoom"};
            size_t cameraNumberMoves = 6;
            static unsigned int moveSelected = 0;

            ImGui::Text("Camera movement: "); ImGui::SameLine();
            if(ImGui::BeginCombo("##", cameraMoveStr[moveSelected], ImGuiComboFlags_HeightLargest | ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_WidthFitPreview)) {
                for(int i = 0; i < cameraNumberMoves; i++) {
                    const bool selected = (moveSelected == i);
                    if(ImGui::Selectable(cameraMoveStr[i], selected)) {
                        moveSelected = i;
                        seleccionarCamara(cameraMoveStr[moveSelected]);
                    }

                    if(selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }
        ImGui::End();
    }

    bool GUI::getbuttonPressed() {
        return this->buttonPressed;
    }


    void GUI::setButtonPressed(bool buttonPressed) {
        this->buttonPressed = buttonPressed;
    }

    std::string GUI::getNombreShader() {
        return this->nombreShader;
    }
    //PR5
    void GUI::seleccionarCamara(const std::string& movimiento) {
        if(movimiento == "Tilt")
            movimientoCam = movimientoCamara::TILT;
        else if(movimiento == "Pan")
            movimientoCam = movimientoCamara::PAN;
        else if(movimiento == "Crane")
            movimientoCam = movimientoCamara::CRANE;
        else if(movimiento == "Dolly")
            movimientoCam = movimientoCamara::DOLLY;
        else if(movimiento == "Orbit")
            movimientoCam = movimientoCamara::ORBIT;
        else if(movimiento == "Zoom")
            movimientoCam = movimientoCamara::ZOOM;
    }

    movimientoCamara GUI::getMovimientoCamara() {
        return this->movimientoCam;
    }

}

