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
            std::array<LuzAplicador*, 4> _aplicadores;
            tipoLuzAplicacion _aplicadorSeleccionado;
        public:
            Luz();
            ~Luz();
            const glm::vec3& getID();
            const glm::vec3& getIA();
            const glm::vec3& getIS();
            const glm::vec3& getPosicion();
            const glm::vec3& getDireccion();
            float getGamma();
            float getAtenuacion();
            const glm::mat4& getVision();
            void setID(const glm::vec3& ID);
            void setIA(const glm::vec3& IA);
            void setIS(const glm::vec3& IS);
            void setPosicion(const glm::vec3& pos);
            void setDireccion(const glm::vec3& dir);
            void setGamma(float gamma);
            void setAtenuacion(float s);
            void setVision(const glm::mat4& vision);

            void setLuzAplicador(tipoLuzAplicacion applicatorSelected);
            void aplicarSubrutina(ShaderPrograms& shaderProgram);
            void aplicarLuz(ShaderPrograms& shaderProgram);
        };
}



#endif //LUZ_H
