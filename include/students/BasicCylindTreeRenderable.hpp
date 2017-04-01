#ifndef BASIC_CYLIND_TREE_RENDERABLE_HPP
#define BASIC_CYLIND_TREE_RENDERABLE_HPP

#include "../HierarchicalRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>

class BasicCylindTreeRenderable : public HierarchicalRenderable
{
    public:
        ~BasicCylindTreeRenderable();
        BasicCylindTreeRenderable( ShaderProgramPtr program);

    private:
        void do_draw();
        void do_animate(float time);

        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec4> m_colors;
//        std::vector<glm::vec3> m_normals;

        unsigned int m_pBuffer;
  //      unsigned int m_nBuffer;
        unsigned int m_cBuffer;
};

typedef std::shared_ptr<BasicCylindTreeRenderable> BasicCylindTreeRenderablePtr;

#endif
