#include "../../include/students/BonhommeDeNeige.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>


BonhommeDeNeige::BonhommeDeNeige(ShaderProgramPtr phongShader, ShaderProgramPtr texShader) :
  HierarchicalRenderable(texShader)
{
  glm::mat4 scaleM(1.0);
  glm::mat4 translationM(1.0);
  glm::mat4 rotationM(1.0);
  const MaterialPtr& blanc = Material::Neige();
  const MaterialPtr& noir = Material::TissuNoir();
  const MaterialPtr& bleu = Material::TissuBleu();
  const MaterialPtr& orange = Material::Carotte();
  double taille_tete = 1.25;
  double taille_buste = 2.0;
  double taille_base = 3.0;
  double taille_boutons = 0.15;
  double angle_boutons = M_PI/20;
  double theta = M_PI/6; // Angle vertical pour positionner les yeux
  double phi = M_PI/8; // Angle horizontal pour positionner les yeux

  // Base du bonhomme de neige
  base = std::make_shared<SphereRenderable>(texShader, blanc);
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_base,taille_base,taille_base));
  base->setLocalTransform(scaleM);

  // Buste du bonhomme de neige
  std::shared_ptr<SphereRenderable> buste = std::make_shared<SphereRenderable>(texShader, blanc);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_base + 0.5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_buste,taille_buste,taille_buste));
  buste->setParentTransform(translationM);
  buste->setLocalTransform(scaleM);

  // Tête du bonhomme de neige
  std::shared_ptr<SphereRenderable> tete = std::make_shared<SphereRenderable>(texShader, blanc);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_buste + 0.5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete,taille_tete,taille_tete));
  tete->setParentTransform(translationM);
  tete->setLocalTransform(scaleM);

  HierarchicalRenderable::addChild(base, buste);
  HierarchicalRenderable::addChild(buste, tete);

  // Boutons du bonhomme de neige
  std::shared_ptr<SphereRenderable> bouton1 = std::make_shared<SphereRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_base*cos(-angle_boutons), taille_base*sin(-angle_boutons), 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_boutons/2,taille_boutons,taille_boutons));
  bouton1->setParentTransform(translationM);
  bouton1->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> bouton2 = std::make_shared<SphereRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_base*cos(angle_boutons), taille_base*sin(angle_boutons), 0));
  bouton2->setParentTransform(translationM);
  bouton2->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> bouton3 = std::make_shared<SphereRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_buste*cos(-angle_boutons), taille_buste*sin(-angle_boutons), 0));
  bouton3->setParentTransform(translationM);
  bouton3->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> bouton4 = std::make_shared<SphereRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_buste*cos(angle_boutons), taille_buste*sin(angle_boutons), 0));
  bouton4->setParentTransform(translationM);
  bouton4->setLocalTransform(scaleM);

  HierarchicalRenderable::addChild(base, bouton1);
  HierarchicalRenderable::addChild(base, bouton2);
  HierarchicalRenderable::addChild(buste, bouton3);
  HierarchicalRenderable::addChild(buste, bouton4);

  // Yeux du bonhomme de neige
  std::shared_ptr<SphereRenderable> oeil1 = std::make_shared<SphereRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_tete*cos(phi), taille_tete*sin(theta)*sin(phi), taille_tete*cos(theta)*sin(phi)));
  oeil1->setParentTransform(translationM);
  oeil1->setLocalTransform(scaleM);

  std::shared_ptr<SphereRenderable> oeil2 = std::make_shared<SphereRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_tete*cos(phi), taille_tete*sin(theta)*sin(phi), taille_tete*cos(theta)*sin(-phi)));
  oeil2->setParentTransform(translationM);
  oeil2->setLocalTransform(scaleM);

  HierarchicalRenderable::addChild(tete, oeil1);
  HierarchicalRenderable::addChild(tete, oeil2);

  // Chapeau du bonhomme de neige
  std::shared_ptr<CylinderRenderable> chapeau_base = std::make_shared<CylinderRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_tete*0.95, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete,taille_tete,taille_tete*0.1));
  rotationM = glm::rotate(glm::mat4(1.0), -(float)(M_PI/2.0), glm::vec3(1,0,0));
  chapeau_base->setParentTransform(translationM);
  chapeau_base->setLocalTransform(rotationM*scaleM);

  std::shared_ptr<CylinderRenderable> chapeau_forme = std::make_shared<CylinderRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_tete*0.1, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete*0.5,taille_tete*0.5,taille_tete));
  rotationM = glm::rotate(glm::mat4(1.0), -(float)(M_PI/2.0), glm::vec3(1,0,0));
  chapeau_forme->setParentTransform(translationM);
  chapeau_forme->setLocalTransform(rotationM*scaleM);

  std::shared_ptr<CylinderRenderable> chapeau_bourdalou = std::make_shared<CylinderRenderable>(phongShader, bleu);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, taille_tete*0.1, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete*0.51,taille_tete*0.51,taille_tete*0.2));
  rotationM = glm::rotate(glm::mat4(1.0), -(float)(M_PI/2.0), glm::vec3(1,0,0));
  chapeau_bourdalou->setParentTransform(translationM);
  chapeau_bourdalou->setLocalTransform(rotationM*scaleM);

  HierarchicalRenderable::addChild(tete, chapeau_base);
  HierarchicalRenderable::addChild(chapeau_base, chapeau_forme);
  HierarchicalRenderable::addChild(chapeau_base, chapeau_bourdalou);

  // Carotte du bonhomme de neige
  std::shared_ptr<ConeRenderable> carotte = std::make_shared<ConeRenderable>(phongShader, orange);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(taille_tete, 0, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_tete*0.1,taille_tete*0.1,taille_tete));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(0,1,0));
  carotte->setParentTransform(translationM);
  carotte->setLocalTransform(rotationM*scaleM);

  HierarchicalRenderable::addChild(tete, carotte);

  // Bras du bonhomme de neige
  std::shared_ptr<ConeRenderable> bras1 = std::make_shared<ConeRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0.9*taille_buste*cos(M_PI/2)*sin(M_PI/6), 0.9*taille_buste*sin(M_PI/2)*sin(M_PI/6), 0.9*taille_buste*cos(M_PI/6)));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_buste*0.05,taille_buste*0.05,taille_tete*4));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(0,0,1));
  rotationM *= glm::rotate(glm::mat4(1.0), (float)(M_PI/6.0), glm::vec3(0,1,0));
  bras1->setParentTransform(translationM);
  bras1->setLocalTransform(rotationM*scaleM);

  std::shared_ptr<ConeRenderable> bras2 = std::make_shared<ConeRenderable>(phongShader, noir);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0.9*taille_buste*cos(M_PI/2)*sin(5*M_PI/6), 0.9*taille_buste*sin(M_PI/2)*sin(5*M_PI/6), 0.9*taille_buste*cos(5*M_PI/6)));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(taille_buste*0.05,taille_buste*0.05,taille_tete*4));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(0,0,1));
  rotationM *= glm::rotate(glm::mat4(1.0), (float)(3*M_PI/4.0), glm::vec3(0,1,0));
  bras2->setParentTransform(translationM);
  bras2->setLocalTransform(rotationM*scaleM);

  HierarchicalRenderable::addChild(buste, bras1);
  HierarchicalRenderable::addChild(buste, bras2);

  // Repositionnement et redimensionnement final du bonhomme de neige
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.3, 0.3, 0.3));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  base->setParentTransform(rotationM*scaleM);

  existe = true;
}

