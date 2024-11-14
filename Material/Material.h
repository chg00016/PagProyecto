//
// Created by carme on 14/11/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H



#include <glm/vec3.hpp>

namespace PAG {
    class Material {
    private:
        glm::vec3 difusa, ambiente, especular;
        float expBrillo;
    public:
        Material();
        Material(const Material& orig);
        Material(const glm::vec3& difusa, const glm::vec3& ambiente, const glm::vec3& especular, float expBrillo);
        ~Material();

        void setDifusa(const glm::vec3& difusa);
        void setAmbiente(const glm::vec3& ambiente);
        void setEspecular(const glm::vec3& especular);
        void setExpBrillo(float expBrillo);

        const glm::vec3& getDifusa() const;
        const glm::vec3& getAmbiente() const;
        const glm::vec3& getEspecular() const;
        float getExpBrillo() const;
    };
} // PAG

#endif //MATERIAL_H
