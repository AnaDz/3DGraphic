#include "../../include/students/BonhommeDeNeige.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>


BonhommeDeNeige::BonhommeDeNeige(ShaderProgramPtr shaderProgram) :
  HierarchicalRenderable(shaderProgram)
{
  glm::mat4 scaleM(1.0);
  glm::mat4 translationM(1.0);
  glm::mat4 rotationM(1.0);
  glm::vec4 blanc = glm::vec4(1,1,1,0);
  glm::vec4 noir = glm::vec4(0.15, 0.15, 0.15, 0);
  glm::vec4 bleu = glm::vec4(0, 0.5, 0.9, 0);
  glm::vec4 orange = glm::vec4(0.8, 0.4, 0.4, 0);
  double taille_tete = 1.25;
  double taille_buste = 2.0;
  double taille_base = 3.0;
  double taille_boutons = 0.15;
  double angle_boutons = M_PI/20;
  double theta = M_PI/6; // Angle vertical pour positionner les yeux
  double phi = M_PI/8; // Angle horizontal

  // Base du bonhomme de neige
  base = std::make_shared<SphereRenderable>(shaderProgram, blanc);
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_base,taille_base,taille_base));
  base->setLocalTransform(scaleM);

  // Buste du bonhomme de neige
  std::shared_ptr<SphereRenderable> buste = std::make_shared<SphereRenderable>(shaderProgram, blanc);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_base + 0.5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_buste,taille_buste,taille_buste));
  buste->setParentTransform(translationM);
  buste->setLocalTransform(scaleM);

  // Tête du bonhomme de neige
  std::shared_ptr<SphereRenderable> tete = std::make_shared<SphereRenderable>(shaderProgram, blanc);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_buste + 0.5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete,taille_tete,taille_tete));
  tete->setParentTransform(translationM);
  tete->setLocalTransform(scaleM);

  HierarchicalRenderable::addChild(base, buste);
  HierarchicalRenderable::addChild(buste, tete);

  // Boutons du bonhomme de neige
  std::shared_ptr<SphereRenderable> bouton1 = std::make_shared<SphereRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_base*cos(-angle_boutons), taille_base*sin(-angle_boutons), 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_boutons/2,taille_boutons,taille_boutons));
  bouton1->setParentTransform(translationM);
  bouton1->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> bouton2 = std::make_shared<SphereRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_base*cos(angle_boutons), taille_base*sin(angle_boutons), 0));
  bouton2->setParentTransform(translationM);
  bouton2->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> bouton3 = std::make_shared<SphereRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_buste*cos(-angle_boutons), taille_buste*sin(-angle_boutons), 0));
  bouton3->setParentTransform(translationM);
  bouton3->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> bouton4 = std::make_shared<SphereRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_buste*cos(angle_boutons), taille_buste*sin(angle_boutons), 0));
  bouton4->setParentTransform(translationM);
  bouton4->setLocalTransform(scaleM);

  HierarchicalRenderable::addChild(base, bouton1);
  HierarchicalRenderable::addChild(base, bouton2);
  HierarchicalRenderable::addChild(buste, bouton3);
  HierarchicalRenderable::addChild(buste, bouton4);

  // Yeux du bonhomme de neige
  std::shared_ptr<SphereRenderable> oeil1 = std::make_shared<SphereRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_tete*cos(phi), taille_tete*sin(theta)*sin(phi), taille_tete*cos(theta)*sin(phi)));
  oeil1->setParentTransform(translationM);
  oeil1->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> oeil2 = std::make_shared<SphereRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_tete*cos(phi), taille_tete*sin(theta)*sin(phi), taille_tete*cos(theta)*sin(-phi)));
  oeil2->setParentTransform(translationM);
  oeil2->setLocalTransform(scaleM);

  HierarchicalRenderable::addChild(tete, oeil1);
  HierarchicalRenderable::addChild(tete, oeil2);

  // Chapeau du bonhomme de neige
  std::shared_ptr<CylinderRenderable> chapeau_base = std::make_shared<CylinderRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_tete*0.95, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete,taille_tete,taille_tete*0.1));
  rotationM = glm::rotate(glm::mat4(1.0), -(float)(M_PI/2.0), glm::vec3(1,0,0));
  chapeau_base->setParentTransform(translationM);
  chapeau_base->setLocalTransform(rotationM*scaleM);

  std::shared_ptr<CylinderRenderable> chapeau_forme = std::make_shared<CylinderRenderable>(shaderProgram, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_tete*0.1, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete*0.5,taille_tete*0.5,taille_tete));
  rotationM = glm::rotate(glm::mat4(1.0), -(float)(M_PI/2.0), glm::vec3(1,0,0));
  chapeau_forme->setParentTransform(translationM);
  chapeau_forme->setLocalTransform(rotationM*scaleM);

  std::shared_ptr<CylinderRenderable> chapeau_bourdalou = std::make_shared<CylinderRenderable>(shaderProgram, bleu);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_tete*0.1, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete*0.51,taille_tete*0.51,taille_tete*0.2));
  rotationM = glm::rotate(glm::mat4(1.0), -(float)(M_PI/2.0), glm::vec3(1,0,0));
  chapeau_bourdalou->setParentTransform(translationM);
  chapeau_bourdalou->setLocalTransform(rotationM*scaleM);

  HierarchicalRenderable::addChild(tete, chapeau_base);
  HierarchicalRenderable::addChild(chapeau_base, chapeau_forme);
  HierarchicalRenderable::addChild(chapeau_base, chapeau_bourdalou);

  // Carotte du bonhomme de neige
  std::shared_ptr<ConeRenderable> carotte = std::make_shared<ConeRenderable>(shaderProgram, orange);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_tete, 0, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete*0.1,taille_tete*0.1,taille_tete));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(0,1,0));
  carotte->setParentTransform(translationM);
  carotte->setLocalTransform(rotationM*scaleM);

  HierarchicalRenderable::addChild(tete, carotte);

}

void BonhommeDeNeige::do_draw() {
  base->do_draw();
}

void BonhommeDeNeige::do_animate(float time) {}
