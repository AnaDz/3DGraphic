#include "./../../include/dynamics/EulerExplicitSolver.hpp"

EulerExplicitSolver::EulerExplicitSolver()
{

}

EulerExplicitSolver::~EulerExplicitSolver()
{

}

void EulerExplicitSolver::do_solve(const float& dt, std::vector<ParticlePtr>& particles)
{
    for (ParticlePtr p : particles) {
        if (!p->isFixed()) {
            //TODO: Implement explicit euler solver
            //Functions to use:
            //Particle::getPosition(), Particle::getVelocity(), Particle::getMass(), Particle::getForce()
            //Particle::setPosition(), Particle::setVelocity()
            glm::vec3 new_velocity = p->getVelocity() + 1/p->getMass()*dt*p->getForce();
            glm::vec3 new_position = p->getPosition() + dt*new_velocity;
            p->setPosition(new_position);
            p->setVelocity(new_velocity);
        }
    }
}
