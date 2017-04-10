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

#include"../../include/dynamics/Particle.hpp"




SnowballRenderable::SnowballRenderable(ShaderProgramPtr shaderProgram,  Viewer* v, ParticlePtr particle)
	: ParticleRenderable(shaderProgram, particle),
//	  m_pBuffer(0), m_cBuffer(0), m_nBuffer(0),
	  viewer(v)
{
	 viewer = v;
//	 buste->setLocalTransform(glm::translate(glm::mat4(1.0), glm::vec3(0, 1 + 0.5, 0)));
//	   HierarchicalRenderable::addChild(boule, buste);
	 //setParentTransform(glm::translate(getParentTransform(), glm::vec3(5, -20, 0)));
	 gauche = false;
	 droite = false;
	 toutDroit = true;

}

void SnowballRenderable::do_animate(float time)
{
}

float scaleFactor = 1;
bool ancien[3]={false, false, false};
void SnowballRenderable::do_draw()
{
	if (m_particle->getPosition().y < 100){
		scaleFactor= 1+m_particle->getPosition().y/100;


	viewer->getCamera().setPosition(glm::vec3(5,-2+ParticleRenderable::m_particle->getPosition().y, 2+ParticleRenderable::m_particle->getPosition().z));

	Material::sendToGPU(m_shaderProgram, Material::Neige());
	setLocalTransform(glm::rotate(glm::mat4(1.0), -(float)(ParticleRenderable::m_particle->getPosition().y), glm::vec3(1,0,0)));
	setLocalTransform(glm::scale(getLocalTransform(), glm::vec3(scaleFactor) ));

	float vitesse = m_particle->getVelocity().y;
	if (gauche){
		m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(-1, 0,0));
		ancien[0]=true;
	}
	if (droite){
		m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(1, 0,0));
		ancien[2]=true;
	}
	if (toutDroit){
		if(ancien[0]){
			m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(-m_particle->getVelocity().x, 0,0));
			ancien[0]=false;
		}
		else if (ancien[2]) {
			m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(-m_particle->getVelocity().x, 0,0));
			ancien[2]=false;
		}
	}
	ParticleRenderable::do_draw();

	}
	else {
		std::cout << "JEU FINI !!\n";
		exit(1);
	}


}

SnowballRenderable::~SnowballRenderable()
{
//    glcheck(glDeleteBuffers(1, &m_pBuffer));
//    glcheck(glDeleteBuffers(1, &m_cBuffer));
//    glcheck(glDeleteBuffers(1, &m_nBuffer));
}

void SnowballRenderable::do_keyPressedEvent(sf::Event& e){
	if (e.key.code == sf::Keyboard::Left) {
	        gauche=true;
	        droite=false;
	        toutDroit=false;
	} else if (e.key.code == sf::Keyboard::Right) {
	        gauche=false;
	        droite=true;
	        toutDroit=false;
	}
}

void SnowballRenderable::do_keyReleasedEvent(sf::Event& e){
	gauche = false;
	droite = false;
	toutDroit = true;

}
