#ifndef TREE_HPP
#define  TREE_HPP
#include "../../include/HierarchicalRenderable.hpp"
#include "../../include/students/TruncTex.hpp"
#include "../../include/students/ConeRenderable.hpp"
#include "./../lighting/Material.hpp"
#include "../dynamics_rendering/ParticleRenderable.hpp"
#include "../dynamics/Particle.hpp"
#include "../dynamics/DynamicSystem.hpp"
#include "../dynamics_rendering/DynamicSystemRenderable.hpp"
#include "../../include/keyframes/KeyframeCollection.hpp"
#include "../Viewer.hpp"

#include <vector>
#include <glm/glm.hpp>

class Tree : public HierarchicalRenderable{
public:
  Tree(ShaderProgramPtr program, const std::string& textureFilename, const std::string& textureFilename2="");
  ~Tree();
  std::shared_ptr<TruncTex> tronc;
  void addParentTransformKeyframe(float time, const GeometricTransformation& transformation);
  void addLocalTransformKeyframe(float time, const GeometricTransformation& transformation);
  void generateAnimation(float time);
private:
  void do_draw();
  void do_animate(float time);
  KeyframeCollection m_localKeyframes; /*!< A collection of keyframes for the local transformation of renderable. */
  KeyframeCollection m_parentKeyframes; /*!< A collection of keyframes for the parent transformation of renderable. */


  MaterialPtr m_material = Material::Neige();

};

typedef std::shared_ptr<Tree> TreePtr;

#endif
