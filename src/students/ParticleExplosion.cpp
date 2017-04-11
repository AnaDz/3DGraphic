#include"../../include/students/ParticleExplosion.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include "./../../teachers/Geometries.hpp"

#include"../../include/dynamics/Particle.hpp"

ParticleExplosion::ParticleExplosion(ShaderProgramPtr shaderProgram,  const MaterialPtr& material, ParticlePtr particle):
  ParticleRenderableStudent(shaderProgram, particle, material), m_pBuffer(0), m_cBuffer(0), m_nBuffer(0)
{
   std::vector<glm::vec3> tmp_x, tmp_n;
	 unsigned int strips=5, slices=5;
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

void ParticleExplosion::do_draw()
{
	Material::sendToGPU(m_shaderProgram, getMaterial());
	ParticleRenderableStudent::do_draw();
}
void ParticleExplosion::do_animate(float time){
  ParticleRenderableStudent::do_animate(time);
}

ParticleExplosion::~ParticleExplosion()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
    glcheck(glDeleteBuffers(1, &m_nBuffer));
}
