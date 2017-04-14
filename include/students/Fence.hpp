#ifndef FENCE_HPP
#define  FENCE_HPP
#include "../../include/HierarchicalRenderable.hpp"
#include "../../include/students/ConeRenderable.hpp"
#include "./../lighting/Material.hpp"
#include "CylinderRenderable.hpp"
#include "../Viewer.hpp"

#include <vector>
#include <glm/glm.hpp>

class Fence : public HierarchicalRenderable{
public:
  Fence(ShaderProgramPtr program, const std::string& textureFilename);
  ~Fence();
  std::shared_ptr<CylinderRenderable> origin;

private:
  void do_draw();
  void do_animate(float time);
  MaterialPtr m_material = Material::Neige();

};

typedef std::shared_ptr<Fence> FencePtr;

#endif
