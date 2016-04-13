#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.h"
#include "particletemplate.h"


class ParticleEffect
{
public:
    ParticleEffect(int numberOfParticles, double x, double y, const ParticleTemplate &tplt);

    void update(sf::Time dt);
    bool isDead() const;

    std::vector<Particle> getParticles() const;

private:
    std::vector<Particle> _particles;
};

#endif // PARTICLEEFFECT_H
