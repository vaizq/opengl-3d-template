#include "body.hpp"


Body::Body(const glm::vec3& pos,
           const glm::vec3& scale,
           const glm::vec3& velo)
    :m_pos(pos), m_velo(velo), m_scale(scale)
{
    m_model = nullptr;
    m_rotations = glm::mat4(1.0f);
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

void Body::Rotate(const float angle, const glm::vec3& normal)
{
    m_rotations = glm::rotate(m_rotations, angle, normal);
}

void Body::Scale(const glm::vec3& scale)
{
    m_scale.x *= scale.x;
    m_scale.y *= scale.y;
    m_scale.z *= scale.z;
}


glm::mat4 Body::GetModelMatrix() const
{
    glm::mat4 modelMat = glm::mat4( 1.0f );
    modelMat = glm::translate(modelMat, m_pos);
    modelMat *= m_rotations;
    modelMat = glm::scale(modelMat, m_scale); 

    return modelMat;
}

void Body::Draw(Shader& shader)
{
    m_model->Draw(shader);
}
