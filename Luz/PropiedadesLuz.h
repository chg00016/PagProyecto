//
// Created by carme on 01/12/2024.
//

#ifndef PROPIEDADESLUZ_H
#define PROPIEDADESLUZ_H



#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>

namespace PAG {
    struct PropiedadesLuz {
        glm::vec3 _ID;
        glm::vec3 _IA;
        glm::vec3 _IS;
        glm::vec3 _p;
        glm::vec3 _d;
        float _gamma;
        float _s;
    };
}


#endif //PROPIEDADESLUZ_H
