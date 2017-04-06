#ifndef TREE_HPP
#define  TREE_HPP
#include "../../include/HierarchicalRenderable.hpp"
#include "../../include/students/TruncTex.hpp"
#include "../../include/students/ConeRenderable.hpp"
#include "./../lighting/Material.hpp"
#include <vector>
#include <glm/glm.hpp>

class Tree: public HierarchicalRenderable{
public:
  Tree(ShaderProgramPtr program, const std::string& textureFilename);
  ~Tree();
  std::shared_ptr<TruncTex> tronc;

private:
  void do_draw();
  void do_animate(float time);

  MaterialPtr m_material = Material::Emerald();

};  

typedef std::shared_ptr<Tree> TreePtr;

#endif