BonhommeDeNeige::~BonhommeDeNeige() {

}

void BonhommeDeNeige::addParentTransformKeyframe(float time, const GeometricTransformation& transformation) {
  m_parentKeyframes.add(time, transformation);
}

void BonhommeDeNeige::addLocalTransformKeyframe(float time, const GeometricTransformation& transformation) {
  m_localKeyframes.add(time, transformation);
}

void BonhommeDeNeige::do_draw() {

}

void BonhommeDeNeige::do_animate(float time) {
  //Assign the interpolated transformations from the keyframes to the local/parent transformations.
  if (!m_localKeyframes.empty()) {
      setLocalTransform(m_localKeyframes.interpolateTransformation(time));
  }
  if (!m_parentKeyframes.empty()) {
      setParentTransform(m_parentKeyframes.interpolateTransformation(time));
  }
}

void BonhommeDeNeige::generateAnimation(glm::vec3 depart) {
  // Animation du bonhomme de neige : il saute droit devant depuis la position depart indiquée en paramètre
  int nb_sauts = 2; // Nombre de sauts que fait le bonhomme de neige en ligne droite
  for (int t=0; t < nb_sauts; t++) {
    this->addParentTransformKeyframe(t+0.0, GeometricTransformation(glm::vec3(depart.x+(2.0*t)+0.0, depart.y+0.0, depart.z+0.0), glm::angleAxis(0.0f, glm::vec3(0.0, 0.0, 1.0))));
    this->addParentTransformKeyframe(t+0.2, GeometricTransformation(glm::vec3(depart.x+(2.0*t)+0.35, depart.y+0.0, depart.z+0.7), glm::angleAxis(0.0f, glm::vec3(0.0, 1.0, 0.0))));
    this->addParentTransformKeyframe(t+0.4, GeometricTransformation(glm::vec3(depart.x+(2.0*t)+0.7, depart.y+0.0, depart.z+1.3), glm::angleAxis(0.0f, glm::vec3(0.0, 1.0, 0.0))));
    this->addParentTransformKeyframe(t+0.5, GeometricTransformation(glm::vec3(depart.x+(2.0*t)+1.0, depart.y+0.0, depart.z+1.5), glm::angleAxis(0.0f, glm::vec3(0.0, 1.0, 0.0))));
    this->addParentTransformKeyframe(t+0.6, GeometricTransformation(glm::vec3(depart.x+(2.0*t)+1.3, depart.y+0.0, depart.z+1.3), glm::angleAxis(0.0f, glm::vec3(0.0, 1.0, 0.0))));
    this->addParentTransformKeyframe(t+0.8, GeometricTransformation(glm::vec3(depart.x+(2.0*t)+1.65, depart.y+0.0, depart.z+0.7), glm::angleAxis(0.0f, glm::vec3(0.0, 1.0, 0.0))));
    this->addParentTransformKeyframe(t+1.0, GeometricTransformation(glm::vec3(depart.x+(2.0*t)+2.0, depart.y+0.0, depart.z+0.0), glm::angleAxis(0.0f, glm::vec3(0.0, 1.0, 0.0))));
  }
}

void BonhommeDeNeige::supprimer() {
  if (!existe) {
    base->supprimer();
  }
}
