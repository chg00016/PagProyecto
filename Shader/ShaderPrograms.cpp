//
// Created by carmen on 04/10/2024.
//

#include "ShaderPrograms.h"
namespace PAG {

    ShaderPrograms::ShaderPrograms() {

    }

    void ShaderPrograms::linkShader(Shader& objeto) {
        success = true;
        if(!objeto.exito()) {
            success = false;
            return;
        }

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

    void ShaderPrograms::setExito(bool success) {
        this->success = success;
    }

    ShaderPrograms::~ShaderPrograms() {
        if ( idSP != 0 ){
            glDeleteProgram ( idSP );
        }
        objeto = nullptr;
    }
    //PR7
    void ShaderPrograms::aplicarSubrutina(const std::string &subrutina, GLuint tipo) {
         GLuint aux = glGetSubroutineIndex (idSP, tipo , subrutina.c_str());
         if (aux == GL_INVALID_INDEX)
             throw std::invalid_argument("ShaderPrograms::aplicarSubrutina: No existe la subrutina " + subrutina);
         glUniformSubroutinesuiv ( tipo, 1, &aux );
    }

    //PR8
    void ShaderPrograms::aplicarUniform(const std::string &uniform, float var) {
        GLint aux = glGetUniformLocation ( idSP, uniform.c_str() );
        if (aux == GL_INVALID_INDEX)
            throw std::invalid_argument("ShaderPrograms::aplicarUniform: No existe la variable " + uniform);;
        glUniform1f(aux, var);
    }

    void ShaderPrograms::aplicarUniform(const std::string &uniform, const glm::vec3 &vec) {
        GLint aux = glGetUniformLocation ( idSP, uniform.c_str() );
        if (aux == GL_INVALID_INDEX)
            throw std::invalid_argument("ShaderPrograms::aplicarUniform: No existe el vector " + uniform);;
        glUniform3f(aux, vec.x, vec.y, vec.z);
    }

    void ShaderPrograms::aplicarUniform(const std::string &uniform, const glm::mat4 &mat) {
        GLint aux = glGetUniformLocation ( idSP, uniform.c_str() );
        if (aux == GL_INVALID_INDEX)
            throw std::invalid_argument("ShaderPrograms::aplicarUniform: No existe la matriz " + uniform);;
        glUniformMatrix4fv(aux, 1, GL_FALSE, &mat[0][0]);
    }
}