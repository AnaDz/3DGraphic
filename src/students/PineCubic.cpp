#include "../../include/students/PineCubic.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include <math.h>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>

PineCubic::PineCubic(ShaderProgramPtr shaderProgram) :
  HierarchicalRenderable(shaderProgram),
  m_pBuffer(0), m_cBuffer(0)
{
  glm::vec4 myColor = glm::vec4(0,0.5,0,0);
  m_positions.push_back(glm::vec3(1,1,1.5));
  m_positions.push_back(glm::vec3(-1,1,1.5));
  m_positions.push_back(glm::vec3(0,0,5));
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);

  m_positions.push_back(glm::vec3(1,1,1.5));
  m_positions.push_back(glm::vec3(1,-1,1.5));
  m_positions.push_back(glm::vec3(0,0,5));
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);

  m_positions.push_back(glm::vec3(-1,1,1.5));
  m_positions.push_back(glm::vec3(-1,-1,1.5));
  m_positions.push_back(glm::vec3(0,0,5));
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);

  m_positions.push_back(glm::vec3(1,-1,1.5));
  m_positions.push_back(glm::vec3(-1,-1,1.5));
  m_positions.push_back(glm::vec3(0,0,5));
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);
  m_colors.push_back(myColor);
  m_model = glm::mat4(1.0);

  glcheck(glGenBuffers(1, &m_pBuffer));
  glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
  glcheck(glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW));

  glcheck(glGenBuffers(1, &m_cBuffer));
  glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
  glcheck(glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW));

}

PineCubic::~PineCubic()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
}

void PineCubic::do_draw()
{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Get the identifier (location) of the uniform modelMat in the shader program
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
  //  int nitLocation = m_shaderProgram->getUniformLocation("NIT");
//    int texSamplerLocation = m_shaderProgram->getUniformLocation("texSampler");

    //Send the data corresponding to this identifier on the GPU
    if (modelLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }

    //Get the identifier of the attribute vPosition in the shader program
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");

    if (positionLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(positionLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
        glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }
    if (colorLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(colorLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
        glcheck(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }


    //Draw triangles elements
    glcheck(glDrawArrays(GL_TRIANGLES,0, m_positions.size()));

    //Release everything
    if (positionLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(positionLocation));
    }
    if (colorLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(colorLocation));
    }


  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void PineCubic::do_animate(float time)
{
}
