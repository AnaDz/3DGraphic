#ifndef CYLINDER_RENDERABLE_HPP
#define CYLINDER_RENDERABLE_HPP

#include "../../include/HierarchicalRenderable.hpp"
#include "./../lighting/Materiable.hpp"

#include <vector>
#include <glm/glm.hpp>

class CylinderRenderable : public HierarchicalRenderable, public Materiable {
public:
  ~CylinderRenderable();
  CylinderRenderable(ShaderProgramPtr program,
                    const MaterialPtr& material = Material::TissuNoir(),
                    const std::string& textureFilename = "");
  void do_draw();
  void supprimer();

private:
  void do_animate(float time);

  std::vector< glm::vec3 > m_positions;
  std::vector< glm::vec4 > m_colors;
  std::vector< glm::vec3 > m_normals;
  std::vector <glm::vec2> m_texCoords;

  unsigned int m_pBuffer;
  unsigned int m_cBuffer;
  unsigned int m_nBuffer;
  unsigned int m_tBuffer;
  unsigned int m_texId;

};

typedef std::shared_ptr<CylinderRenderable> CylinderRenderablePtr;

#endif
