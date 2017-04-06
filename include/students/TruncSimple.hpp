#ifndef TRUNCSIMPLE_HPP
#define TRUNCSIMPLE_HPP

#include "../HierarchicalRenderable.hpp"
#include "./../lighting/Material.hpp"
#include <vector>
#include <glm/glm.hpp>

class TruncSimple : public HierarchicalRenderable
{
    public:
        ~TruncSimple();
        TruncSimple( ShaderProgramPtr program);

    private:
        void do_draw();
        void do_animate(float time);

        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec4> m_colors;


        unsigned int m_pBuffer;
        unsigned int m_nBuffer;
        unsigned int m_cBuffer;

};

typedef std::shared_ptr<TruncSimple> TruncSimplePtr;

#endif
