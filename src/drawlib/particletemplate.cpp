#include "particletemplate.h"

ParticleTemplate::ParticleTemplate(std::function<double(void)> x,
                                   std::function<double(void)> y,
                                   std::function<double(void)> v,
                                   std::function<double(void)> theta,
                                   std::function<sf::Time(void)> lifeTime,
                                   std::function<std::array<double,2>(double, double, double, double, sf::Time)> accelerationModel,
                                   std::function<sf::Color(double, double, double, double, sf::Time)> colorModel) :
    _x(x), _y(y), _v(v), _theta(theta), _lifeTime(lifeTime), _accelerationModel(accelerationModel), _colorModel(colorModel)
{
}

double ParticleTemplate::x() const
{
    return _x();
}

double ParticleTemplate::y() const
{
    return _y();
}

double ParticleTemplate::v() const
{
    return _v();
}

double ParticleTemplate::theta() const
{
    return _theta();
}

sf::Time ParticleTemplate::lifeTime() const
{
    return _lifeTime();
}

std::function<std::array<double,2> (double, double, double, double, sf::Time)> ParticleTemplate::accelerationModel() const
{
    return _accelerationModel;
}

std::function<sf::Color (double, double, double, double, sf::Time)> ParticleTemplate::colorModel() const
{
    return _colorModel;
}

std::function<double(void)> ParticleTemplate::normalDist(double mean, double stddev)
{
    static std::default_random_engine generator;
    return [mean, stddev]()
    {
        std::normal_distribution<double> normalDist(mean, stddev);
        return normalDist(generator);
    };
}

std::function<double(void)> ParticleTemplate::uniformDist(double a, double b)
{
    static std::default_random_engine generator;
    return [a,b]()
    {
        std::uniform_real_distribution<double> uniformDist(a,b);
        return uniformDist(generator);
    };
}
