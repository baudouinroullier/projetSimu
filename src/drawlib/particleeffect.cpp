#include "particleeffect.h"
#include <random>
#include <array>

ParticleEffect::ParticleEffect(int numberOfParticles, double x, double y, ParticleTemplate &tplt)
{
    _particles.reserve(numberOfParticles);
    for (int i=numberOfParticles; i; i--)
    {
        _particles.push_back({x+tplt.x(), y+tplt.y(), tplt.v(), tplt.theta(), tplt.lifeTime(), tplt.accelerationModel(), tplt.colorModel()});
    }
}

void ParticleEffect::update(sf::Time dt)
{
    for (auto &p : _particles)
        p.update(dt);
}

bool ParticleEffect::isOver() const
{
    for (auto& p : _particles)
        if (!p.isOver())
            return false;
    return true;
}

std::vector<Particle> ParticleEffect::getParticles() const
{
    return _particles;
}
