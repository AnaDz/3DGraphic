/*
 * Snowball.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: mariono
 */


#include"../../include/students/SnowballRenderable.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include "./../../teachers/Geometries.hpp"

#include"../../include/dynamics/Particle.hpp" // attention, surement doit extend ParticleRenderable. A voir
SnowballRenderable::SnowballRenderable(ShaderProgramPtr shaderProgram,  const MaterialPtr& material, Viewer* v, ParticlePtr particle)
	: ParticleRenderable(shaderProgram, particle), Materiable(material),
	  m_pBuffer(0), m_cBuffer(0), m_nBuffer(0),
	  viewer(v)
{
	 viewer = v;
	 std::vector<glm::vec3> tmp_x, tmp_n;
	 unsigned int strips=20, slices=20;
	 teachers::getUnitSphere(tmp_x, tmp_n, strips, slices);
	 m_positions.insert(m_positions.end(), tmp_x.begin(), tmp_x.end());
	 m_normals.insert(m_normals.end(), tmp_n.begin(), tmp_n.end());
	 m_colors.resize(m_positions.size(), randomColor());


	 //Create buffers
	 glGenBuffers(1, &m_pBuffer); //vertices
	 glGenBuffers(1, &m_cBuffer); //colors
	 glGenBuffers(1, &m_nBuffer); //normals

	 //Activate buffer and send data to the graphics card
	 glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
	 glcheck(glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW));
	 glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
	 glcheck(glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW));
	 glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
	 glcheck(glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW));
}

void SnowballRenderable::do_animate(float time)
{
	//ça la fait rouler mais du coup ça fait pas prendre en compte les collisions :) mais c'est déjà ça !
	//viewer->getCamera().setPosition(glm::vec3(5,-2+time,2));
//	setParentTransform(glm::translate(glm::mat4(1.0), glm::vec3(2*time,0,0)));
//	setLocalTransform(glm::rotate(glm::mat4(1.0), (float)(2*time*3.14), glm::vec3(0,1,0)));
}

void SnowballRenderable::do_draw()
{
	Material::sendToGPU(m_shaderProgram, getMaterial());
	ParticleRenderable::do_draw();
//	//Location
//	    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
//	    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
//	    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");
//	    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
//
//	    Material::sendToGPU(m_shaderProgram, getMaterial());
//	    //Send data to GPU
//	    if(modelLocation != ShaderProgram::null_location)
//	    {
//	        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
//	    }
//
//	    if(positionLocation != ShaderProgram::null_location)
//	    {
//	        //Activate location
//	        glcheck(glEnableVertexAttribArray(positionLocation));
//	        //Bind buffer
//	        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
//	        //Specify internal format
//	        glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
//	    }
//
//	    if(colorLocation != ShaderProgram::null_location)
//	    {
//	        glcheck(glEnableVertexAttribArray(colorLocation));
//	        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
//	        glcheck(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
//	    }
//
//	    if(normalLocation != ShaderProgram::null_location)
//	    {
//	        glcheck(glEnableVertexAttribArray(normalLocation));
//	        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
//	        glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
//	    }
//
//	    //Draw triangles elements
//	    glcheck(glDrawArrays(GL_TRIANGLES,0, m_positions.size()));
//
//	    if(positionLocation != ShaderProgram::null_location)
//	    {
//	        glcheck(glDisableVertexAttribArray(positionLocation));
//	    }
//	    if(colorLocation != ShaderProgram::null_location)
//	    {
//	        glcheck(glDisableVertexAttribArray(colorLocation));
//	    }
//	    if(normalLocation != ShaderProgram::null_location)
//	    {
//	        glcheck(glDisableVertexAttribArray(normalLocation));
//	    }
}

SnowballRenderable::~SnowballRenderable()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
    glcheck(glDeleteBuffers(1, &m_nBuffer));
}


