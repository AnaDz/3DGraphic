#include "../../include/students/TruncSimple.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include <math.h>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

TruncSimple::TruncSimple(ShaderProgramPtr shaderProgram) :
  HierarchicalRenderable(shaderProgram),
  m_pBuffer(0), m_cBuffer(0), m_nBuffer(0)
{
  int prec = 10;
  float pi = atan(1) * 4;
  float step = 2*pi/prec;
  glm::vec4 myColor;
  myColor = glm::vec4(102.0/255.0,51.0/255.0,0,0);

  for(int i = 0; i<prec; i++) {

    m_positions.push_back(glm::vec3(0,0,0));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0));

    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);

    m_normals.push_back(glm::vec3(0.0,0.0,-1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,-1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,-1.0));

    m_positions.push_back(glm::vec3(0,0,2));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));

    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);

    m_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,1.0));

    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));

    m_normals.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0.0));



    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));

    m_normals.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0.0));

    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);


  }

    m_model = glm::mat4(1.0);

    glcheck(glGenBuffers(1, &m_pBuffer));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW));

    glcheck(glGenBuffers(1, &m_nBuffer));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW));

    glcheck(glGenBuffers(1, &m_cBuffer));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW));

}

TruncSimple::~TruncSimple()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
    glcheck(glDeleteBuffers(1, &m_nBuffer));
}

void TruncSimple::do_draw()
{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Get the identifier (location) of the uniform modelMat in the shader program
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    int nitLocation = m_shaderProgram->getUniformLocation("NIT");

    //Send the data corresponding to this identifier on the GPU
    if (modelLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }
    if (nitLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix3fv(nitLocation, 1, GL_FALSE,
            glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(getModelMatrix()))))));
    }

    //Get the identifier of the attribute vPosition in the shader program
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");
    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");

    if (positionLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(positionLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
        glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }
    if (normalLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(normalLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
        glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    if (colorLocation != ShaderProgram::null_location) {
        // Bind texture on texture unit 0

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
    if (normalLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(normalLocation));
    }
    if (colorLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(colorLocation));
    }

  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TruncSimple::do_animate(float time)
{
}
