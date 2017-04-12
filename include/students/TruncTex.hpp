#ifndef TRUNCTEX_HPP
#define TRUNCTEX_HPP

#include "../HierarchicalRenderable.hpp"
#include "./../lighting/Materiable.hpp"
#include <vector>
#include <glm/glm.hpp>

class TruncTex : public HierarchicalRenderable, public Materiable
{
    public:
        ~TruncTex();
        TruncTex(ShaderProgramPtr program,
                  const std::string& textureFilename,
                  const MaterialPtr& material = Material::Neige());
        void do_draw();
        void do_animate(float time);
        void supprimer();
    private:

      std::vector< glm::vec3 > m_positions;
      std::vector< glm::vec4 > m_colors;
      std::vector< glm::vec3 > m_normals;
      std::vector <glm::vec2> m_texCoords;

      unsigned int m_pBuffer;
      unsigned int m_cBuffer;
      unsigned int m_nBuffer;
      unsigned int m_tBuffer;
      unsigned int m_texId;

      MaterialPtr m_material;
};

typedef std::shared_ptr<TruncTex> TruncTexPtr;

#endif
