//
// Created by carmen on 20/09/2024.
//

#include "Renderer.h"




namespace PAG {
    Renderer* Renderer::instancia = nullptr;

    /**
    * @Brief Constructor por defecto
    */
    Renderer::Renderer () {
        clearColor = glm::vec4(0.6, 0.6, 0.6, 1.0);
        camara = new Camara();
    }

    /**
    * @Brief Destructor de Renderer
    */
    Renderer::~Renderer () {
        if ( idVBO != 0 ){
            glDeleteBuffers ( 1, &idVBO );
        }
        if ( idIBO != 0 ){
            glDeleteBuffers ( 1, &idIBO );
        }
        if ( idVAO != 0 ){
            glDeleteVertexArrays ( 1, &idVAO );
        }
        //no enlazado
        /**
        for (int i = 0; i < 2; i++) {
            if(noEntrelazadoidVBO[i] != 0){
                glDeleteBuffers ( 2, noEntrelazadoidVBO );
            }
        }*/
        //PR5
        if(this->camara)
            delete camara;
    }

    /**
     * @Brief Método que inicializa openGL
     */
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
        //PR3
        if(!shaders->exito())
            return;
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
        glUseProgram ( shaders->getIdSP());
        //PR5
        int location = glGetUniformLocation ( shaders->getIdSP(), "matrizMVP");
        glm::mat4 a = (camara->TransformacionMProyeccion()*camara->TransformacionMVision());
        glUniformMatrix4fv(location , 1, GL_FALSE, &a[0][0]);
        //
        glBindVertexArray ( idVAO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );

    }

    /**
     * Método para cambiar el tamaño de la ventana
     * @param width:entero que es ancho de la ventana
     * @param height:entero que es alto de la ventana
     */
    void Renderer::cambioTamViewport(GLFWwindow *window, int width, int height) {
        glViewport ( 0, 0, width, height );

    }

    /**
     * @Brief Método que cambia el color de fondo de la ventana al mover la rueda del ratón
     * @param window : ventana de glfw
     * @param xoffset : movimiento sobre el eje x de la rueda
     * @param yoffset : movimiento sobre el eje y de la rueda
     */
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

     /**
      * @Brief Getter de ClearColor
      * @return vector que es clearColor
      */
     glm::vec4 Renderer::getClearColor() {
        return this->clearColor;
    }

     /**
      * @Brief Setter de clearColor
      * @param r: Componente roja del color
      * @param g : Componente verde del color
      * @param b : Componente azul del color
      * @param t : Componente transparente del color
      */
     void Renderer::setClearColor(float r, float g, float b, float t) {
        this->clearColor = glm::vec4(r,g,b,t);
    }

     /**
      * @Brief Método para renderizar
      */
     void Renderer::render() {
        glClearColor(clearColor[0],clearColor[1], clearColor[2],clearColor[3]);
        //PR3
        glEnable ( GL_DEPTH_TEST );
        glEnable ( GL_MULTISAMPLE );

     }

//PR3
/**
* Método para crear el VAO para el modelo a renderizar
* @note No se incluye ninguna comprobación de errores
*/
void PAG::Renderer::creaModelo (){
    /**
    GLfloat vertices[] = { -.5, -.5, 0,.5, -.5, 0,.0, .5, 0 };
    GLfloat colores[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    */
    GLfloat verticesColores[] = { -.5, -.5, 0, 1.0, 0.0, 0.0, .5, -.5, 0, 0.0, 1.0, 0.0, .0, .5, 0, 0.0, 0.0, 1.0};
    GLuint indices[] = { 0, 1, 2 };

//VAO
    glGenVertexArrays ( 1, &idVAO );
    glBindVertexArray ( idVAO );
//idVBO no entrelazado
        /**
        glGenBuffers(2, noEntrelazadoidVBO);
        glBindBuffer(GL_ARRAY_BUFFER,  noEntrelazadoidVBO[0]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,  noEntrelazadoidVBO[1]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colores, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(1);
        */
//idVBO entrelazado
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verticesColores, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
//IBO
        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices,
                       GL_STATIC_DRAW);
}

    //PR4
    void Renderer::setShaderProgram(ShaderPrograms& shaderPrograms) {
        this->shaders = &shaderPrograms;
    }
    //PR5
    void Renderer::moverRaton(GLFWwindow* window,double xoffset, double yoffset) {
        static double xOldPos = 0.0;
        static double yOldPos = 0.0;

        int movY;
        int movX;

        if(glm::epsilonEqual(xoffset, yOldPos, glm::epsilon<double>()))
            movY = 0;
        else
            movY = (yoffset - yOldPos) > 0 ? -1 : 1;

        if(glm::epsilonEqual(yoffset, xOldPos, glm::epsilon<double>()))
            movX = 0;
        else
            movX = (xoffset - xOldPos) < 0 ? -1 : 1;

        if (clickIzquierdo){
            switch (TipoMovCamara) {
                case TILT:{camara->tilt(movY); break;}
                case PAN:{camara->pan(-movX); break;}
                case DOLLY:{camara->dolly(movX*0.01,movY*0.01); break;}
                case CRANE:{camara->crane(movY*0.01); break;}
                case ORBIT:{camara->orbit(movX,movY); break;}
                case ZOOM: {camara->zoom(movX);break;}

            }
        }
        xOldPos = xoffset;
        yOldPos = yoffset;
    }
    void Renderer::setClickIzquierdo(bool clickIzquierdo) {
        this->clickIzquierdo = clickIzquierdo;
    }

    void Renderer::setTipoMovCamara(movimientoCamara tipoMovCamara) {
        this->TipoMovCamara = tipoMovCamara;
    }

}
