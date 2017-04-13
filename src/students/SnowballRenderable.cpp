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


SnowballRenderable::SnowballRenderable(ShaderProgramPtr flatShader,  ShaderProgramPtr phongShader, ShaderProgramPtr texShader, Viewer* v, ParticlePtr particle, std::shared_ptr<SphereRenderable> sky, DynamicSystemPtr system)
	: ParticleRenderableStudent(texShader, particle)
{

	//init générateur aléatoire
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

	 // Création du bonhomme de neige
	 bonhomme = std::make_shared<BonhommeDeNeige>(phongShader, texShader);
	 HierarchicalRenderable::addChild(bonhomme, bonhomme->base);
	 bonhomme->generateAnimation(0.0, glm::vec3(0,5*cos(angle),5*sin(angle))) ;
	 viewer->addRenderable(bonhomme);

	 // Création de l'arbre
	 std::string filename = "../textures/bark.jpg";
	 std::string filename2 = "../textures/needle.jpg";
	 arbre = std::make_shared<Tree>(texShader, filename, filename2);
	 glm::vec3 px,pv;
	 float pm, pr;
	//px = glm::vec3(0,0,0.5);
	 px = glm::vec3(5,5*cos(angle),5*sin(angle));
	 pv = glm::vec3(0,0,0);
	 pr = 1;
	 pm = 1.0;
	 particle_arbre = std::make_shared<Particle>(px, pv, pm, pr);
	 arbre->setParentTransform(glm::translate(glm::mat4(1.0), glm::vec3(5,5*cos(angle),5*sin(angle))));
	 arbre->setPosition(glm::vec3(5,5*cos(angle),5*sin(angle)));
	 particle_arbre->setSpecialAnimation(true);
	 particle_arbre->setLink(arbre);
	 particle_arbre->setFixed(true);
	 system->addParticle(particle_arbre);
	 //ParticleRenderablePtr part = std::make_shared<ParticleRenderable>(flatShader,particle_arbre);
	 HierarchicalRenderable::addChild(arbre, arbre->tronc);
	 viewer->addRenderable(arbre);
	 //viewer->addRenderable(part);
	 //Explosion(system, systemRenderable, phongShader);

	 // Création du mesh : la petite maison dans la prairie enneigée
 	 mesh=std::make_shared<TexturedMeshRenderable>(
	 texShader, "../meshes/Maison.obj", "../textures/Cottage Texture.jpg");
	 glm::mat4 trans, scaleM;
	 trans = glm::translate(glm::mat4(1.0), glm::vec3(1,5*cos(angle),5*sin(angle)));
	 scaleM = glm::scale(trans, glm::vec3(0.02,0.02,0.02));
	 mesh->setParentTransform(scaleM);
	 mesh->setMaterial(Material::Maison());
	 glm::mat4 rotationM = glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0)), (float)(M_PI/2.0), glm::vec3(0,1,0)), angle, glm::vec3(0,0,1));
	 mesh->setLocalTransform(rotationM);
	 viewer->addRenderable(mesh);



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
	// Déplacement du terrain et des objets s'y trouvant au fur et à mesure que la boule avance
	if (m_particle->getPosition().y >= k*40){
		// Déplacement de la maison
		aleaM = rand()%(40-30)+30;
		aleaA = rand()%(40-30)+30;
		aleaB = rand()%(40-30)+30;

		glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(rand()%(12-2)+2,(k*40+aleaM)*cos(angle),(k*40+aleaM)*sin(angle)));
		glm::mat4 scaleM = glm::scale(trans, glm::vec3(0.02,0.02,0.02));
		mesh->setParentTransform(scaleM);

		// Déplacement du bonhomme de neige
		bonhomme->generateAnimation(viewer->getTime(), glm::vec3(rand()%8,(k*40+aleaB)*cos(angle),(k*40+aleaB)*sin(angle)));

		// Déplacement de l'arbre
		int random = rand();
		glm::vec3 translation = glm::vec3(random%12,(k*40+aleaA)*cos(angle),(k*40+aleaA)*sin(angle));
		particle_arbre->setPosition(translation);
		arbre->setPosition(translation);
		trans = glm::translate(glm::mat4(1.0), translation);
		scaleM = glm::scale(trans, glm::vec3(1,1,1));
		arbre->setParentTransform(trans);
		arbre->generateAnimation(viewer->getTime());
		// Déplacement du terrain
		glm::mat4 parentTransformation, localTransformation;
		GroundRenderablePtr tmp;
			for (int x=0; x<nx; x++){
				for (int y=0; y<40; y++){
				// 	if (k%3==1){
				// 	tmp = std::make_shared<GroundRenderable>(flatShader,x,(k+2)*25+y,n, viewer);
				// 	viewer->addRenderable(tmp);
				//
				// } else {
					tmp = groundR[x][y];
					parentTransformation=glm::translate(glm::rotate(glm::mat4(1.0), angle, glm::vec3(1,0,0)), glm::vec3(x,(k+2)*40+y,0));
					tmp->setParentTransform(parentTransformation);
					localTransformation = glm::mat4(1.0);
					tmp->setLocalTransform(localTransformation);
				// }
				groundR[x][y]= groundR[x][y+40];
				groundR[x][y+40]=groundR[x][y+80];
				groundR[x][y+80]=tmp;
			}
		}
		//version2
	// 	for (int x=0; x<nx; x++){
	// 		for (int y=k*25; y<(k+1)*25; y++){
	// 		// 	if (k%3==1){
	// 		// 	tmp = std::make_shared<GroundRenderable>(flatShader,x,(k+2)*25+y,n, viewer);
	// 		// 	viewer->addRenderable(tmp);
	// 		//
	// 		// } else {
	// 			//tmp = groundR[x][y];
	// 			tmp= std::make_shared<GroundRenderable>(flatShader,x,y,n, viewer);
	// 			parentTransformation=glm::rotate(glm::mat4(1.0), angle, glm::vec3(1,0,0));
	// 			tmp->setParentTransform(parentTransformation);
	// 			localTransformation = glm::mat4(1.0);
	// 			tmp->setLocalTransform(localTransformation);
	// 		// }
	// 		printf("y=%i, ymod25 = %i, ymod25+25=%i,ymod25+50=%i\n ", y, y%25, y%25+25, y%25+50);
	// 		groundR[x][y%25]= groundR[x][y%25+25];
	// 		groundR[x][y%25+25]=groundR[x][y%25+50];
	// 		groundR[x][y%25+50]=tmp;
	//
	// 	}
	// }
		k++;
		//ajouterObstacles();
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
