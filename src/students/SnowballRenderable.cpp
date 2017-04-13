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
#include "../../include/dynamics/DynamicSystem.hpp"
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

int nx = 12;
int ny = 120;
int n = 10;
float angle = -(float)3.14/12;
int terrain = 0; // Le terrain que la boule vient de parcourir

SnowballRenderable::SnowballRenderable(ShaderProgramPtr flatShader,  ShaderProgramPtr phongShader, ShaderProgramPtr texShader, Viewer* v, ParticlePtr particle, std::shared_ptr<SphereRenderable> sky, DynamicSystemPtr system)
	: ParticleRenderableStudent(texShader, particle)
{

	// Initialisation du générateur aléatoire
		 srand(time(NULL));

	 // Initialisation des attributs
	 viewer = v;
	 flatShader=flatShader;
	 texShader=texShader;
	 phongShader=phongShader;
	 system=system;
	 gauche = false;
	 droite = false;
	 toutDroit = true;
	 skybox = sky;

	 // Initialisation du sol
	 groundR.resize(nx, std::vector<GroundRenderablePtr>(ny));

	 glm::mat4 parentTransformation, localTransformation;

	 // Création du terrain
	 for (int x=0; x<nx; x++){
		 for (int y=0; y<ny; y++){
			 groundR[x][y] = std::make_shared<GroundRenderable>(flatShader,x,y,n);
			 parentTransformation=glm::translate(glm::rotate(glm::mat4(1.0), angle, glm::vec3(1,0,0)), glm::vec3(x,y,0));
			 groundR[x][y]->setParentTransform(parentTransformation);
			 localTransformation = glm::mat4(1.0);
			 groundR[x][y]->setLocalTransform(localTransformation);
			 viewer->addRenderable(groundR[x][y]);
		 }
	 }

	 // "Fréquence" d'apparition des objets
   int nb_bonhommes = 6;
	 int nb_maisons = 6;
	 int nb_arbres = 6;
	 bonshommes.resize(nb_bonhommes);
	 meshes.resize(nb_maisons);
	 arbres.resize(nb_arbres);

	 // Création des bonshommes de neige
	 for (int i = 0; i < nb_bonhommes; i++) {
		 bonshommes[i] = std::make_shared<BonhommeDeNeige>(phongShader, texShader);
		 HierarchicalRenderable::addChild(bonshommes[i], bonshommes[i]->base);
		 viewer->addRenderable(bonshommes[i]);
 	 }

	 // Création des arbres
	 std::string filename = "../textures/bark.jpg";
	 std::string filename2 = "../textures/needle.jpg";
	 glm::vec3 px,pv;
	 float pm, pr;
	 px = glm::vec3(0,0,0.5);
	 pv = glm::vec3(0,0,0);
	 pr = 0.5;
	 pm = 1.0;
	 for (int i = 0; i < nb_arbres; i++) {
		 arbres[i] = std::make_shared<Tree>(texShader, filename, filename2);
		 ParticlePtr particle_arbre = std::make_shared<Particle>(px, pv, pm, pr);
		 arbres[i]->setParentTransform(glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(1,-5*cos(angle),-5*sin(angle))), glm::vec3(0.25,0.25,0.25)));
		 particle_arbre->setSpecialAnimation(true);
		 particle_arbre->setLink(arbres[i]);
		 system->addParticle(particle_arbre);
		 HierarchicalRenderable::addChild(arbres[i], arbres[i]->tronc);
		 viewer->addRenderable(arbres[i]);
		 //Explosion(system, systemRenderable, phongShader);
 	 }

	 // Création des meshes : la petite maison dans la prairie enneigée version Camping Paradis
	 glm::mat4 trans, scaleM;
	 for (int i = 0; i < nb_maisons; i++) {
	 	 meshes[i]=std::make_shared<TexturedMeshRenderable>(
		 		texShader, "../meshes/Maison.obj", "../textures/Cottage Texture.jpg");
		 trans = glm::translate(glm::mat4(1.0), glm::vec3(1.0,-5*cos(angle),-5*sin(angle)));
		 scaleM = glm::scale(trans, glm::vec3(0.02,0.02,0.02));
		 meshes[i]->setParentTransform(scaleM);
		 meshes[i]->setMaterial(Material::Maison());
		 glm::mat4 rotationM = glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0)), (float)(M_PI/2.0), glm::vec3(0,1,0)), angle, glm::vec3(0,0,1));
		 meshes[i]->setLocalTransform(rotationM);
		 viewer->addRenderable(meshes[i]);
   }



}

void SnowballRenderable::do_animate(float time)
{
}

float scaleFactor = 1;
bool ancien[3]={false, false, false};
int k=1;
double prevY = 0;
double prevZ = 0;

