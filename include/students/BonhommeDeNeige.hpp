#ifndef BONHOMME_DE_NEIGE_HPP
#define BONHOMME_DE_NEIGE_HPP

#include "../../include/HierarchicalRenderable.hpp"
#include "../../include/students/SphereRenderable.hpp"
#include "../../include/students/CylinderRenderable.hpp"
#include "../../include/students/ConeRenderable.hpp"

#include <vector>
#include <glm/glm.hpp>

class BonhommeDeNeige : public HierarchicalRenderable {
public:
  BonhommeDeNeige(ShaderProgramPtr program);
  std::shared_ptr<SphereRenderable> base;

private:
  void do_draw();
  void do_animate(float time);

};

typedef std::shared_ptr<BonhommeDeNeige> BonhommeDeNeigePtr;

#endif
