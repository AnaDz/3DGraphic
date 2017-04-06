#include "../../include/students/PineCylin.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include <math.h>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>

PineCylin::PineCylin(ShaderProgramPtr shaderProgram) :
  HierarchicalRenderable(shaderProgram),
  m_pBuffer(0), m_cBuffer(0)
{
  int prec = 10;
  float pi = atan(1) * 4;
  float step = 2*pi/prec;
  glm::vec4 green = glm::vec4(0,0.5,0,0);
  for(int i = 0; i<prec; i++) {
    m_positions.push_back(glm::vec3(cos(i*step)*1.5,sin(i*step)*1.5,1.5));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*1.5,sin((i+1)*step)*1.5,1.5));
    m_positions.push_back(glm::vec3(0,0,5));
    m_colors.push_back(green);
    m_colors.push_back(green);
    m_colors.push_back(green);
  }
}

PineCylin::~PineCylin()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
}

void PineCylin::do_draw()
{
  std::cout << "hey" << std::endl;
  //Get the identifier (location) of the uniform modelMat in the shader program
  int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
  //  int nitLocation = m_shaderProgram->getUniformLocation("NIT");
  //    int texSamplerLocation = m_shaderProgram->getUniformLocation("texSampler");

  //Send the data corresponding to this identifier on the GPU
  if (modelLocation != ShaderProgram::null_location) {
      glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
  }

std::cout << "oh.." << std::endl;
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

  std::cout << "OK.." << std::endl;
  //Release everything
  if (positionLocation != ShaderProgram::null_location) {
      glcheck(glDisableVertexAttribArray(positionLocation));
  }
  if (colorLocation != ShaderProgram::null_location) {
      glcheck(glDisableVertexAttribArray(colorLocation));
  }


  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  std::cout << "draw" << std::endl;
  }

void PineCylin::do_animate(float time)
{
}
