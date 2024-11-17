//
// Created by carme on 04/11/2024.
//

#ifndef MODELO_H
#define MODELO_H

#include <string>
#include <ostream>
#include <vector>

#include <glad/glad.h>
#include <glm/vec3.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Material/Material.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>

namespace PAG {

    struct Vertice {
        Vertice(glm::vec3 posicion = {0,0,0}, glm::vec3 vNormal= {0,0,0});
        Vertice(aiVector3t<ai_real> posicion, aiVector3t<ai_real> normal);
        glm::vec3 posicion;
        glm::vec3 vNormal;
    };

    class Modelo {
    private:
        GLuint idVAO = 0; // Identificador del vertex array object
        GLuint idVBO = 0; // Identificador del vertex buffer object
        GLuint idIBO = 0; // Identificador del index buffer object
        std::vector<Vertice> vertices;
        std::vector<GLuint> indices;
        std::string fichero;
        glm::mat4 mTransformacion;

        Material* material = nullptr;

        void crearModelo(std::string &ruta);
        void procesarNodo(aiNode *nodo, const aiScene *scene);
        void procesarMalla(aiMesh *malla);
    public:
        Modelo(std::string ruta);
        Modelo (const Modelo& orig);
        void rotar(const GLfloat &grados,const glm::vec3 &vTransformacion);
        void escalar(const glm::vec3 &vTransformacion);
        void trasladar(const glm::vec3 &vTransformacion);
        void dibujarModelo();

        const std::string &getFichero() const;
        const glm::mat4 &getMatrizTransformacion() const;
        void destruirModelo();

        virtual ~Modelo();

        //PR7
        void setMaterial(Material* material);
        Material* getMaterial() const;
    };
}


#endif //MODELO_H
