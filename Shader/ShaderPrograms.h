//
// Created by carmen on 04/10/2024.
//

#ifndef SHADERPROGRAMS_H
#define SHADERPROGRAMS_H

#include <glm/fwd.hpp>
#include <glm/matrix.hpp>

#include "Shader.h"

namespace PAG {
    class ShaderPrograms {
    private:
        GLuint idSP = 0; // Identificador del shader program
        Shader* objeto;
        bool success = false;
    public:
        ShaderPrograms();
        void linkShader(Shader& objeto);
        GLuint& getIdSP();
        bool exito();
        void setExito(bool success);

        virtual ~ShaderPrograms();
        //PR7
        void aplicarSubrutina(const std::string &subrutina, GLuint tipo);
        //PR8
        void aplicarUniform(const std::string &uniform, float var);
        void aplicarUniform(const std::string &uniform, const glm::vec3 &vec);
        void aplicarUniform(const std::string &uniform, const glm::mat4 &mat);
    };
}

#endif //SHADERPROGRAMS_H
