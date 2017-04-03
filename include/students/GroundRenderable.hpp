/*
 * GroundRenderable.hpp
 *
 *  Created on: Mar 30, 2017
 *      Author: mariono
 */

#ifndef AJOUTS_PROJET_GROUNDRENDERABLE_HPP_
#define AJOUTS_PROJET_GROUNDRENDERABLE_HPP_

#include <vector>
#include <glm/glm.hpp>
#include "../HierarchicalRenderable.hpp"

class GroundRenderable : public HierarchicalRenderable
{
public:
    ~GroundRenderable();
    GroundRenderable(ShaderProgramPtr program, int x, int y, int n);

protected:
    void do_draw();
    void do_animate(float time);

    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::ivec3> m_indices;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;
    unsigned int m_iBuffer;
};

typedef std::shared_ptr<GroundRenderable> GroundRenderablePtr;



#endif /* AJOUTS_PROJET_GROUNDRENDERABLE_HPP_ */
