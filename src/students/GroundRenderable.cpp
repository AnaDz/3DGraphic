/*
 * GroundRenderable.cpp
 *
 *  Created on: Mar 30, 2017
 *      Author: mariono
 */

#include"../../include/students/GroundRenderable.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include "../../include/students/PerlinNoise.hpp"

GroundRenderable::GroundRenderable(ShaderProgramPtr shaderProgram, int x, int y, int n)
	: HierarchicalRenderable(shaderProgram), m_pBuffer(0), m_cBuffer(0), m_nBuffer(0), m_iBuffer(0)
{

	for (int i=0; i<=n; i++){
		for (int j=0; j<=n; j++){
			m_positions.push_back(glm::vec3((float)i/n,(float)j/n, 0.3*Get2DPerlinNoiseValue((i+x*n),(j+y*n), 10.0)));
		}
	}

	for (int i=0; i<=n; i++){
		for (int j=0; j<=n; j++){
			float gris = (1+Get2DPerlinNoiseValue(x*(n+1)+i, y*(n+1)+j, 10.0))*0.6+0.4;
			m_colors.push_back(glm::vec4(gris, gris, gris, 1));
		}
	}

	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			m_indices.push_back(glm::ivec3(i*(n+1)+j, i*(n+1)+(j+1), (i+1)*(n+1)+j));
			m_indices.push_back(glm::ivec3((i+1)*(n+1)+j, i*(n+1)+(j+1), (i+1)*(n+1)+(j+1)));
		}
	}

  glGenBuffers(1, &m_pBuffer); //vertices
  glGenBuffers(1, &m_cBuffer); //colors
  glGenBuffers(1, &m_iBuffer); //indices

  glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
  glcheck(glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW));
  glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
  glcheck(glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW));
  glcheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer));
  glcheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(glm::ivec3), m_indices.data(), GL_STATIC_DRAW));
}


void GroundRenderable::do_animate(float time)
{
}

void GroundRenderable::do_draw()
{
    //Location
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");

    //Send data to GPU
    if(modelLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }

    if(positionLocation != ShaderProgram::null_location) {
        //Activate location
        glcheck(glEnableVertexAttribArray(positionLocation));
        //Bind buffer
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
        //Specify internal format
        glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    if(colorLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(colorLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
        glcheck(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    if(normalLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(normalLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
        glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    //Draw triangles elements
    glcheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer));
    glcheck(glDrawElements(GL_TRIANGLES, m_indices.size()*3, GL_UNSIGNED_INT, (void*)0));

    if(positionLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(positionLocation));
    }
    if(colorLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(colorLocation));
    }
    if(normalLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(normalLocation));
    }
}

GroundRenderable::~GroundRenderable()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
    glcheck(glDeleteBuffers(1, &m_nBuffer));
    glcheck(glDeleteBuffers(1, &m_iBuffer));
}