void SnowballRenderable::do_draw()
{
	// Agrandissement progressif de la boule
	if (m_particle->getPosition().y < 100){
		scaleFactor= 0.4+m_particle->getPosition().y/200;
		m_particle->setRadius(scaleFactor/2);
	}

	// Positionnement de la caméra et de la skybox pour suivre le mouvement de la boule de neige
	viewer->getCamera().setMouseBehavior(Camera::SPACESHIP_BEHAVIOR);
	viewer->getCamera().setPosition(glm::vec3(m_particle->getPosition().x,-3+ParticleRenderableStudent::m_particle->getPosition().y, 3+ParticleRenderableStudent::m_particle->getPosition().z));
	glm::mat4 translation_skybox = glm::translate(glm::mat4(1.0), glm::vec3(3,prevY,prevZ));
	skybox->setParentTransform(translation_skybox);
	prevY = -2+ParticleRenderableStudent::m_particle->getPosition().y;
	prevZ = 2+ParticleRenderableStudent::m_particle->getPosition().z;

	// Rotation boule de neige
	setLocalTransform(glm::rotate(glm::mat4(1.0), -(float)(ParticleRenderableStudent::m_particle->getPosition().y), glm::vec3(1,0,0)));

	// Déplacement de la boule de neige latéralement : ajustement de la vitesse
	float vitesse = m_particle->getVelocity().y;
	if (gauche){
		m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(-.05, 0,0));
		ancien[0]=true;
	}
	if (droite){
		m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(0.05, 0,0));
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

	// Vitesse maximale autorisée
	if (m_particle->getVelocity().y > 25 ){
		glm::vec3 tmp = m_particle->getVelocity();
		tmp.y = 25;
		m_particle->setVelocity(tmp);
	}

	// Dessin de la boule de neige
	ParticleRenderableStudent::do_draw();

	int aleaM;
	int aleaA;
	int aleaB;
	// Distance entre la position et le bord du terrain précédent
	double distance = sqrt(m_particle->getPosition().y*m_particle->getPosition().y+m_particle->getPosition().z*m_particle->getPosition().z);
	// Déplacement du terrain et des objets s'y trouvant au fur et à mesure que la boule avance
	if (distance-5 >= k*40){

		// Déplacement des maisons
		for (int i = terrain*2; i <= terrain*2+1; i++) {
			aleaM = rand()%40;
			glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(rand()%(nx-2)+1,((k+2)*40+aleaM)*cos(angle),((k+2)*40+aleaM)*sin(angle)));
			glm::mat4 scaleM = glm::scale(trans, glm::vec3(0.02,0.02,0.02));
			meshes[i]->setParentTransform(scaleM);
		}

		// Déplacement des bonshommes de neige
		for (int i = terrain*2; i < terrain*2+1; i++) {
			aleaB = rand()%40;
			bonshommes[i]->generateAnimation(viewer->getTime(), glm::vec3(rand()%(nx/2)-8,((k+2)*40+aleaB)*cos(angle),((k+2)*40+aleaB)*sin(angle)));
		}

		// Déplacement de l'arbre
		for (int i = terrain*2; i < terrain*2+1; i++) {
			aleaA = rand()%40;
			glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(rand()%(nx-2)+1,((k+2)*40+aleaA)*cos(angle),((k+2)*40+aleaA)*sin(angle)));
			glm::mat4 scaleM = glm::scale(trans, glm::vec3(0.25,0.25,0.25));
			arbres[i]->setParentTransform(scaleM);
	  }

		// Déplacement du terrain
		glm::mat4 parentTransformation, localTransformation;
		GroundRenderablePtr tmp;
			for (int x=0; x<nx; x++){
				for (int y=0; y<40; y++){
					tmp = groundR[x][y];
					parentTransformation=glm::translate(glm::rotate(glm::mat4(1.0), angle, glm::vec3(1,0,0)), glm::vec3(x,(k+2)*40+y,0));
					tmp->setParentTransform(parentTransformation);
					localTransformation = glm::mat4(1.0);
					tmp->setLocalTransform(localTransformation);
				groundR[x][y]= groundR[x][y+40];
				groundR[x][y+40]=groundR[x][y+80];
				groundR[x][y+80]=tmp;
			}
		}
		k++;
		distance = sqrt(m_particle->getPosition().y*m_particle->getPosition().y+m_particle->getPosition().z*m_particle->getPosition().z);
		terrain = (terrain + 1)%3;
	}
}

SnowballRenderable::~SnowballRenderable()
{

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
	if (e.key.code == sf::Keyboard::F5){
		printf("coucou \n");
	}


}

void SnowballRenderable::do_keyReleasedEvent(sf::Event& e){
	gauche = false;
	droite = false;
	toutDroit = true;

}
