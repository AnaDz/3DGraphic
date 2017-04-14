#include "../../include/students/Fence.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Fence::Fence(ShaderProgramPtr program, const std::string& textureFilename) :
  HierarchicalRenderable(program)
{
  glm::mat4 scaleM(1.0);
  glm::mat4 translationM(1.0);
  glm::mat4 rotationM(1.0);


  origin = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));
  origin->setLocalTransform(scaleM);
  std::shared_ptr<CylinderRenderable> second_poto = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  second_poto->setLocalTransform(rotationM*scaleM);
  second_poto->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,second_poto);

  std::shared_ptr<CylinderRenderable> poto_h1 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h1->setLocalTransform(rotationM*scaleM);
  poto_h1->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h1);

  std::shared_ptr<CylinderRenderable> poto_h2 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h2->setLocalTransform(rotationM*scaleM);
  poto_h2->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h2);


  std::shared_ptr<CylinderRenderable> poto_h3 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 2*5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h3->setLocalTransform(rotationM*scaleM);
  poto_h3->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h3);

  std::shared_ptr<CylinderRenderable> poto_h4 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*2, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h4->setLocalTransform(rotationM*scaleM);
  poto_h4->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h4);

  std::shared_ptr<CylinderRenderable> poto3 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 2*5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  poto3->setLocalTransform(scaleM);
  poto3->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto3);

  std::shared_ptr<CylinderRenderable> poto_h5 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 3*5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h5->setLocalTransform(rotationM*scaleM);
  poto_h5->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h5);

  std::shared_ptr<CylinderRenderable> poto_h6 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*3, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h6->setLocalTransform(rotationM*scaleM);
  poto_h6->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h6);

  std::shared_ptr<CylinderRenderable> poto4 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 3*5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  poto4->setLocalTransform(scaleM);
  poto4->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto4);


  std::shared_ptr<CylinderRenderable> poto_h7 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 4*5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h7->setLocalTransform(rotationM*scaleM);
  poto_h7->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h7);

  std::shared_ptr<CylinderRenderable> poto_h8 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*4, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h8->setLocalTransform(rotationM*scaleM);
  poto_h8->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h8);

  std::shared_ptr<CylinderRenderable> poto5 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 4*5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  poto5->setLocalTransform(scaleM);
  poto5->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto5);



  std::shared_ptr<CylinderRenderable> poto_h9 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h9->setLocalTransform(rotationM*scaleM);
  poto_h9->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h9);

  std::shared_ptr<CylinderRenderable> poto_h10 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*5, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h10->setLocalTransform(rotationM*scaleM);
  poto_h10->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h10);

  std::shared_ptr<CylinderRenderable> poto6 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  poto6->setLocalTransform(scaleM);
  poto6->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto6);

  std::shared_ptr<CylinderRenderable> poto_h11 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 6*5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h11->setLocalTransform(rotationM*scaleM);
  poto_h11->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h11);

  std::shared_ptr<CylinderRenderable> poto_h12 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*6, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h12->setLocalTransform(rotationM*scaleM);
  poto_h12->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h12);

  std::shared_ptr<CylinderRenderable> poto7 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 6*5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  poto7->setLocalTransform(scaleM);
  poto7->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto7);



  std::shared_ptr<CylinderRenderable> poto_h13 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 7*5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h13->setLocalTransform(rotationM*scaleM);
  poto_h13->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h13);

  std::shared_ptr<CylinderRenderable> poto_h14 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*7, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h14->setLocalTransform(rotationM*scaleM);
  poto_h14->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h14);

  std::shared_ptr<CylinderRenderable> poto8 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 7*5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  poto8->setLocalTransform(scaleM);
  poto8->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto8);


  std::shared_ptr<CylinderRenderable> poto_h15 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 8*5, 2.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h15->setLocalTransform(rotationM*scaleM);
  poto_h15->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h15);

  std::shared_ptr<CylinderRenderable> poto_h16 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 5*8, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.15,0.15,5.0));
  rotationM = glm::rotate(glm::mat4(1.0), (float)(M_PI/2.0), glm::vec3(1,0,0));
  poto_h16->setLocalTransform(rotationM*scaleM);
  poto_h16->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto_h16);

  std::shared_ptr<CylinderRenderable> poto9 = std::make_shared<CylinderRenderable>(program, m_material, textureFilename);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 8*5, 0));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,3.0));

  poto9->setLocalTransform(scaleM);
  poto9->setParentTransform(translationM);

  HierarchicalRenderable::addChild(origin,poto9);
}


Fence::~Fence(){

}


void Fence::do_draw() {

}

void Fence::do_animate(float time) {

}
