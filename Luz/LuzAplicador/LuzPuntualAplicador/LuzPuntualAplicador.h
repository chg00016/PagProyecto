//
// Created by carme on 01/12/2024.
//

#ifndef LUZPUNTUALAPLICADOR_H
#define LUZPUNTUALAPLICADOR_H



#include "../LuzAplicador.h"

namespace PAG {
    class LuzPuntualAplicador : public LuzAplicador {
    public:
        LuzPuntualAplicador();
        ~LuzPuntualAplicador();
        void aplicarSubrutina(ShaderPrograms& shaderProgram);
        void aplicarLuz(PropiedadesLuz& properties, const glm::mat4& vision, ShaderPrograms& shaderProgram) override;
    };
}


#endif //LUZPUNTUALAPLICADOR_H
