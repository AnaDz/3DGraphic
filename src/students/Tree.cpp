#include "../../include/students/Tree.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Tree::Tree(ShaderProgramPtr program, const std::string& textureFilename, const std::string& textureFilename2) :
  HierarchicalRenderable(program)
{
  glm::mat4 scaleM(1.0);
  glm::mat4 translationM(1.0);
  glm::mat4 rotationM(1.0);


  tronc = std::make_shared<TruncTex>(program, textureFilename);
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.25,0.25,0.25));
  tronc->setLocalTransform(scaleM);
  std::shared_ptr<ConeRenderable> feuilles = std::make_shared<ConeRenderable>(program, m_material, textureFilename2);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0.25));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(1.5*0.25,1.5*0.25,3.5*0.25));

  feuilles->setLocalTransform(rotationM*scaleM);
  feuilles->setParentTransform(translationM);

  HierarchicalRenderable::addChild(tronc,feuilles);
  existe = true;

}

void Tree::generateAnimation(float time){
  this->addParentTransformKeyframe(time + 0.0, GeometricTransformation(position + glm::vec3(0.0, 0.0, 0.0), glm::angleAxis(0.0f, glm::vec3(1.0, 0.0, 0.0))));
  if(falling){
    this->addParentTransformKeyframe(time + 0.0, GeometricTransformation(position + glm::vec3(0.0, 0.0, 0.0), glm::angleAxis(0.0f, glm::vec3(1.0, 0.0, 0.0))));
    this->addParentTransformKeyframe(time + 0.5, GeometricTransformation(position + glm::vec3(0.0, 6.0, 1.0), glm::angleAxis(1.0f, glm::vec3(1.0, 0.0, 0.0))));
    this->addParentTransformKeyframe(time + 1, GeometricTransformation(position + glm::vec3(0.0, 12.0, 2.5), glm::angleAxis(2.0f, glm::vec3(1.0, 0.0, 0.0))));
    this->addParentTransformKeyframe(time + 1.2, GeometricTransformation(position + glm::vec3(0.0, 13, 3), glm::angleAxis(2.0f, glm::vec3(1.0, 0.0, 0.0))));
    this->addParentTransformKeyframe(time + 1.4, GeometricTransformation(position + glm::vec3(0.0, 15, 4), glm::angleAxis(2.0f, glm::vec3(1.0, 0.0, 0.0))));
  }
}

void Tree::addParentTransformKeyframe(float time, const GeometricTransformation& transformation) {
  m_parentKeyframes.add(time, transformation);
}

void Tree::addLocalTransformKeyframe(float time, const GeometricTransformation& transformation) {
  m_localKeyframes.add(time, transformation);
}


Tree::~Tree(){

}


void Tree::do_draw() {
}

void Tree::do_animate(float time) {
  if(falling){
    generateAnimation(time);
  }

  if (!m_localKeyframes.empty()) {
      setLocalTransform(m_localKeyframes.interpolateTransformation(time));
  }
  if (!m_parentKeyframes.empty()) {
      setParentTransform(m_parentKeyframes.interpolateTransformation(time));
      falling = false;
  }
}

void Tree::supprimer() {
  if (!existe) {
    tronc->supprimer();
  }
}


void Tree::setPosition(glm::vec3 pos){
  position = pos;
}
