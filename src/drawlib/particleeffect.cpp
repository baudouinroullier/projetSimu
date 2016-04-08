#include "particleeffect.h"
#include <random>
#include <array>

ParticleEffect::ParticleEffect(int numberOfParticles, double x, double y)
{
    std::default_random_engine generator;
    std::normal_distribution<double> vDist(0.,200.), lifeTimeDist(.3,0.05);

    _particles.reserve(numberOfParticles);
    for (int i=numberOfParticles; i; i--)
    {
        double vtheta = (double)(rand()%3600)/10.;
        double vr = vDist(generator);

        _particles.push_back({x, y, vr*cos(vtheta), vr*sin(vtheta)-400, sf::seconds(lifeTimeDist(generator)),
                              [](double, double, double vx, double vy, sf::Time)->std::array<double,2>{return {-2*vx, -2*vy+2000};},
                              [](double, double, double vx, double vy, sf::Time t)->sf::Color{return {255, std::min<int>(2*sqrt(t.asSeconds())*sqrt(vx*vx+vy*vy),255), 0};} });
    }
}

void ParticleEffect::update(sf::Time dt)
{
    for (auto &p : _particles)
        p.update(dt);
}

bool ParticleEffect::isOver()
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
