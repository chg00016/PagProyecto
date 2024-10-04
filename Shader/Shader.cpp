//
// Created by carmen on 04/10/2024.
//

#include "Shader.h"



namespace PAG {
    Shader::Shader() {

    }

    /**
    * Método para crear, compilar y enlazar el shader program
    */
   void PAG::Shader::crearShader() {
        //Vertex shader
        idVS = glCreateShader ( GL_VERTEX_SHADER );
        if(idVS == 0) {
            success = false;
            throw std::runtime_error ("[PAG::Shader::creaShader]: Error creating vertex shader");
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
            throw std::runtime_error("[PAG::Shader::creaShader]: Error compiling vertex shader\n  " + mensaje);
        }

        //fragment shader
        idFS = glCreateShader ( GL_FRAGMENT_SHADER );
        if(idFS == 0) {
            success = false;
            throw std::runtime_error ("[PAG::Shader::creaShader]: Error creating fragment shader");
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
            throw std::runtime_error("[PAG::Shader::creaShader]: Error compiling fragment shader\n  " + mensaje);
        }

    }

    /**
     * Método que carga de archivo de texto el código fuente del shader
     */
    void PAG::Shader::cargarShader(const std::string& ruta) {

        std::ifstream archivoShader;

        archivoShader.open ( ruta + "-vs.glsl" );
        if ( !archivoShader.is_open () ){
            success = false;
            throw std::runtime_error("[PAG::Shader::cargarShader]: Error en la apertura del archivo de vertex shader");
        }

        std::stringstream streamShader;
        streamShader << archivoShader.rdbuf ();
        codigoVS = streamShader.str ();

        archivoShader.close ();

        //-------------
        streamShader.str(std::string());
        archivoShader.open(ruta + "-fs.glsl");
        if( !archivoShader.is_open() ){
            success = false;
            throw std::runtime_error("[PAG::Shader::cargarShader]: Error en la apertura del archivo de fragment shader");
        }
        streamShader << archivoShader.rdbuf();
        codigoFS = streamShader.str();

        archivoShader.close();

    }

    /**
     * @Brief Funcion que devuelve true si la creacion y cargado de los shaders es correcto
     * @return true si la creacion y cargado de los shaders es correcto
     */
    bool Shader::exito() {
        return success;
    }

    /**
     * @Brief Getter del identificador del vertex shader
     * @return Identificador del vertex shader
     */
    GLuint& Shader::getVertexShader() {
        return idVS;
    }

    /**
     * @Brief Getter del identificador del fragment shader
     * @return Identificador del fragment shader
     */
    GLuint& Shader::getFragmentShader() {
        return idFS;
    }

    /**
     * @Brief Destructor del shader
     */
    Shader::~Shader() {
        if ( idVS != 0 ){
            glDeleteShader ( idVS );
        }
        if ( idFS != 0 ){
            glDeleteShader ( idFS );
        }

    }
}
