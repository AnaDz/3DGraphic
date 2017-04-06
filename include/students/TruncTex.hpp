#ifndef TRUNCTEX_HPP
#define TRUNCTEX_HPP

#include "../HierarchicalRenderable.hpp"
#include "./../lighting/Material.hpp"
#include <vector>
#include <glm/glm.hpp>

class TruncTex : public HierarchicalRenderable
{
    public:
        ~TruncTex();
        TruncTex( ShaderProgramPtr program , const std::string& textureFilename);
        void do_draw();
        void do_animate(float time);
        void setMaterial(const MaterialPtr& material);
    private:


        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec2> m_texCoords;


        unsigned int m_pBuffer;
        unsigned int m_nBuffer;
        unsigned int m_tBuffer;
        unsigned int m_texId;

        MaterialPtr m_material;
};

typedef std::shared_ptr<TruncTex> TruncTexPtr;

#endif
