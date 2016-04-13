#include "animatedsprite.h"
#include "../tinyxml2/tinyxml2.h"


AnimatedSprite::AnimatedSprite(std::string XMLFileName)
{

}

AnimatedSprite::AnimatedSprite(std::string fileName, sf::Time delay) : _varray(sf::Quads, 4), _x(32), _y(32), _angle(0)
{
    _textures.loadFromFile(fileName);
    auto framesSize = _textures.getSize();
    unsigned int width = framesSize.x, height = framesSize.y;

    if (height != 64 || width%64)
        throw std::logic_error("Animation texture size is not correct.");

    int nFrames = width/64;
    for (unsigned int i=0; i<nFrames; i++)
        _currentSteps.push_back({i,delay});

    _totalTime = delay*(float)nFrames;

    updateAnimation({});
    updatePosition();
}

AnimatedSprite::AnimatedSprite(std::string fileName, const AnimationSteps &steps) : _varray(sf::Quads, 4), _x(32), _y(32), _angle(0), _currentSteps(steps)
{
    _textures.loadFromFile(fileName);
    auto framesSize = _textures.getSize();
    unsigned int width = framesSize.x, height = framesSize.y;

    if (height != 64 || width%64)
        throw std::logic_error("Animation texture size is not correct.");

    for (auto p : _currentSteps)
        _totalTime += p.second;

    updateAnimation({});
    updatePosition();
}

AnimatedSprite::AnimatedSprite(std::string fileName, const MultiAnimationSteps &multisteps): _varray(sf::Quads, 4), _multiSteps(multisteps), _x(32), _y(32), _angle(0), _totalTime(sf::milliseconds(100))
{
    _textures.loadFromFile(fileName);
    auto framesSize = _textures.getSize();
    unsigned int width = framesSize.x, height = framesSize.y;

    if (height != 64 || width%64)
        throw std::logic_error("Animation texture size is not correct.");

    // use first frame forever as default
    _currentSteps.push_back({0,sf::milliseconds(100)});

    updateAnimation({});
    updatePosition();
}

void AnimatedSprite::setPosition(double x, double y)
{
    _x = (float)x;
    _y = (float)y;

    updatePosition();
}

void AnimatedSprite::setRotation(double angle)
{
    _angle = angle;
    updatePosition();
}

void AnimatedSprite::move(double dx, double dy)
{
    setPosition(_x+(float)dx, _y+(float)dy);
}

void AnimatedSprite::rotate(double dangle)
{
    setRotation(_angle+dangle);
}

std::vector<float> AnimatedSprite::getPosition() const
{
    return {_x,_y};
}

void AnimatedSprite::chooseAnimation(std::string name)
{
    try { _currentSteps = _multiSteps.at(name); }
    catch (const std::out_of_range& oor) {
      throw std::logic_error("\"" + name + "\" is not a valid animation name.");
    }
    // compute total time of the chosen animation
    _totalTime = sf::Time::Zero;
    for (auto p : _currentSteps)
        _totalTime += p.second;
}

void AnimatedSprite::updateAnimation(sf::Time dt)
{
    _currentTime += dt;
    if (_currentTime >= _totalTime)
        _currentTime -= _totalTime;

    sf::Time cumulatedTime{_currentSteps[0].second};
    int frameNumber = 0;
    while (cumulatedTime <= _currentTime)
    {
        frameNumber++;
        cumulatedTime += _currentSteps[frameNumber].second;
    }

    _varray[0].texCoords = {64*(float)_currentSteps[frameNumber].first,0};
    _varray[1].texCoords = {64*(float)_currentSteps[frameNumber].first+64,0};
    _varray[2].texCoords = {64*(float)_currentSteps[frameNumber].first+64,64};
    _varray[3].texCoords = {64*(float)_currentSteps[frameNumber].first,64};
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = &_textures;
    target.draw(_varray, states);
}

void AnimatedSprite::updatePosition()
{
    float c = cos(_angle), s = sin(_angle);
    _varray[0].position = {-c*32 - s*32 + _x,  s*32 - c*32 + _y};
    _varray[1].position = { c*32 - s*32 + _x, -s*32 - c*32 + _y};
    _varray[2].position = { c*32 + s*32 + _x, -s*32 + c*32 + _y};
    _varray[3].position = {-c*32 + s*32 + _x,  s*32 + c*32 + _y};
}
