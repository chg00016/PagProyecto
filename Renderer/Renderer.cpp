//
// Created by carmen on 20/09/2024.
//

#include "Renderer.h"




namespace PAG {
    Renderer* Renderer::instancia = nullptr;

    /**
    * Constructor por defecto
    */
    Renderer::Renderer () {
        clearColor = glm::vec4(0.6, 0.6, 0.6, 1.0);
    }

    /**
    * Destructor
    */
    Renderer::~Renderer ()
    { }

    void Renderer::inicializarOpenGL() {
        // - Establecemos un gris medio como color con el que se borrará el frame buffer.
        // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
        glClearColor ( clearColor.r,clearColor.g,clearColor.b,clearColor.a);

        // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
        // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
        glEnable ( GL_DEPTH_TEST );
    }

    /**
    * Consulta del objeto único de la clase
    * @return La dirección de memoria del objeto
    */
    Renderer& Renderer::getInstancia (){
        if (!instancia)
            instancia = new Renderer;
    return *instancia;
    }

    /**
    * Método para hacer el refresco de la escena
    */
    void Renderer::refrescar (){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /**
     * Método para cambiar el tamaño de la ventana
     * @param width:entero que es ancho de la ventana
     * @param height:entero que es alto de la ventana
     */
    void Renderer::cambioTamViewport(GLFWwindow *window, int width, int height) {
        glViewport ( 0, 0, width, height );

    }

    void Renderer::ruedaRaton(GLFWwindow *window, double xoffset, double yoffset) {
        //Porcentaje de variacion del color
        float colorVariacion =  0.005f;

        //Si la rueda del raton se mueve hacia abajo
        if (yoffset < 0){
            float min = clearColor[0];
            for(int i = 0; i < glm::vec4::length()-1; i++) {
                clearColor[i] -= colorVariacion;
                if(min > clearColor[i])
                    min = clearColor[i];
            }

            if(min < 0)
                for(int i = 0; i < glm::vec4::length()-1; i++)
                    if(clearColor[i] < 0)
                    clearColor[i] -= min;
            //Si la rueda del raton se mueve hacia arriba
        }else if(yoffset > 0) {
            float max = -1;
            for(int i = 0; i < glm::vec4::length()-1; i++) {
                clearColor[i] += colorVariacion;
                if(max < clearColor[i])
                    max = clearColor[i];
            }
            //Si se pasa de 1 se resetea a 1
            if(max > 1)
                for(int i = 0; i < glm::vec4::length(); i++)
                    clearColor[i] /= max;

        }
    }

    /**
     * Método para realizar un informe de gl
     */
     std::string Renderer::getInforme() {
        std::string informe;
        informe.append((const char*)glGetString ( GL_RENDERER ));
        informe.push_back('\n');
        informe.append((const char*)glGetString ( GL_VENDOR ));
        informe.push_back('\n');
        informe.append((const char*)glGetString ( GL_VERSION ));
        informe.push_back('\n');
        informe.append((const char*)glGetString ( GL_SHADING_LANGUAGE_VERSION ));

        return informe;
    }

    glm::vec4 Renderer::getClearColor() {
        return this->clearColor;
    }

    void Renderer::setClearColor(float r, float g, float b, float t) {
        this->clearColor = glm::vec4(r,g,b,t);
    }
     void Renderer::render() {
        glClearColor(clearColor[0],clearColor[1], clearColor[2],clearColor[3]);
     }


}
