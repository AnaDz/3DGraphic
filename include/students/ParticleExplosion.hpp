#ifndef ParticleExplosion_HPP
#define ParticleExplosion_HPP

#include <vector>
#include <glm/glm.hpp>
#include "../dynamics_rendering/ParticleRenderable.hpp"
#include "../dynamics/Particle.hpp"
#include "../Viewer.hpp"
#include "./../lighting/Materiable.hpp"

class ParticleExplosion : public ParticleRenderable
{
public:
    ~ParticleExplosion();
    ParticleExplosion(ShaderProgramPtr program, const MaterialPtr& material, ParticlePtr particle);

protected:
    void do_draw();
    void do_animate(float time);

    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec3> m_normals;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;


};

typedef std::shared_ptr<ParticleExplosion> ParticleExplosionPtr;

#endif
