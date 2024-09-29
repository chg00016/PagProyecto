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
    }

    /**
    * @Brief Destructor de Renderer
    */
    Renderer::~Renderer () {
        if ( idVS != 0 ){
            glDeleteShader ( idVS );
        }
        if ( idFS != 0 ){
            glDeleteShader ( idFS );
        }
        if ( idSP != 0 ){
            glDeleteProgram ( idSP );
        }
        if ( idVBO != 0 ){
            glDeleteBuffers ( 1, &idVBO );
        }
        if ( idIBO != 0 ){
            glDeleteBuffers ( 1, &idIBO );
        }
        if ( idVAO != 0 ){
            glDeleteVertexArrays ( 1, &idVAO );
        }
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
        if(problemaShader)
            return;
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
        glUseProgram ( idSP );
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
* Método para crear, compilar y enlazar el shader program
* @note No se incluye ninguna comprobación de errores
*/
void PAG::Renderer::creaShaderProgram(){

    idVS = glCreateShader ( GL_VERTEX_SHADER );
        if(idVS == 0) {
            problemaShader = true;
            throw std::runtime_error ("[PAG::Renderer::creaShaderProgram]: Error creating vertex shader");
        }

    const GLchar* fuenteVS = codigoVS.c_str ();
    glShaderSource ( idVS, 1, &fuenteVS, nullptr );
    glCompileShader ( idVS );

        GLint resultadoCompilacionVS;
        glGetShaderiv ( idVS, GL_COMPILE_STATUS, &resultadoCompilacionVS );

        if ( resultadoCompilacionVS == GL_FALSE )
        {  // Ha habido un error en la compilación.
            // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv ( idVS, GL_INFO_LOG_LENGTH, &tamMsj );
            if ( tamMsj > 0 )
            {  GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog ( idVS, tamMsj, &datosEscritos, mensajeFormatoC );
                mensaje.assign ( mensajeFormatoC );
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error compiling vertex shader\n  " + mensaje);
        }
//---------------------
    idFS = glCreateShader ( GL_FRAGMENT_SHADER );
        if(idFS == 0) {
            problemaShader = true;
            throw std::runtime_error ("[PAG::Renderer::creaShaderProgram]: Error creating fragment shader");
        }

    const GLchar* fuenteFS = codigoFS.c_str ();
    glShaderSource ( idFS, 1, &fuenteFS, nullptr );
    glCompileShader ( idFS );

        GLint resultadoCompilacionFS;
        glGetShaderiv ( idFS, GL_COMPILE_STATUS, &resultadoCompilacionFS );


        if ( resultadoCompilacionFS == GL_FALSE )
        {  // Ha habido un error en la compilación.
            // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv ( idFS, GL_INFO_LOG_LENGTH, &tamMsj );
            if ( tamMsj > 0 )
            {  GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog ( idFS, tamMsj, &datosEscritos, mensajeFormatoC );
                mensaje.assign ( mensajeFormatoC );
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error compiling fragment shader\n  " + mensaje);
        }
//---------------------

    idSP = glCreateProgram ();
        if(idSP == 0) {
            problemaShader = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error creating the shader program");
        }
    glAttachShader ( idSP, idVS );
    glAttachShader ( idSP, idFS );
    glLinkProgram ( idSP );

        glLinkProgram ( idSP );
        GLint resultadoEnlazado = 0;
        glGetProgramiv ( idSP, GL_LINK_STATUS, &resultadoEnlazado );
        if ( resultadoEnlazado == GL_FALSE )
        {  // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv ( idSP, GL_INFO_LOG_LENGTH, &tamMsj );
            if ( tamMsj > 0 )
            {  GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog ( idSP, tamMsj, &datosEscritos, mensajeFormatoC );
                mensaje.assign ( mensajeFormatoC );
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
        throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error linking the program");
        }
}

/**
 * Método que carga de archivo de texto el código fuente del shader
 */
void PAG::Renderer::cargarShader(const std::string& ruta) {
        std::ifstream archivoShader;

        archivoShader.open ( ruta + "-vs.glsl" );
        if ( !archivoShader.is_open () ){
            problemaShader = true;
            throw std::runtime_error("[PAG::Renderer::obtenerShaders]: Error en la apertura del archivo");
        }

        std::stringstream streamShader;
        streamShader << archivoShader.rdbuf ();
        codigoVS = streamShader.str ();

        archivoShader.close ();

        //-------------
        streamShader.str(std::string());
        archivoShader.open(ruta + "-fs.glsl");
        if( !archivoShader.is_open() ){
            problemaShader = true;
            throw std::runtime_error("[PAG::Renderer::obtenerShaders]: Error en la apertura del archivo");
        }
        streamShader << archivoShader.rdbuf();
        codigoFS = streamShader.str();

        archivoShader.close();
    }

/**
* Método para crear el VAO para el modelo a renderizar
* @note No se incluye ninguna comprobación de errores
*/
void PAG::Renderer::creaModelo (){
    GLfloat vertices[] = { -.5, -.5, 0,.5, -.5, 0,.0, .5, 0 };
    GLuint indices[] = { 0, 1, 2 };
    glGenVertexArrays ( 1, &idVAO );
    glBindVertexArray ( idVAO );

        glGenBuffers ( 1, &idVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, idVBO );
        glBufferData ( GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices,
        GL_STATIC_DRAW );
        glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),
        nullptr );
        glEnableVertexAttribArray ( 0 );
        glGenBuffers ( 1, &idIBO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLuint), indices,
        GL_STATIC_DRAW );
}

}
