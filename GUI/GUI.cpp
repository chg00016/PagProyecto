//
// Created by carme on 21/09/2024.
//

#include "GUI.h"

#include "../Camara/Camara.h"

namespace PAG {
    GUI* GUI::instancia = nullptr;

    GUI::GUI() {
        //PR6
        fileBrowser.SetTitle("Explorador de archivos");
        fileBrowser.SetTypeFilters({".obj"});
        //PR7
        for(int i = 0; i < 3; i++) {
            componenteDifuso[i] = 0.0f;
            componeneteAmbiente[i] = 0.0f;
            componenteEspecular[i] = 0.0f;
        }
        componenteBrillo = 0.0f;
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
        fileBrowser.Display();
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
        //Cuarta Ventana
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

            switch(movimientoCam) {
                case movimientoCamara::TILT:
                    tiltVentana();
                    break;
                case movimientoCamara::PAN:
                    panVentana();
                    break;
                case movimientoCamara::CRANE:
                    craneVentana();
                    break;
                case movimientoCamara::DOLLY:
                    dollyVentana();
                    break;
                case movimientoCamara::ORBIT:
                    orbitVentana();
                    break;
                case movimientoCamara::ZOOM:
                    zoomVentana();
                    break;
            }
        }
        ImGui::End();

        //PR6
        ImGui::SetNextWindowPos(ImVec2(ImVec2(40, 0)), ImGuiCond_Once);
        if(ImGui::Begin("Explorador de archivos")) { // La ventana está desplegada
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            if(ImGui::Button("Crear modelo con el fichero .obj"))
                fileBrowser.Open();
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(ImVec2(40, 0)), ImGuiCond_Once);
        if(ImGui::Begin("Transformaciones del modelo")) { // La ventana está desplegada
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::Text("Modelo seleccionado: ");

            for(int i = 0; i < numeroModelos; i++) {
                if(ImGui::Button(std::to_string(i).c_str()))
                    modeloSeleccionado = i;

                ImGui::SameLine();
                if(i == numeroModelos - 1)
                    if(ImGui::Button("Destruir Modelo"))
                        destruirModeloSelecionado = true;
            }
            //PR7
            ImGui::Separator();
            if(modeloSeleccionado != -1) {
                ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x * 0.4f, 400), ImGuiChildFlags_Borders,
                                  ImGuiWindowFlags_HorizontalScrollbar);
                moveConfigSubWindow();
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginChild("ChildR", ImVec2(0, 400), ImGuiChildFlags_Borders,
                                  ImGuiWindowFlags_HorizontalScrollbar);
                materialSubWindow();
                ImGui::EndChild();
            }
        }
        ImGui::End();
        if(ImGui::Begin("Propiedades del Render")) {
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::Checkbox("Malla de triangulos", &mallaTriangulos);
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

    void GUI::orbitVentana() {
        ImVec2 buttonSize(80, 20);

        if (ImGui::Button("UP", buttonSize))
            direccionMovimiento = arriba;
        ImGui::SameLine();
        if (ImGui::Button("DOWN", buttonSize))
            direccionMovimiento = abajo;
        if (ImGui::Button("LEFT", buttonSize))
            direccionMovimiento = izquierda;
        ImGui::SameLine();
        if (ImGui::Button("RIGHT", buttonSize))
            direccionMovimiento = derecha;
    }

    void GUI::dollyVentana() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("NORTH", buttonSize))
            direccionMovimiento = arriba;
        ImGui::SameLine();
        if(ImGui::Button("SOUTH", buttonSize))
            direccionMovimiento = abajo;
        if(ImGui::Button("WEST", buttonSize))
            direccionMovimiento = izquierda;
        ImGui::SameLine();
        if(ImGui::Button("EAST", buttonSize))
            direccionMovimiento = derecha;
    }

    void GUI::tiltVentana() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("UP", buttonSize))
            direccionMovimiento = arriba;
        if(ImGui::Button("DOWN", buttonSize))
            direccionMovimiento = abajo;
    }

    void GUI::panVentana() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("LEFT", buttonSize))
            direccionMovimiento = izquierda;
        ImGui::SameLine();
        if(ImGui::Button("RIGHT", buttonSize))
            direccionMovimiento = derecha;
    }

    void GUI::craneVentana() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("UP", buttonSize))
            direccionMovimiento = arriba;
        if(ImGui::Button("DOWN", buttonSize))
            direccionMovimiento = abajo;
    }

    void GUI::zoomVentana() {
        ImGui::SliderFloat("##xx", &barraZoom, 0.0f, 90.0f, "%.3f", ImGuiSliderFlags_None);
    }

    direccionCamara GUI::getDireccionCamara() {
        return this->direccionMovimiento;
    }

    void GUI::setBarraZoom(float barraZoom) {
        this->barraZoom = barraZoom;
    }

    void GUI::resetBotonCamara() {
       this->direccionMovimiento = reset;
    }

    float GUI::getBarraZoom() {
        return this->barraZoom;
    }

    //PR6
    void GUI::translacionVentana() {
        ImVec2 buttonSize(80, 20);

        if (ImGui::Button("ARRIBA", buttonSize))
            direccionMovModelo = movimiento1;
        ImGui::SameLine();
        if (ImGui::Button("ABAJO", buttonSize))
            direccionMovModelo = movimiento2;
        if (ImGui::Button("IZQUIERDA", buttonSize))
            direccionMovModelo = movimiento3;
        ImGui::SameLine();
        if (ImGui::Button("DERECHA", buttonSize))
            direccionMovModelo = movimiento4;
        if (ImGui::Button("HACIA DELANTE", buttonSize))
            direccionMovModelo = movimiento5;
        ImGui::SameLine();
        if (ImGui::Button("HACIA ATRÁS", buttonSize))
            direccionMovModelo = movimiento6;
    }

    void GUI::rotacionVentana() {
        ImVec2 buttonSize(140, 20);

        ImGui::Text("Rotacion eje X");
        if (ImGui::Button("CLOCKWISE##01", buttonSize))
            direccionMovModelo = movimiento1;
        ImGui::SameLine();
        if (ImGui::Button("COUNTER CLOCKWISE##01", buttonSize))
            direccionMovModelo = movimiento2;

        ImGui::Text("Rotacion eje Y");
        if (ImGui::Button("CLOCKWISE##02", buttonSize))
            direccionMovModelo = movimiento3;
        ImGui::SameLine();
        if (ImGui::Button("COUNTER CLOCKWISE##02", buttonSize))
            direccionMovModelo = movimiento4;

        ImGui::Text("Rotacion eje Z");
        if (ImGui::Button("CLOCKWISE##03", buttonSize))
            direccionMovModelo = movimiento5;
        ImGui::SameLine();
        if (ImGui::Button("COUNTER CLOCKWISE##03", buttonSize))
            direccionMovModelo = movimiento6;
    }

    void GUI::seleccionarMovModelo(const std::string& movimiento) {
        if(movimiento == "Translacion")
            movimientoModelo = modeloMovimiento::translacion;
        else if(movimiento == "Rotacion")
            movimientoModelo = modeloMovimiento::rotacion;
        else if(movimiento == "Escalado")
            movimientoModelo = modeloMovimiento::escalado;
    }

    void GUI::escaladoVentana() {
        ImVec2 buttonSize(100, 20);

        ImGui::Text("Escala en eje X");
        if (ImGui::Button("AUMENTA##01", buttonSize))
            direccionMovModelo = movimiento1;
        ImGui::SameLine();
        if (ImGui::Button("DECREMENTA##01", buttonSize))
            direccionMovModelo = movimiento2;

        ImGui::Text("Escala en eje Y");
        if (ImGui::Button("AUMENTA##02", buttonSize))
            direccionMovModelo = movimiento3;
        ImGui::SameLine();
        if (ImGui::Button("DECREMENTA##02", buttonSize))
            direccionMovModelo = movimiento4;

        ImGui::Text("Escala en eje Z");
        if (ImGui::Button("AUMENTA##03", buttonSize))
            direccionMovModelo = movimiento5;
        ImGui::SameLine();
        if (ImGui::Button("DECREMENTA##03", buttonSize))
            direccionMovModelo = movimiento6;
    }

    modeloMovimiento GUI::getModeloMovimiento() const {
        return movimientoModelo;
    }

    direccionMovimientoModelo GUI::getDireccionMovModelo() const {
        return direccionMovModelo;
    }

    int GUI::getModeloSeleccionado() const {
        return modeloSeleccionado;
    }

    int GUI::getNumeroModelos() const {
        return numeroModelos;
    }

    bool GUI::destruirModelo() const {
        return destruirModeloSelecionado;
    }

    void GUI::resetBotonDestruirModeloSeleccionado() {
        destruirModeloSelecionado = false;
    }

    void GUI::setModeloSeleccionado(int modeloSeleccionado) {
        this->modeloSeleccionado = modeloSeleccionado;
    }

    void GUI::setNumerosModelos(int numeroModelos) {
        this->numeroModelos = numeroModelos;
        if(this->numeroModelos <= 0)
            modeloSeleccionado--;
    }

    void GUI::resetBotonesModelo() {
        direccionMovModelo = resetDireccion;
    }

    bool GUI::ModeloFicheroSeleccionado() const {
        return fileBrowser.HasSelected();
    }

    std::string GUI::getModeloFichero() {
        return fileBrowser.GetSelected().string();
    }

    void GUI::borrarModeloFichero() {
        fileBrowser.ClearSelected();
    }
