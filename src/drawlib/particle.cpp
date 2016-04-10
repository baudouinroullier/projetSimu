#include "particle.h"

Particle::Particle(double x, double y, double v, double theta, sf::Time lifeTime,
                   std::function<std::array<double,2>(double, double, double, double, sf::Time)> accelerationModel,
                   std::function<sf::Color(double, double, double, double, sf::Time)> colorModel):
    _x(x), _y(y), _vx(v*cos(theta)), _vy(v*sin(theta)), _lifeTime(lifeTime), _accelerationModel(accelerationModel), _colorModel(colorModel)
{
}

void Particle::update(sf::Time dt)
{
    auto acc = _accelerationModel(_x, _y, _vx, _vy, _lifeTime);
    _vx += acc[0]*dt.asSeconds();
    _vy += acc[1]*dt.asSeconds();
    _x  += _vx*dt.asSeconds();
    _y  += _vy*dt.asSeconds();
    _lifeTime -= dt;
}

double Particle::getX() const
{
    return _x;
}

double Particle::getY() const
{
    return _y;
}

sf::Color Particle::getColor() const
{
    return _colorModel(_x, _y, _vx, _vy, _lifeTime);
}

bool Particle::isOver() const
{
    return _lifeTime <= sf::Time::Zero;
}
