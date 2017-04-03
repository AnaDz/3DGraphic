#include "./../../include/dynamics/SpringForceField.hpp"

SpringForceField::SpringForceField(const ParticlePtr p1, const ParticlePtr p2,
                                   float stiffness, float equilibriumLength,
                                   float damping) :
    m_p1(p1),
    m_p2(p2),
    m_stiffness(stiffness),
    m_equilibriumLength(equilibriumLength),
    m_damping(damping)
{}

void SpringForceField::do_addForce()
{
    //TODO: Implement a damped spring
    //Functions to use:
    //glm::length( vec3 ): Return the length of a vector
    //glm::normalize( vec3 ): Return the normalization of a vector
    //Particle::getVelocity(), Particle::getForce(), Particle::setForce()
    //
    //Nb:   Compute force ONLY IF the displacement length is above std::numeric_limits<float>::epsilon()
    //      Otherwise the computation is useless
    ParticlePtr p1 = this->getParticle1();
    ParticlePtr p2 = this->getParticle2();
    glm::vec3 ecart = p2->getPosition() - p1->getPosition();
    if (std::numeric_limits<float>::epsilon() > glm::length(ecart)) {
      return;
    }
    glm::vec3 fk = -this->m_stiffness * (glm::length(ecart) - this->m_equilibriumLength) * glm::normalize(ecart);
    glm::vec3 fkc = -this->m_damping * glm::dot(p2->getVelocity() - p1->getVelocity(), glm::normalize(ecart))*glm::normalize(ecart);
    p1->setForce(p1->getForce() + -fk-fkc);
    p2->setForce(p2->getForce() + fk+fkc);
}

ParticlePtr SpringForceField::getParticle1() const
{
    return m_p1;
}

ParticlePtr SpringForceField::getParticle2() const
{
    return m_p2;
}
