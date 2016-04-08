#ifndef PARTICLEMOTOR_H
#define PARTICLEMOTOR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "particleeffect.h"


class ParticleMotor : public sf::Drawable
{
public:
    ParticleMotor();

    void createParticleEffect(int partNumber, double x, double y);

    void update(sf::Time dt);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::VertexArray _varray;
    std::vector<ParticleEffect> _particleEffects;
};

#endif // PARTICLEMOTOR_H
