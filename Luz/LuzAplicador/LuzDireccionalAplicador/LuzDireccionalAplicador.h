//
// Created by carme on 01/12/2024.
//

#ifndef LUZDIRECCIONALAPLICADOR_H
#define LUZDIRECCIONALAPLICADOR_H



#include "../LuzAplicador.h"

namespace PAG {
    class LuzDireccionalAplicador : public LuzAplicador {
    public:
        LuzDireccionalAplicador();
        ~LuzDireccionalAplicador();
        void aplicarSubrutina(ShaderPrograms& shaderProgram);
        void aplicarLuz(PropiedadesLuz& properties, const glm::mat4& vision, ShaderPrograms& shaderProgram) override;
    };
}


#endif //LUZDIRECCIONALAPLICADOR_H
