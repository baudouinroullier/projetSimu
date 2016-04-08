#ifndef PARTICLETEMPLATE_H
#define PARTICLETEMPLATE_H

#include <SFML/Graphics.hpp>
#include <random>
#include <functional>
#include <array>


class ParticleTemplate
{
public:
    ParticleTemplate(std::function<double(void)> x,
                     std::function<double(void)> y,
                     std::function<double(void)> v,
                     std::function<double(void)> theta,
                     std::function<sf::Time(void)> lifeTime,
                     std::function<std::array<double,2>(double, double, double, double, sf::Time)> accelerationModel,
                     std::function<sf::Color(double, double, double, double, sf::Time)> colorModel);

    double x();
    double y();
    double v();
    double theta();
    sf::Time lifeTime();
    std::function<std::array<double,2>(double, double, double, double, sf::Time)> accelerationModel();
    std::function<sf::Color(double, double, double, double, sf::Time)> colorModel();

    static double normalDist(double mean, double stddev);
    static double uniformDist(double a, double b);

private:

    std::function<double(void)> _x, _y, _v, _theta;
    std::function<sf::Time(void)> _lifeTime;
    std::function<std::array<double,2>(double, double, double, double, sf::Time)> _accelerationModel;
    std::function<sf::Color(double, double, double, double, sf::Time)> _colorModel;
};


#endif // PARTICLETEMPLATE_H
