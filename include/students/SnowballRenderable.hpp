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
#include "../students/ParticleRenderableStudent.hpp"
#include "../dynamics/Particle.hpp"
#include "../Viewer.hpp"
#include "./../lighting/Materiable.hpp"
#include "../../include/students/SphereRenderable.hpp"
#include "../../include/students/GroundRenderable.hpp"



class SnowballRenderable : public ParticleRenderableStudent
{
public:
    ~SnowballRenderable();
    SnowballRenderable(ShaderProgramPtr program, Viewer* v, ParticlePtr particle, std::shared_ptr<SphereRenderable> sky);
    void do_keyPressedEvent(sf::Event& e);
    void do_keyReleasedEvent(sf::Event& e);
    std::shared_ptr<SphereRenderable> skybox;
private:
    void do_draw();
    void do_animate(float time);

    Viewer *viewer;

    bool gauche;
    bool droite;
    bool toutDroit;

    //nx = 6; ny=75;
    GroundRenderablePtr groundR[6][75];


};

typedef std::shared_ptr<SnowballRenderable> SnowballRenderablePtr;




#endif /* INCLUDE_STUDENTS_SNOWBALLRENDERABLE_HPP_ */
