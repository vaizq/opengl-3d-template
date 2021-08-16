#ifndef MESH_HPP
#define MESH_HPP

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords; 
    glm::vec3 tangent;
    glm::vec3 biTangent;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader);
private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  

#endif
