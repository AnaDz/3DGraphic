#include "../../include/students/Tree.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Tree::Tree(ShaderProgramPtr program, const std::string& textureFilename) :
  HierarchicalRenderable(program)
{
  glm::mat4 scaleM(1.0);
  glm::mat4 translationM(1.0);
  glm::mat4 rotationM(1.0);

  tronc = std::make_shared<TruncTex>(program, textureFilename);
  MaterialPtr pearl = Material::Pearl();
  tronc->setMaterial(pearl);
  std::shared_ptr<ConeRenderable> feuilles = std::make_shared<ConeRenderable>(program, m_material);
  translationM = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 1.5));
  scaleM = glm::scale(glm::mat4(1.0), glm::vec3(1.5,1.5,3.5));

  feuilles->setLocalTransform(rotationM*scaleM);
  feuilles->setParentTransform(translationM);

  HierarchicalRenderable::addChild(tronc,feuilles);

}

Tree::~Tree(){

}

void Tree::do_draw() {
  tronc->do_draw();
}

void Tree::do_animate(float time) {

}
