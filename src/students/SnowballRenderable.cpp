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
#include "../../include/students/Explosion.hpp"
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

int nx = 12;
int ny = 120;
int n = 10;
float angle = -(float)3.14/12;
int terrain = 0; // Le terrain que la boule vient de parcourir

// "Fréquence" d'apparition des objets
int nb_bonhommes = 3*3;
int nb_maisons = 3*3;
int nb_arbres = 3*3;

SnowballRenderable::SnowballRenderable(ShaderProgramPtr flatShader,  ShaderProgramPtr phongShader, ShaderProgramPtr texShader, Viewer* v, ParticlePtr particle, std::shared_ptr<SphereRenderable> sky, DynamicSystemPtr system, DynamicSystemRenderablePtr systemRenderable)
	: ParticleRenderableStudent(texShader, particle)
{

	// Initialisation du générateur aléatoire
		 srand(time(NULL));

	 // Initialisation des attributs
	 viewer = v;
	 this->flatShader=flatShader;
	 this->texShader=texShader;
	 this->phongShader=phongShader;
	 this->systemRenderable=systemRenderable;
	 this->system=system;
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

 	 glm::vec3 px,pv;
	 float pm, pr;
	 bonshommes.resize(nb_bonhommes);
	 particle_bonhomme.resize(nb_bonhommes);
	 meshes.resize(nb_maisons);
	 posMesh.resize(nb_maisons);
	 arbres.resize(nb_arbres);
	 particle_arbre.resize(nb_arbres);


	 // Création des bonshommes de neige
	 px = glm::vec3(0,5*cos(angle),5*sin(angle));
	 pv = glm::vec3(0,0,0);
	 pr = 0.49;
	 pm = 1.0;

	 for (int i = 0; i < nb_bonhommes; i++) {
		 bonshommes[i] = std::make_shared<BonhommeDeNeige>(phongShader, texShader);
		 HierarchicalRenderable::addChild(bonshommes[i], bonshommes[i]->base);
		 bonshommes[i]->setParentTransform(glm::translate(glm::mat4(1.0), glm::vec3(0,-5*cos(angle),-5*sin(angle))));
		 bonshommes[i]->setPosition(glm::vec3(0,-5*cos(angle),-5*sin(angle)));

		 particle_bonhomme[i] = std::make_shared<Particle>(px, pv, pm, pr);
		 particle_bonhomme[i]->setSpecialAnimation(true);
		 particle_bonhomme[i]->setLink(bonshommes[i]);
		 particle_bonhomme[i]->setFixed(true);
		 particle_bonhomme[i]->setScore(5);

		 system->addParticle(particle_bonhomme[i]);
		 bonshommes[i]->addParticle(particle_bonhomme[i]);
		 bonshommes[i]->generateAnimation(0.0);
		 viewer->addRenderable(bonshommes[i]);
 	 }

	 std::string filename = "../textures/bark.jpg";
	 std::string filename2 = "../textures/needle.jpg";
	 px = glm::vec3(5,5*cos(angle),5*sin(angle));
	 pv = glm::vec3(0,0,0);
	 pr = 0.5;
	 pm = 1.0;

	 for (int i = 0; i < nb_arbres; i++) {
		 arbres[i] = std::make_shared<Tree>(texShader, filename, filename2);
		 particle_arbre[i] = std::make_shared<Particle>(px, pv, pm, pr);
		 arbres[i]->setParentTransform(glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(1,-5*cos(angle),-5*sin(angle))), glm::vec3(0.25,0.25,0.25)));
		 arbres[i]->setPosition(glm::vec3(1,-5*cos(angle),-5*sin(angle)));
		 particle_arbre[i]->setSpecialAnimation(true);
		 particle_arbre[i]->setLink(arbres[i]);
		 particle_arbre[i]->setFixed(true);
		 particle_arbre[i]->setScore(1);
		 system->addParticle(particle_arbre[i]);
		 HierarchicalRenderable::addChild(arbres[i], arbres[i]->tronc);
		 viewer->addRenderable(arbres[i]);
 	 }

	 // Création des meshes : la petite maison dans la prairie enneigée version Camping Paradis
	 glm::mat4 trans, scaleM;
	 for (int i = 0; i < nb_maisons; i++) {
	 	 meshes[i]=std::make_shared<TexturedMeshRenderable>(
		 		texShader, "../meshes/Maison.obj", "../textures/Cottage Texture.jpg");
		 trans = glm::translate(glm::mat4(1.0), glm::vec3(5.0,-10*cos(angle),-10*sin(angle)));
		 scaleM = glm::scale(trans, glm::vec3(0.03,0.03,0.03));
		 meshes[i]->setParentTransform(scaleM);
		 meshes[i]->setMaterial(Material::Maison());
		 glm::mat4 rotationM = glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0)), (float)(M_PI/2.0), glm::vec3(0,1,0)), angle, glm::vec3(0,0,1));
		 meshes[i]->setLocalTransform(rotationM);
		 viewer->addRenderable(meshes[i]);
		 posMesh[i]=glm::vec3(5.0,-10*cos(angle), -10*sin(angle));
   }

	 explo = std::make_shared<Explosion>(system, systemRenderable, phongShader, glm::vec3(-10,-10,-10), m_particle->getRadius());

	 fences.resize(6);
	 for (int i=0; i<fences.size(); i++){
		 fences[i] = std::make_shared<Fence>(texShader, "../textures/candy.jpg");
		 //fences[i]->setParentTransform(glm::scale(glm::mat4(1.0), glm::vec3(0.5,1,0.2)));
		 HierarchicalRenderable::addChild(groundR[i%2*(nx-1)][i%3*(ny/3-1)], fences[i]);
		 HierarchicalRenderable::addChild(fences[i], fences[i]->origin);
		 viewer->addRenderable(fences[i]);
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

bool detectionObjetFin = false;

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
		m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(-.1, 0,0));
		ancien[0]=true;
	}
	if (droite){
		m_particle->setVelocity(m_particle->getVelocity() + glm::vec3(0.1, 0,0));
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

	// détection collision Mesh
	//2.1 gauche, 0.85*cos(angle) haut 1.4 droite, 1.2*sin(angle) bas
	for (int i=0; i < nb_maisons; i++){
		if ((m_particle->getPosition().x  + m_particle->getRadius())< posMesh[i].x+1.8 && (m_particle->getPosition().x +m_particle->getRadius()) > posMesh[i].x-2.1 && (m_particle->getPosition().y + m_particle->getRadius())< posMesh[i].y+1.2*cos(angle) && (m_particle->getPosition().y + m_particle->getRadius()) > posMesh[i].y-0.85*cos(angle)){
			detectionObjetFin=true;
		}
	}

	if (detectionObjetFin && fin_explo){
		//printf("salut yolo \n");
 	 //Explosion(system, systemRenderable, phongShader, m_particle->getPosition(), m_particle->getRadius());
	 glm::vec3 px,pv;
	 double radius = m_particle->getRadius();
	 int slices = 7;
	 int strips = 7;
	 for(int i=0; i<slices; ++i) {
		 for(int j=0; j<strips; ++j) {
			 double curr_theta = i*(2.0*M_PI/(double)slices);
			 double curr_phi = j*(M_PI/(double)strips);
			 int v = 40;
			 px = m_particle->getPosition() + glm::vec3(0,0,radius) + glm::vec3(radius*cos(curr_theta)*sin(curr_phi), radius*sin(curr_theta)*sin(curr_phi), radius*cos(curr_phi));
			 pv = glm::vec3(v*radius*cos(curr_theta)*sin(curr_phi), v*radius*sin(curr_theta)*sin(curr_phi), v*radius*cos(curr_phi));
			 //ParticlePtr particle = std::make_shared<Particle>(px, pv, pm, pr);
			 explo->listePart[i][j]->setPosition(px);
			 explo->listePart[i][j]->setVelocity(pv);
		 }
	 }
	 m_particle->setFixed(true);
	 this->fin_explo=false;
	} else if (fin_explo) {
		// Dessin boule de neige
		ParticleRenderableStudent::do_draw();
	}

	int aleaM;
	int aleaA;
	int aleaB;
	// Distance entre la position et le bord du terrain précédent
	double distance = sqrt(m_particle->getPosition().y*m_particle->getPosition().y+m_particle->getPosition().z*m_particle->getPosition().z);
	// Déplacement du terrain et des objets s'y trouvant au fur et à mesure que la boule avance
	if (distance-5 >= k*40){

		// Déplacement des maisons
		for (int i = terrain*(nb_maisons/3); i <= terrain*(nb_maisons/3)+(nb_maisons/3)-1; i++) {
			aleaM = rand()%40;
			glm::vec3 translation = glm::vec3(rand()%(nx-2)+1,((k+2)*40+aleaM)*cos(angle),((k+2)*40+aleaM)*sin(angle));
			glm::mat4 trans = glm::translate(glm::mat4(1.0), translation);
			glm::mat4 scaleM = glm::scale(trans, glm::vec3(0.04,0.04,0.04));
			meshes[i]->setParentTransform(scaleM);
			posMesh[i]= translation;
		}

		// Déplacement des bonshommes de neige
		for (int i = terrain*(nb_bonhommes/3); i <= terrain*(nb_bonhommes/3)+(nb_bonhommes/3)-1; i++) {
			aleaB = rand()%40;
			glm::vec3 translation = glm::vec3(rand()%(nx/2)-8,((k+2)*40+aleaB)*cos(angle),((k+2)*40+aleaB)*sin(angle));
			bonshommes[i]->setFalled(false);
			bonshommes[i]->setPosition(translation);
			glm::mat4 trans = glm::translate(glm::mat4(1.0), translation);
			bonshommes[i]->setParentTransform(trans);
			particle_bonhomme[i]->setPosition(translation);
			bonshommes[i]->generateAnimation(viewer->getTime());
		}

		// Déplacement de l'arbre
		for (int i = terrain*(nb_arbres/3); i <= terrain*(nb_arbres/3)+(nb_arbres/3)-1; i++) {
			aleaA = rand()%40;
			glm::vec3 translation = glm::vec3(rand()%(nx-2)+1,((k+2)*40+aleaA)*cos(angle),((k+2)*40+aleaA)*sin(angle));
			particle_arbre[i]->setPosition(translation);
			glm::mat4 trans = glm::translate(glm::mat4(1.0), translation);
			arbres[i]->setPosition(translation);
			arbres[i]->setParentTransform(trans);
			arbres[i]->generateAnimation(viewer->getTime());
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
		printf("coucou on recommence :)  \n");
	}


}

void SnowballRenderable::do_keyReleasedEvent(sf::Event& e){
	gauche = false;
	droite = false;
	toutDroit = true;

}
