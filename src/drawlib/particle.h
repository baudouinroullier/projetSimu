#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <array>
#include <functional>


class Particle
{
public:
    Particle(double x, double y, double vx, double vy, sf::Time lifeTime,
             std::function<std::array<double,2>(double, double, double, double, sf::Time)> accelerationModel,
             std::function<sf::Color(double, double, double, double, sf::Time)> colorModel );

    void update(sf::Time dt);

    double getX() const;
    double getY() const;
    sf::Color getColor();

    bool isOver();

private:
    double _x, _y;
    double _vx, _vy;
    sf::Time _lifeTime;

    std::function<std::array<double,2>(double, double, double, double, sf::Time)> _accelerationModel;
    std::function<sf::Color(double, double, double, double, sf::Time)> _colorModel;
};

#endif // PARTICLE_H
