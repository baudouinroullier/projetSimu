#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>


typedef std::vector<std::pair<unsigned int, sf::Time>> AnimationSteps;
typedef std::unordered_map<std::string, std::vector<std::pair<unsigned int, sf::Time>>> MultiAnimationSteps;


class AnimatedSprite : public sf::Drawable
{
public:
    AnimatedSprite(std::string fileName, sf::Time delay);
    AnimatedSprite(std::string fileName, const AnimationSteps &steps);
    AnimatedSprite(std::string fileName, const MultiAnimationSteps &multisteps);

    void setPosition(double x, double y);
    void setRotation(double angle);
    void move(double dx, double dy);
    void rotate(double dangle);

    std::vector<float> getPosition();

    void chooseAnimation(std::string name);
    void updateAnimation(sf::Time dt);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // display variables
    sf::Texture _textures;
    sf::VertexArray _varray;

    // animation time variables
    MultiAnimationSteps _multiSteps;
    AnimationSteps _currentSteps;
    sf::Time _currentTime, _totalTime;

    // placement and rotation variables
    float _x, _y;  // position of top left corner
    double _angle;  // rotation around center
    void updatePosition();
};

#endif // ANIMATEDSPRITE_H
