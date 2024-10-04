//
// Created by carmen on 04/10/2024.
//

#ifndef SHADERPROGRAMS_H
#define SHADERPROGRAMS_H
#include "Shader.h"

namespace PAG {
    class ShaderPrograms {
    private:
        GLuint idSP = 0; // Identificador del shader program
        Shader* objeto;
        bool success = true;
    public:
        ShaderPrograms();
        void linkShader(Shader& objeto);
        GLuint& getIdSP();
        bool exito();

        virtual ~ShaderPrograms();
    };
}

#endif //SHADERPROGRAMS_H
