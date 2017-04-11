#ifndef Explosion_HPP
#define Explosion_HPP

#include <vector>
#include <glm/glm.hpp>
#include "../students/ParticleRenderableStudent.hpp"
#include "../dynamics/Particle.hpp"
#include "../Viewer.hpp"
#include "./../lighting/Materiable.hpp"
#include "../dynamics/DynamicSystem.hpp"
#include "../dynamics_rendering/DynamicSystemRenderable.hpp"

class Explosion
{
public:
    ~Explosion();
    Explosion(DynamicSystemPtr system, DynamicSystemRenderablePtr systemRenderable, ShaderProgramPtr phongShader);

};

#endif
