//
// Created by carme on 14/11/2024.
//

#include "Material.h"
namespace PAG {
    Material::Material():
        difusa(), ambiente(), especular(), expBrillo(0.0f) {

    }

    Material::Material(const Material& orig):
        difusa(orig.difusa), ambiente(orig.ambiente),
        especular(orig.especular), expBrillo(orig.expBrillo) {

    }

    Material::Material(const glm::vec3& difusa, const glm::vec3& ambiente, const glm::vec3& especular, float expBrillo):
            difusa(difusa), ambiente(ambiente),
            especular(especular), expBrillo(expBrillo) {

    }

    Material::~Material() {

    }

    void Material::setDifusa(const glm::vec3& difusa) { this->difusa = difusa; }
    void Material::setAmbiente(const glm::vec3& ambiente) { this->ambiente = ambiente; }
    void Material::setEspecular(const glm::vec3& especular) { this->especular = especular; }
    void Material::setExpBrillo(float expBrillo) { this->expBrillo = expBrillo; }

    const glm::vec3& Material::getDifusa() const { return difusa; }
    const glm::vec3& Material::getAmbiente() const { return ambiente; }
    const glm::vec3& Material::getEspecular() const { return especular; }
    float Material::getExpBrillo() const { return expBrillo; }
}