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
         const glm::vec3& velo = { 0.0f, 0.0f, 0.0f }, 
         const glm::vec3& normal = { 0.0f, 1.0f, 0.0f },
         const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });    
    ~Body(); 
    void LoadModel(std::string fPath);
    void translate(const glm::vec3& dPos);
    glm::mat4 GetModelMatrix();
    void Draw(Shader& shader);
    // Add simpler function for translation scaling and rotating later
public:
    glm::vec3 m_velo;
    glm::vec3 m_pos;
    glm::vec3 m_normal;
    glm::vec3 m_scale;
    float m_angle = 0;
    
    Model* m_model;
};


#endif
