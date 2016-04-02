#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class AnimatedSprite : public sf::Drawable
{
public:
    AnimatedSprite(std::string fileName, sf::Time delay);
    AnimatedSprite(std::string fileName, std::vector<std::pair<unsigned int, sf::Time>> &orderAndDelay);

    void setPosition(double x, double y);
    void setRotation(double angle);
    void move(double dx, double dy);
    void rotate(double dangle);

    void updateAnimation(sf::Time dt);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // display variables
    sf::Texture _textures;
    sf::VertexArray _varray;

    // animation time variables
    std::vector<std::pair<unsigned int, sf::Time>> _orderAndDelay;
    sf::Time _clock, _totalTime;

    // placement and rotation variables
    float _x, _y;  // position of top left corner
    double _angle;  // rotation around center
    void updatePosition();
};

#endif // ANIMATEDSPRITE_H
