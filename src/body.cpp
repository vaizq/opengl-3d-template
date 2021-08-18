#include "body.hpp"


Body::Body(const glm::vec3& pos,
           const glm::vec3& velo,
           const glm::vec3& normal,
           const glm::vec3& scale)
    :m_pos(pos), m_velo(velo), m_normal(normal), m_scale(scale)
{
    m_model = nullptr;
}

Body::~Body()
{
    if(m_model != nullptr)
    {
        delete m_model;
    } 
}


void Body::LoadModel(const std::string fPath)
{
    m_model = new Model(fPath);
}

void Body::Translate(const glm::vec3& dPos)
{
    m_pos += dPos;
}

glm::mat4 Body::GetModelMatrix()
{
    glm::mat4 modelMat = glm::mat4( 1.0f );
    modelMat = glm::translate(modelMat, m_pos);
    modelMat = glm::rotate(modelMat, m_angle, m_normal);
    modelMat = glm::scale(modelMat, m_scale); 

    return modelMat;
}

void Body::Draw(Shader& shader)
{
    m_model->Draw(shader);
}
