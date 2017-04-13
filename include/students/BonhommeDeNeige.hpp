#ifndef BONHOMME_DE_NEIGE_HPP
#define BONHOMME_DE_NEIGE_HPP

#include "../../include/HierarchicalRenderable.hpp"
#include "../../include/students/SphereRenderable.hpp"
#include "../../include/students/CylinderRenderable.hpp"
#include "../../include/students/ConeRenderable.hpp"
#include "../../include/dynamics/Particle.hpp"

#include "../../include/keyframes/KeyframeCollection.hpp"

#include <vector>
#include <glm/glm.hpp>

class BonhommeDeNeige : public HierarchicalRenderable {
public:
  BonhommeDeNeige(ShaderProgramPtr phongShader, ShaderProgramPtr texShader);
  ~BonhommeDeNeige();
  std::shared_ptr<SphereRenderable> base;
  void addParentTransformKeyframe(float time, const GeometricTransformation& transformation);
  void addLocalTransformKeyframe(float time, const GeometricTransformation& transformation);
  void generateAnimation(float temps);
  void supprimer();
  void setPosition(glm::vec3 pos);
  void addParticle(ParticlePtr part);
  void setFalled(bool fal);
private:
  void do_draw();
  void do_animate(float time);
  KeyframeCollection m_localKeyframes; /*!< A collection of keyframes for the local transformation of renderable. */
  KeyframeCollection m_parentKeyframes; /*!< A collection of keyframes for the parent transformation of renderable. */
  bool existe;
  glm::vec3 position = glm::vec3(0,0,0);
  ParticlePtr particle_liee = nullptr;
  bool falled = false;
};

typedef std::shared_ptr<BonhommeDeNeige> BonhommeDeNeigePtr;

#endif
