//
// Created by carme on 04/11/2024.
//

#include "Modelo.h"

namespace PAG {
    Vertice::Vertice(aiVector3t<ai_real> posicion, aiVector3t<ai_real> normal) {
       this->posicion.x = posicion.x;
       this->posicion.y = posicion.y;
       this->posicion.z = posicion.z;

       this->vNormal.x = normal.x;
       this->vNormal.y = normal.y;
       this->vNormal.z = normal.z;
    }

    Vertice::Vertice(glm::vec3 posicion, glm::vec3 vNormal) {
        this->posicion = posicion;
        this->vNormal = vNormal;

    }

    Modelo::Modelo(std::string ruta): fichero(ruta) {
        mTransformacion = glm::identity<glm::mat4>();
        crearModelo(ruta);
    }

    Modelo::Modelo(const Modelo &orig) {
        this->fichero = orig.fichero;
        this->idVAO = orig.idVAO;
        this->idVBO = orig.idVBO ;
        this->idIBO = orig.idIBO;
        this->vertices = orig.vertices;
        this->indices = orig.indices;
        this->mTransformacion = orig.mTransformacion;
        this->material = orig.material;
    }

    void Modelo::crearModelo(std::string &ruta) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(ruta, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::runtime_error (std::string("ASSIMP::crearModelo()")+ importer.GetErrorString() );
        }

        procesarNodo(scene->mRootNode, scene);

        //VAO
        glGenVertexArrays ( 1, &idVAO );
        glBindVertexArray ( idVAO );
        //VBO
        glGenBuffers ( 1, &idVBO );
        glBindBuffer(GL_ARRAY_BUFFER, idVBO );

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertice), vertices.data(), GL_STATIC_DRAW);

        //vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), nullptr);
        glEnableVertexAttribArray(0);
        //colores
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (const void *) offsetof(Vertice, vColor));
        glEnableVertexAttribArray(1);
        //normales
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (const void *) offsetof(Vertice, vNormal));
        glEnableVertexAttribArray(2);

        //IBO
        glGenBuffers ( 1, &idIBO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW );
    }

    void Modelo::procesarNodo(aiNode *nodo, const aiScene *scene) {
        unsigned int i;
        for (i = 0; i < nodo->mNumMeshes; ++i) {
            aiMesh *malla = scene->mMeshes[nodo->mMeshes[i]];
            procesarMalla(malla);
        }

        for (i = 0; i < nodo->mNumChildren; ++i) {
            procesarNodo(nodo->mChildren[i], scene);
        }
    }

    void Modelo::procesarMalla(aiMesh *malla) {
        if (!malla->mVertices)
            throw std::invalid_argument( "Modelo::procesarMalla(aiMesh *malla): Los vertices del modelo no se han procesado correctamente.");

        vertices.clear();
        indices.clear();

        for (unsigned int i = 0; i < malla->mNumVertices; i++) {

            Vertice vertice;

            vertice.posicion.x = malla->mVertices[i].x;
            vertice.posicion.y = malla->mVertices[i].y;
            vertice.posicion.z = malla->mVertices[i].z;

            vertice.vNormal.x = malla->mNormals[i].x;
            vertice.vNormal.y = malla->mNormals[i].y;
            vertice.vNormal.z = malla->mNormals[i].z;

            vertices.emplace_back(vertice);
        }

        if (!malla->HasFaces())
            throw std::invalid_argument( "Modelo::procesarMalla(aiMesh *malla): Los vertices del modelo no se relacionan en ninguna cara.");

        unsigned int j;
        for (unsigned int i = 0; i < malla->mNumFaces; ++i) {
            aiFace cara = malla->mFaces[i];
            for (j = 0; j < cara.mNumIndices; ++j){
                indices.emplace_back(cara.mIndices[j]);
            }
        }
    }

    void Modelo::rotar(const GLfloat &grados,const glm::vec3 &vTransformacion) {
        this->mTransformacion *= glm::rotate(grados, vTransformacion);
    }

    void Modelo::escalar(const glm::vec3 &vTransformacion) {
        this->mTransformacion  *= glm::scale(vTransformacion);
    }

    void Modelo::trasladar(const glm::vec3 &vTransformacion) {
        this->mTransformacion =  glm::translate(vTransformacion) * this->mTransformacion;
    }

    void Modelo::dibujarModelo() {
        glBindVertexArray(idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    }

    const std::string & Modelo::getFichero() const {
        return this->fichero;
    }

    const glm::mat4& Modelo::getMatrizTransformacion() const {
        return this->mTransformacion;
    }
    void Modelo::destruirModelo() {
        if ( idVBO != 0 )
            glDeleteBuffers (1, &idVBO );
        if ( idIBO != 0 )
            glDeleteBuffers ( 1, &idIBO );
        if ( idVAO != 0 )
            glDeleteVertexArrays ( 1, &idVAO );
    }


    Modelo::~Modelo() {
        this->material = nullptr;
    }

    //PR7

    void Modelo::setMaterial(Material* material) {
        this->material = material;
    }

    Material* Modelo::getMaterial() const {
        return this->material;
    }
}
