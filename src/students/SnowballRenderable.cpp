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
#include "../../include/students/GroundRenderable.hpp"



SnowballRenderable::SnowballRenderable(ShaderProgramPtr shaderProgram,  Viewer* v, ParticlePtr particle, std::shared_ptr<SphereRenderable> sky)
	: ParticleRenderableStudent(shaderProgram, particle),
	  viewer(v)
{
	 viewer = v;
	 gauche = false;
	 droite = false;
	 toutDroit = true;
	 skybox = sky;

	 //initialisation du sol
	 int nx = 6;
	 int ny = 75;
	 int n = 10;
	 float angle = -(float)3.14/12;

	 glm::mat4 parentTransformation, localTransformation;
	 //groundR = malloc(sizeof(GroundRenderablePtr) * nx * ny);

	 ShaderProgramPtr flatShader= std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
			 "../shaders/flatFragment.glsl");
	 viewer->addShaderProgram(flatShader);

	 for (int x=0; x<nx; x++){
		 for (int y=0; y<ny; y++){
			 groundR[x][y] = std::make_shared<GroundRenderable>(flatShader,x,y,n, viewer);
			 parentTransformation=glm::translate(glm::rotate(glm::mat4(1.0), angle, glm::vec3(1,0,0)), glm::vec3(x,y,0));
			 groundR[x][y]->setParentTransform(parentTransformation);
			 localTransformation = glm::mat4(1.0);
			 groundR[x][y]->setLocalTransform(localTransformation);
			 viewer->addRenderable(groundR[x][y]);

		 }
	 }
}

void SnowballRenderable::do_animate(float time)
{
}

float scaleFactor = 1;
bool ancien[3]={false, false, false};
int k =1;
double prevY = 0;
double prevZ = 0;
void SnowballRenderable::do_draw()
{
	if (m_particle->getPosition().y < 100){
		scaleFactor= 1+m_particle->getPosition().y/100;
		m_particle->setRadius(scaleFactor/2);
	}

	viewer->getCamera().setMouseBehavior(Camera::SPACESHIP_BEHAVIOR);
	viewer->getCamera().setPosition(glm::vec3(3,-2+ParticleRenderableStudent::m_particle->getPosition().y, 2+ParticleRenderableStudent::m_particle->getPosition().z));
	glm::mat4 translation_skybox = glm::translate(glm::mat4(1.0), glm::vec3(3,prevY,prevZ));
	skybox->setParentTransform(translation_skybox);
	prevY = -2+ParticleRenderableStudent::m_particle->getPosition().y;
	prevZ = 2+ParticleRenderableStudent::m_particle->getPosition().z;

	Material::sendToGPU(m_shaderProgram, Material::Neige());
	setLocalTransform(glm::rotate(glm::mat4(1.0), -(float)(ParticleRenderableStudent::m_particle->getPosition().y), glm::vec3(1,0,0)));

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

	if (m_particle->getVelocity().y > 50 ){
		glm::vec3 tmp = m_particle->getVelocity();
		tmp.y = 50;
		m_particle->setVelocity(tmp);
		//printf("vitesse.x =%f, vitesse.y =%f, vitesse.z =%f \n",m_particle->getVelocity().x, m_particle->getVelocity().y, m_particle->getVelocity().z);
	}
	ParticleRenderableStudent::do_draw();



	if (m_particle->getPosition().y >= k*25){
		// m_particle->setPosition(glm::vec3(m_particle->getPosition().x, 0, 0));
		int nx = 6;
		int ny = 75;
		int n = 10;
		float angle = -(float)3.14/12;

		glm::mat4 parentTransformation, localTransformation;
		//GroundRenderablePtr groundR ;

		GroundRenderablePtr tmp;
			for (int x=0; x<nx; x++){
				for (int y=0; y<25; y++){
					tmp = groundR[x][y];
					//printf("x=%i, y=%i \n",x,y);
					parentTransformation=glm::translate(glm::rotate(glm::mat4(1.0), angle, glm::vec3(1,0,0)), glm::vec3(x,(k+2)*25+y,0));
					tmp->setParentTransform(parentTransformation);
					localTransformation = glm::mat4(1.0);
					tmp->setLocalTransform(localTransformation);

					groundR[x][y]= groundR[x][y+25];
					groundR[x][y+25]=groundR[x][y+50];
					groundR[x][y+50]=tmp;

				}
			}
			//printf("segfault avant \n");

		k++;
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
