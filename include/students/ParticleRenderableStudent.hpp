#ifndef PARTICLE_RENDERABLE_STUDENT_HPP
#define PARTICLE_RENDERABLE_STUDENT_HPP

#include "../HierarchicalRenderable.hpp"
#include "../dynamics/Particle.hpp"
#include "./../lighting/Materiable.hpp"

#include <vector>
#include <glm/glm.hpp>

/**@brief Render a particle to the screen.
 *
 * Render a particle to the screen. Since a particle is modeled by
 * a ball, this renderable simply render the corresponding ball. If
 * you have more than one renderable, have a look to ParticleListRenderable.
 */
class ParticleRenderableStudent : public HierarchicalRenderable, public Materiable
{
    public:
        /**@brief Build a particle renderable.
         *
         * Build a renderable to render a particle.
         * @param program The shader program used to render the particle.
         * @param particle The particle to render.
         */
        ParticleRenderableStudent(ShaderProgramPtr program,
                            ParticlePtr particle,
                            const MaterialPtr& material = Material::Neige(),
                            const std::string& textureFilename = "../textures/snow.png");

        ~ParticleRenderableStudent();

    protected:
        void do_draw();
        void do_animate(float time);

        ParticlePtr m_particle;

        size_t m_numberOfVertices;
        std::vector< glm::vec3 > m_positions;
        std::vector< glm::vec4 > m_colors;
        std::vector< glm::vec3 > m_normals;
        std::vector <glm::vec2> m_texCoords;

        unsigned int m_pBuffer;
        unsigned int m_cBuffer;
        unsigned int m_nBuffer;
        unsigned int m_tBuffer;
        unsigned int m_texId;
};

typedef std::shared_ptr<ParticleRenderableStudent> ParticleRenderableStudentPtr;

#endif //PARTICLE_RENDERABLE_STUDENT_HPP
