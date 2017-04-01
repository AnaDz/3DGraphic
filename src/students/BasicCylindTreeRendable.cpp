#include "../../include/students/BasicCylindTreeRenderable.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include <math.h>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "./../../teachers/Geometries.hpp"
#include <SFML/Graphics/Image.hpp>
#include <iostream>

BasicCylindTreeRenderable::BasicCylindTreeRenderable(ShaderProgramPtr shaderProgram) :
  HierarchicalRenderable(shaderProgram),
  m_pBuffer(0), m_cBuffer(0)
{
  int prec = 100;
  float pi = atan(1) * 4;
  float step = 2*pi/prec;
  glm::vec4 myColor;
  myColor = glm::vec4(102.0/255.0,51.0/255.0,0,0);
  glm::vec4 green = glm::vec4(0,0.5,0,0);
  for(int i = 0; i<prec; i++) {

    m_positions.push_back(glm::vec3(0,0,0));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0));

    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);

    m_positions.push_back(glm::vec3(0,0,2));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));

    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);

    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));

    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));

    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);
    m_colors.push_back(myColor);

    m_positions.push_back(glm::vec3(cos(i*step)*1.5,sin(i*step)*1.5,1.5));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*1.5,sin((i+1)*step)*1.5,1.5));
    m_positions.push_back(glm::vec3(0,0,5));
    m_colors.push_back(green);
    m_colors.push_back(green);
    m_colors.push_back(green);



  }
    m_model = glm::mat4(1.0);

    glGenBuffers(1, &m_pBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_cBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW);
}

BasicCylindTreeRenderable::~BasicCylindTreeRenderable()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
}

void BasicCylindTreeRenderable::do_draw()
{
    // Here you must:
    // 1. get the model matrix and send it to the shader (as uniform)
    // 2. for each attribute: retrieve its location on the shader,
    //    activate it, bind a buffer, then specify internal format
    // 3. draw the triangles
    // 4. unbind everything

  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //Get the identifier (location) of the uniform modelMat in the shader program
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    //Send the data corresponding to this identifier on the GPU
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

    //Get the identifier of the attribute vPosition in the shader program
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    //Activate the attribute array at this location
    // activation du buffer position puis bind
    glEnableVertexAttribArray(positionLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    //Specify the location and the format of the vertex position attribute
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //Draw the triangles



    //Get the fucking color !
    int color = m_shaderProgram->getAttributeLocation("vColor");
    // activation du buffer color
    if(color != ShaderProgram::null_location) {
      glEnableVertexAttribArray(color);
      //Bind the position buffer on the GL_ARRAY_BUFFER target
      glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
      glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }
    glDrawArrays(GL_TRIANGLES,0, m_positions.size());
    //Release the vertex attribute array
    glDisableVertexAttribArray(positionLocation);
    //Release the vertex attribute array
    glDisableVertexAttribArray(color);

  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BasicCylindTreeRenderable::do_animate(float time)
{
}
