/*
 * SnowBall.hpp
 *
 *  Created on: Apr 4, 2017
 *      Author: mariono
 */

#ifndef INCLUDE_STUDENTS_SNOWBALLRENDERABLE_HPP_
#define INCLUDE_STUDENTS_SNOWBALLRENDERABLE_HPP_

#include <vector>
#include <glm/glm.hpp>
#include "../dynamics_rendering/ParticleRenderable.hpp"
#include "../dynamics/Particle.hpp"
#include "../Viewer.hpp"
#include "./../lighting/Materiable.hpp"
//doit surement étendre le particleRenderable en fait ^^
class SnowballRenderable : public ParticleRenderable, public Materiable
{
public:
    ~SnowballRenderable();
    SnowballRenderable(ShaderProgramPtr program, const MaterialPtr& material, Viewer* v, ParticlePtr particle);

protected:
    void do_draw();
    void do_animate(float time);

    Viewer *viewer;
    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec3> m_normals;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;


};

typedef std::shared_ptr<SnowballRenderable> SnowballRenderablePtr;



#endif /* INCLUDE_STUDENTS_SNOWBALLRENDERABLE_HPP_ */
