//
// Created by carme on 01/12/2024.
//

#ifndef LUZ_H
#define LUZ_H



#include <array>

#include "LuzAplicador/LuzDireccionalAplicador/LuzDireccionalAplicador.h"
#include "LuzAplicador/LuzFocalAplicador/LuzFocalAplicador.h"
#include "LuzAplicador/LuzPuntualAplicador/LuzPuntualAplicador.h"
#include "LuzAplicador/LuzAmbienteAplicador/LuzAmbienteAplicador.h"

namespace PAG {
    class Luz {
    private:
        PropiedadesLuz _propiedades;
        glm::mat4 _vision;
        std::array<LuzAplicador*, NUM_LIGHT_APPLICATORS> _aplicadores;
        tipoLuzAplicacion _aplicadorSeleccionado;
    public:
        Luz();
        ~Luz();

        void setDI(const glm::vec3& DI);
        void setAI(const glm::vec3& AI);
        void setSI(const glm::vec3& SI);
        void setPosition(const glm::vec3& pos);
        void setDirection(const glm::vec3& dir);
        void setGamma(float gamma);
        void setAttenuation(float s);
        void setVision(const glm::mat4& vision);

        const glm::vec3& getDI();
        const glm::vec3& getAI();
        const glm::vec3& getSI();
        const glm::vec3& getPostition();
        const glm::vec3& getDirection();
        float getGamma();
        float getAttenuation();
        const glm::mat4& getVision();

        void setLuzAplicador(tipoLuzAplicacion applicatorSelected);
        void aplicarSubrutina(ShaderPrograms& shaderProgram);
        void aplicarLuz(ShaderPrograms& shaderProgram);
    };
}



#endif //LUZ_H
