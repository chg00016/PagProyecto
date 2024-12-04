//
// Created by carme on 01/12/2024.
//

#ifndef LUZAMBIENTEAPLICADOR_H
#define LUZAMBIENTEAPLICADOR_H


#include "../LuzAplicador.h"

namespace PAG {
    class LuzAmbienteAplicador : public LuzAplicador {
    public:
        LuzAmbienteAplicador();
        ~LuzAmbienteAplicador();
        void aplicarSubrutina(ShaderPrograms& shaderProgram);
        void aplicarLuz(PropiedadesLuz& properties, const glm::mat4& vision, ShaderPrograms& shaderProgram) override;
    };
}


#endif //LUZAMBIENTEAPLICADOR_H
