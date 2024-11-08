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
        //PR5
        if(this->camara)
            delete camara;
        //PR6
        for(Modelo& modelo : modelos)
            modelo.destruirModelo();
        modelos.clear();
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
        int location = glGetUniformLocation ( shaders->getIdSP(), "view");
        glm::mat4 a = (camara->TransformacionMVision());
        glUniformMatrix4fv(location , 1, GL_FALSE, &a[0][0]);
        location = glGetUniformLocation ( shaders->getIdSP(), "projection");
        a = (camara->TransformacionMProyeccion());
        glUniformMatrix4fv(location , 1, GL_FALSE, &a[0][0]);
        //PR6
        for(Modelo &modelo: modelos) {
            location = glGetUniformLocation(shaders->getIdSP(), "model");
            glUniformMatrix4fv(location , 1, GL_FALSE, &modelo.getMatrizTransformacion()[0][0]);
            modelo.dibujarModelo();
        }
    }

    /**
     * Método para cambiar el tamaño de la ventana
     * @param width:entero que es ancho de la ventana
     * @param height:entero que es alto de la ventana
     */
    void Renderer::cambioTamViewport(GLFWwindow *window, int width, int height) {
        glViewport ( 0, 0, width, height );
        //PR5
        if(width == 0 && height == 0)
            camara->setAspecto(0);
        else
            camara->setAspecto((float)width / (float)height);
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
    void Renderer::setDireccionCamara(direccionCamara dir) {
        int arriba = 0, abajo = 0, izquierda = 0, derecha = 0;

        switch(dir) {
            case direccionCamara::arriba:
                arriba = 1;
            break;
            case direccionCamara::abajo:
                abajo = -1;
            break;
            case direccionCamara::izquierda:
                izquierda = -1;
            break;
            case direccionCamara::derecha:
                derecha = 1;
            break;
            case direccionCamara::reset:
                return;
        }

        switch(TipoMovCamara) {
            case CRANE:
                camara->crane(static_cast<float>(arriba + abajo) * 0.1f);
            break;
            case DOLLY:
                camara->dolly(static_cast<float>(izquierda + derecha) * 0.1f, -static_cast<float>(arriba + abajo) * 0.1f);
            break;
            case TILT:
                camara->tilt(static_cast<float>(arriba + abajo) * 1.0f);
            break;
            case PAN:
                camara->pan(-static_cast<float>(izquierda + derecha) * 1.0f);
            break;
            case ORBIT:
                camara->orbit(static_cast<float>(izquierda + derecha) * 3.0f, -static_cast<float>(arriba + abajo) * 3.0f);
            break;
        }
    }

    Camara& Renderer::getCamara() {
        return *camara;
    }

    //PR6
    void Renderer::crearModelo(const std::string &ruta) {
        modelos.emplace_back(ruta);
    }

    void Renderer::destruirModeloSeleccionado() {
        if(modeloSeleccionado >= 0) {
            modelos[modeloSeleccionado].destruirModelo();
            modelos.erase(modelos.begin() + modeloSeleccionado);
            modeloSeleccionado--;
        }
    }

    int Renderer::getModeloSeleccionado() const {
        return this->modeloSeleccionado;
    }

    void Renderer::setModeloSeleccionado(int seleccion) {
        this->modeloSeleccionado = seleccion;
    }

    int Renderer::getNumeroModelos() const {
        return (shaders->exito()) ? modelos.size() : 0;
    }

    void Renderer::setMovimientoModelo(modeloMovimiento movimiento) {
        this->movimientoModelo = movimiento;
    }

    void Renderer::setDireccionMovModelo(direccionMovimientoModelo direccion) {
        if(modeloSeleccionado < 0)
            return;

        int movimientoTipo1 = 0, movimientoTipo2 = 0, movimientoTipo3 = 0;

        switch(direccion) {
            case direccionMovimientoModelo::movimiento1:
                movimientoTipo1 = 1;
            break;
            case direccionMovimientoModelo::movimiento2:
                movimientoTipo1 = -1;
            break;
            case direccionMovimientoModelo::movimiento3:
                movimientoTipo2 = 1;
            break;
            case direccionMovimientoModelo::movimiento4:
                movimientoTipo2 = -1;
            break;
            case direccionMovimientoModelo::movimiento5:
                movimientoTipo3 = 1;
            break;
            case direccionMovimientoModelo::movimiento6:
                movimientoTipo3 = -1;
            break;
            case direccionMovimientoModelo::resetDireccion:
                return;
        }
        switch(movimientoModelo) {
            case modeloMovimiento::translacion:
                modelos[modeloSeleccionado].trasladar(glm::vec3(-movimientoTipo2, movimientoTipo1, movimientoTipo3));
            break;
            case modeloMovimiento::rotacion:
                modelos[modeloSeleccionado].rotar(5.0f, glm::vec3(movimientoTipo1, movimientoTipo2, movimientoTipo3));
            break;
            case modeloMovimiento::escalado:
                modelos[modeloSeleccionado].escalar(0.05f * glm::vec3(movimientoTipo1, movimientoTipo2, movimientoTipo3) + glm::vec3(1.0f));
            break;
        }
    }

}
