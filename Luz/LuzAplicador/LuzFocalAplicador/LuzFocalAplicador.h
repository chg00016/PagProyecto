//
// Created by carme on 01/12/2024.
//

#ifndef LUZFOCALAPLICADOR_H
#define LUZFOCALAPLICADOR_H



#include "../LuzAplicador.h"

namespace PAG {
    class LuzFocalAplicador : public LuzAplicador {
    public:
        LuzFocalAplicador();
        ~LuzFocalAplicador();
        void aplicarSubrutina(ShaderPrograms& shaderProgram);
        void aplicarLuz(PropiedadesLuz& properties, const glm::mat4& vision, ShaderPrograms& shaderProgram) override;
    };
}



#endif //LUZFOCALAPLICADOR_H