//PR7

    float GUI::getComponenteBrillo() const {
        return componenteBrillo;
    }
    const float* GUI::getComponenteDifuso() const {
        return componenteDifuso;
    }
    const float* GUI::getComponenteAmbiente() const {
        return componeneteAmbiente;
    }
    const float* GUI::getComponenteEspecular() const {
        return componenteEspecular;
    }

    void GUI::setComponenteBrillo(float brillo) {
        componenteBrillo = brillo;
    }

    void GUI::setComponenteDifuso(float x, float y, float z) {
        componenteDifuso[0] = x;
        componenteDifuso[1] = y;
        componenteDifuso[2] = z;
    }

    void GUI::setComponenteAmbiente(float x, float y, float z) {
        componeneteAmbiente[0] = x;
        componeneteAmbiente[1] = y;
        componeneteAmbiente[2] = z;
    }

    void GUI::setComponenteEspecular(float x, float y, float z) {
        componenteEspecular[0] = x;
        componenteEspecular[1] = y;
        componenteEspecular[2] = z;
    }

    void GUI::materialSubWindow() {
        ImGui::Text("Material del modelo:");
        int nColumns = 4;

        ImGui::Columns(nColumns);
        ImGui::Text("Color difuso"); ImGui::NextColumn();
        ImGui::Text("Color ambiente"); ImGui::NextColumn();
        ImGui::Text("Color especular"); ImGui::NextColumn();
        ImGui::Text("Exponente de Brillo"); ImGui::NextColumn();

        for(int i = 0; i < 3; i++) {
            if (i > 0) ImGui::SameLine();
            ImGui::PushID(i);
            ImGui::VSliderFloat("##v", ImVec2(15, 160), &componenteDifuso[i], 0.0f, 1.0f, "");
            ImGui::PopID();
        }
        ImGui::NextColumn();

        for(int i = 0; i < 3; i++) {
            if (i > 0) ImGui::SameLine();
            ImGui::PushID(i + 3);
            ImGui::VSliderFloat("##v", ImVec2(15, 160), &componeneteAmbiente[i], 0.0f, 1.0f, "");
            ImGui::PopID();
        }
        ImGui::NextColumn();

        for(int i = 0; i < 3; i++) {
            if (i > 0) ImGui::SameLine();
            ImGui::PushID(i + 6);
            ImGui::VSliderFloat("##v", ImVec2(15, 160), &componenteEspecular[i], 0.0f, 1.0f, "");
            ImGui::PopID();
        }
        ImGui::NextColumn();

        ImGui::VSliderFloat("##v", ImVec2(18, 160), &componenteBrillo, 0.0f, 1.0f, "");
        ImGui::NextColumn();
    }

    void GUI::moveConfigSubWindow() {
        const char* MovesStr[] = {"Translacion","Rotacion","Escalado"};
        size_t numMovimientos = 3;
        static unsigned int movSeleccionado = 0;

        ImGui::Text("Transformaciones del Modelo:");
        if(ImGui::BeginCombo("##", MovesStr[movSeleccionado], ImGuiComboFlags_HeightLargest | ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_WidthFitPreview)) {
            for(int i = 0; i < numMovimientos; i++) {
                const bool seleccionado = (movSeleccionado == i);
                if(ImGui::Selectable(MovesStr[i], seleccionado)) {
                    movSeleccionado = i;
                    seleccionarMovModelo(MovesStr[movSeleccionado]);
                }

                if(seleccionado)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        switch(movimientoModelo) {
            case modeloMovimiento::translacion:
                translacionVentana();
            break;
            case modeloMovimiento::rotacion:
                rotacionVentana();
            break;
            case modeloMovimiento::escalado:
                escaladoVentana();
        }
    }
    bool GUI::getmallaTriangulos() const {
        return mallaTriangulos;
    }


}

