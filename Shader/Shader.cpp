//
// Created by carmen on 04/10/2024.
//

#include "Shader.h"



namespace PAG {
    Shader::Shader() {

    }

    void PAG::Shader::crearShader() {
        //Vertex shader
        idVS = glCreateShader ( GL_VERTEX_SHADER );
        if(idVS == 0) {
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


    GLuint& Shader::getVertexShader() {
        return idVS;
    }


    GLuint& Shader::getFragmentShader() {
        return idFS;
    }


    Shader::~Shader() {
        if ( idVS != 0 ){
            glDeleteShader ( idVS );
        }
        if ( idFS != 0 ){
            glDeleteShader ( idFS );
        }

    }
}
