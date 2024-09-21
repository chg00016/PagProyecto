//
// Created by carmen on 20/09/2024.
//

#include "Renderer.h"




namespace PAG {
    Renderer* Renderer::instancia = nullptr;

    /**
    * Constructor por defecto
    */
    Renderer::Renderer ()
    { }

    /**
    * Destructor
    */
    Renderer::~Renderer ()
    { }

    void Renderer::inicializarOpenGL() {
        // - Establecemos un gris medio como color con el que se borrará el frame buffer.
        // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
        glClearColor ( 0.6, 0.6, 0.6, 1.0 );

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
        //Definimos el color base de la pantalla
        static float color = 0.6f;
        glClearColor(color, color, color, 1.0f);

        //Porcentaje de variacion del color
        static float colorVariation = 0.005f;

        //Si la rueda del raton se mueve hacia arriba
        if(yoffset > 0) {
            float min = 1;
            //cambiamos el color
            color -= colorVariation;
            if(min > color) {
                min = color;
            }
            //Si se pasa de 0 se resetea a 0
            if(color < 0.0f)
                color = 0.0f;

            //Si la rueda del raton se mueve hacia abajo
        }else if (yoffset < 0) {
            float max = 0;
            //cambiamos el color
            color += colorVariation;
            if(max < color) {
                max = color;
            }
            //Si se pasa de 1 se resetea a 1
            if(color > 1.0f)
                color = 1.0f;
        }
    }

    /**
     * Método para realizar un informe de gl
     */
    void Renderer::getInforme() {
        std::cout << glGetString ( GL_RENDERER ) << std::endl
        << glGetString ( GL_VENDOR ) << std::endl
        << glGetString ( GL_VERSION ) << std::endl
        << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
    }

}
