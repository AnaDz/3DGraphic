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
    Explosion(DynamicSystemPtr system, DynamicSystemRenderablePtr systemRenderable, ShaderProgramPtr phongShader, glm::vec3 position = glm::vec3(0,0,0), double radius = 0.5);

    std::vector<std::vector<ParticlePtr>> listePart;
};
typedef std::shared_ptr<Explosion> ExplosionPtr;
#endif
