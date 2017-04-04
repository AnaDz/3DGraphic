#ifndef CONE_RENDERABLE_HPP
#define CONE_RENDERABLE_HPP

#include "../../include/HierarchicalRenderable.hpp"
#include "./../lighting/Materiable.hpp"

#include <vector>
#include <glm/glm.hpp>

class ConeRenderable : public HierarchicalRenderable, public Materiable {
public:
  ~ConeRenderable();
  ConeRenderable(ShaderProgramPtr program, glm::vec4 couleur,
                    const MaterialPtr& material = Material::Snow());
  void do_draw();

private:
  void do_animate(float time);

  std::vector< glm::vec3 > m_positions;
  std::vector< glm::vec4 > m_colors;
  std::vector< glm::vec3 > m_normals;

  unsigned int m_pBuffer;
  unsigned int m_cBuffer;
  unsigned int m_nBuffer;

};

typedef std::shared_ptr<ConeRenderable> ConeRenderablePtr;

#endif
