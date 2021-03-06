#include "particleengine.h"

ParticleEngine::ParticleEngine() : _varray(sf::Quads, 0)
{
}

void ParticleEngine::createParticleEffect(int partNumber, double x, double y, ParticleTemplate &tplt)
{
    _particleEffects.push_back({partNumber, x, y, tplt});

    int size = _varray.getVertexCount();
    _varray.resize(size+4*partNumber);
}

void ParticleEngine::update(sf::Time dt)
{
    int i(0);
    for (auto &pe : _particleEffects)
    {
        pe.update(dt);
        for (const auto &p : pe.getParticles())
        {
            if (!p.isDead())
            {
                _varray[4*i  ].position = {(float)p.getX()-2, (float)p.getY()-2};
                _varray[4*i+1].position = {(float)p.getX()+2, (float)p.getY()-2};
                _varray[4*i+2].position = {(float)p.getX()+2, (float)p.getY()+2};
                _varray[4*i+3].position = {(float)p.getX()-2, (float)p.getY()+2};
                auto color = p.getColor();
                _varray[4*i  ].color = color;
                _varray[4*i+1].color = color;
                _varray[4*i+2].color = color;
                _varray[4*i+3].color = color;
                i++;
            }
        }
    }
    _varray.resize(4*i);
    for (auto it=_particleEffects.begin(); it!=_particleEffects.end();)
    {
        if (it->isDead())
            it = _particleEffects.erase(it);
        else it++;
    }
}

void ParticleEngine::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_varray, states);
}
