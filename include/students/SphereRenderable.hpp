#ifndef SPHERE_RENDERABLE_HPP
#define SPHERE_RENDERABLE_HPP

#include "../../include/HierarchicalRenderable.hpp"
#include "./../lighting/Materiable.hpp"

#include <vector>
#include <glm/glm.hpp>

class SphereRenderable : public HierarchicalRenderable, public Materiable {
public:
  ~SphereRenderable();
  SphereRenderable(ShaderProgramPtr program,
                    const MaterialPtr& material = Material::Neige(),
                    const std::string& textureFilename = "../textures/snow.png");
  void do_draw();

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

typedef std::shared_ptr<SphereRenderable> SphereRenderablePtr;

#endif
