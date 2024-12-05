//
// Created by carme on 01/12/2024.
//

#ifndef LUZAPLICADOR_H
#define LUZAPLICADOR_H


#define NUM_LIGHT_APPLICATORS 4

#include "../PropiedadesLuz.h"
#include "../../Shader/ShaderPrograms.h"

namespace PAG {
    enum tipoLuzAplicacion {
        _ninguna = -1,
        _luzPuntual = 0,
        _luzFocal,
        _luzDireccional,
        _luzAmbiente
    };

    class LuzAplicador {
    public:
        LuzAplicador() = default;
        virtual ~LuzAplicador() = default;
        virtual void aplicarSubrutina(ShaderPrograms& shaderProgram) = 0;
        virtual void aplicarLuz(PropiedadesLuz& properties, const glm::mat4& vision, ShaderPrograms& shaderProgram) = 0;
    };
}


#endif //LUZAPLICADOR_H
