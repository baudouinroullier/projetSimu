#include "animatedsprite.h"


AnimatedSprite::AnimatedSprite(std::string fileName, sf::Time delay) : _varray(sf::Quads, 4), _x(32), _y(32), _angle(0)
{
    _textures.loadFromFile(fileName);
    auto framesSize = _textures.getSize();
    unsigned int width = framesSize.x, height = framesSize.y;

    if (height != 64 || width%64)
        throw std::logic_error("Animation texture size is not correct.");

    int nFrames = width/64;
    for (unsigned int i=0; i<nFrames; i++)
        _orderAndDelay.push_back({i,delay});

    _totalTime = delay*(float)nFrames;

    updateAnimation({});
    updatePosition();
}

AnimatedSprite::AnimatedSprite(std::string fileName, AnimationSteps &steps) : _varray(sf::Quads, 4), _orderAndDelay(steps), _x(32), _y(32), _angle(0)
{
    _textures.loadFromFile(fileName);
    auto framesSize = _textures.getSize();
    unsigned int width = framesSize.x, height = framesSize.y;

    if (height != 64 || width%64)
        throw std::logic_error("Animation texture size is not correct.");

    for (auto p : _orderAndDelay)
        _totalTime += p.second;

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

void AnimatedSprite::updateAnimation(sf::Time dt)
{
    _clock += dt;
    if (_clock >= _totalTime)
        _clock -= _totalTime;

    sf::Time cumulatedTime{_orderAndDelay[0].second};
    float frameNumber = 0;
    while (cumulatedTime <= _clock)
    {
        frameNumber++;
        cumulatedTime += _orderAndDelay[frameNumber].second;
    }

    _varray[0].texCoords = {64*(float)_orderAndDelay[frameNumber].first,0};
    _varray[1].texCoords = {64*(float)_orderAndDelay[frameNumber].first+64,0};
    _varray[2].texCoords = {64*(float)_orderAndDelay[frameNumber].first+64,64};
    _varray[3].texCoords = {64*(float)_orderAndDelay[frameNumber].first,64};
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_varray, &_textures);
}

void AnimatedSprite::updatePosition()
{
    float c = cos(_angle), s = sin(_angle);
    _varray[0].position = {-c*32 - s*32 + _x,  s*32 - c*32 + _y};
    _varray[1].position = { c*32 - s*32 + _x, -s*32 - c*32 + _y};
    _varray[2].position = { c*32 + s*32 + _x, -s*32 + c*32 + _y};
    _varray[3].position = {-c*32 + s*32 + _x,  s*32 + c*32 + _y};
}
