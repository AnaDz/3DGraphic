#include"../../include/students/Explosion.hpp"
#include "../../include/dynamics/ConstantForceField.hpp"
#include "../../include/dynamics_rendering/ConstantForceFieldRenderable.hpp"
#include "../../include/dynamics/Plane.hpp"
#include "../../include/dynamics_rendering/QuadRenderable.hpp"
#include "../../include/Utils.hpp"
#include "../../include/students/ParticleExplosion.hpp"

Explosion::Explosion(DynamicSystemPtr system, DynamicSystemRenderablePtr systemRenderable, ShaderProgramPtr phongShader, glm::vec3 position, double radius){
  /* ParticleExplosion mggl*/

  glm::mat4 translationM(1.0);
  //system->setCollisionsDetection(true);

  //Initialize the restitution coefficient for collision
  //1.0 = full elastic response
  //0.0 = full absorption
  system->setRestitution(0.6f);

  // //Initialize a plane from 3 points and add it to the system as an obstacle
  // glm::vec3 p1(-50.0, -50.0, 0.0);
  // glm::vec3 p2(50.0, -50.0, 0.0);
  // glm::vec3 p3(50.0, 50.0, 0.0);
  // glm::vec3 p4(-50.0, 50.0, 0.0);
  // PlanePtr plane = std::make_shared<Plane>(p1, p2, p3);
  // system->addPlaneObstacle(plane);
  //
  //
  //
  // //Create a plane renderable to display the obstacle
  // PlaneRenderablePtr planeRenderable = std::make_shared<QuadRenderable>(phongShader, p1,p2,p3,p4);
  // HierarchicalRenderable::addChild( systemRenderable, planeRenderable );

  glm::vec3 px,pv;
  float pm, pr;

  int slices = 7;
  int strips = 7;

  listePart.resize(slices, std::vector<ParticlePtr>(strips));

  for(int i=0; i<slices; ++i)
  {
      for(int j=0; j<strips; ++j)
      {
          double curr_theta = i*(2.0*M_PI/(double)slices);
          double curr_phi = j*(M_PI/(double)strips);
          /* MODULABLE */
          /* Ce qu'on peut faire : augmenter le v ou diminuer
          et aussi ajouter une composante pour la vitesse (genre 20 + Vx) pour que les boules soient dirigées plus vers un sens !*/
          int v = random(2,10);
          v = 40;
          px = position + glm::vec3(0,0,radius) + glm::vec3(radius*cos(curr_theta)*sin(curr_phi), radius*sin(curr_theta)*sin(curr_phi), radius*cos(curr_phi));
          pv = glm::vec3(v*radius*cos(curr_theta)*sin(curr_phi), v*radius*sin(curr_theta)*sin(curr_phi), v*radius*cos(curr_phi));
          pr = random(radius/6,radius/2);
          pm = 10;
          //ParticlePtr particle = std::make_shared<Particle>(px, pv, pm, pr);
          listePart[i][j]= std::make_shared<Particle>(px, pv, pm, pr);
          system->addParticle(listePart[i][j]);

          // ATTENTION A ADAPTER LE TRANSLATE
          translationM = glm::translate(glm::mat4(1.0), glm::vec3(0.0,0.0,4.0));
          ParticleRenderableStudentPtr particleRenderable = std::make_shared<ParticleRenderableStudent>(phongShader, listePart[i][j]);

          ParticleExplosionPtr expl = std::make_shared<ParticleExplosion>(phongShader, Material::Neige(), listePart[i][j]);

          HierarchicalRenderable::addChild(systemRenderable, expl);

        }
      }
      ConstantForceFieldPtr gravityForceField
          = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0, 0, -10} );
      system->addForceField(gravityForceField);
}
Explosion::~Explosion(){}
