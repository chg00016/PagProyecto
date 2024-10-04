//
// Created by carmen on 04/10/2024.
//

#include "ShaderPrograms.h"
namespace PAG {

    ShaderPrograms::ShaderPrograms() {

    }

    void ShaderPrograms::linkShader(Shader& objeto) {
        if(!objeto.exito())
            return;

        idSP = glCreateProgram ();
        if(idSP == 0) {
            success = false;
            throw std::runtime_error("[PAG::ShaderPrograms::linkShader]: Error creating the shader program");
        }
        glAttachShader ( idSP, objeto.getVertexShader() );
        glAttachShader ( idSP, objeto.getFragmentShader());
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
            throw std::runtime_error("[PAG::ShaderPrograms::linkShader]: Error linking the program");
        }

    }


    GLuint &ShaderPrograms::getIdSP() {
        return idSP;
    }

    bool ShaderPrograms::exito() {
        return success;
    }

    ShaderPrograms::~ShaderPrograms() {
        if ( idSP != 0 ){
            glDeleteProgram ( idSP );
        }
        objeto = nullptr;
    }

}