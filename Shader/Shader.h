//
// Created by carmen on 04/10/2024.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glad/glad.h>
#include <stdexcept>

namespace PAG {
    class Shader {
    private:
        GLuint idVS = 0; // Identificador del vertex shader
        GLuint idFS = 0; // Identificador del fragment shader
        std::string codigoVS = "";
        std::string codigoFS = "";
    public:
        Shader();
        void crearShader();
        GLuint& getVertexShader();
        GLuint& getFragmentShader();


        virtual ~Shader();
    };
}


#endif //SHADER_H
