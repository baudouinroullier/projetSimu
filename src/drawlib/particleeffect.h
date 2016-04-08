#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.h"


class ParticleEffect
{
public:
    ParticleEffect(int numberOfParticles, double x, double y);

    void update(sf::Time dt);
    bool isOver();

    std::vector<Particle> getParticles() const;

private:
    std::vector<Particle> _particles;

};

#endif // PARTICLEEFFECT_H
