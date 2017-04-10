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
#include "../../include/students/SphereRenderable.hpp"




class SnowballRenderable : public ParticleRenderable
{
public:
    ~SnowballRenderable();
    SnowballRenderable(ShaderProgramPtr program, Viewer* v, ParticlePtr particle);
    void do_keyPressedEvent(sf::Event& e);
    void do_keyReleasedEvent(sf::Event& e);
private:
    void do_draw();
    void do_animate(float time);

    Viewer *viewer;

    bool gauche;
    bool droite;
    bool toutDroit;

};

typedef std::shared_ptr<SnowballRenderable> SnowballRenderablePtr;




#endif /* INCLUDE_STUDENTS_SNOWBALLRENDERABLE_HPP_ */
