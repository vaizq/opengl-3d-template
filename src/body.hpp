#ifndef BODY_HPP
#define BODY_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

#include "model.hpp"
#include "shader.hpp"


class Body
{
public:
    Body(const glm::vec3& pos = { 0.0f, 0.0f, 0.0f },
         const glm::vec3& scale = { 1.0f, 1.0f, 1.0f },    
         const glm::vec3& velo = { 0.0f, 0.0f, 0.0f }); 
    ~Body(); 
    void LoadModel(std::string fPath);

    void Translate(const glm::vec3& dPos);
    void Rotate(const float angle, const glm::vec3& normal);
    void Scale(const glm::vec3& scale);

    glm::mat4 GetModelMatrix() const;
    void Draw(Shader& shader);

private:
    glm::vec3 m_velo;
    glm::vec3 m_pos;
    glm::vec3 m_scale;
    glm::mat4 m_rotations;
    
    Model* m_model;
};


#endif
