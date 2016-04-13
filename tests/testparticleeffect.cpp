#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "../src/drawlib/particleengine.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Projet Simu!");  // create window
    window.setVerticalSyncEnabled(true);
    auto wndSize = window.getSize();
    sf::View view({0,0, (float)wndSize.x, (float)wndSize.y});
    window.setView(view);


    /****** TESTING PARTICLE EFFECTS ******/
    ParticleEngine partEngine;
    ParticleTemplate partTpltSparks([](){return 0;}, [](){return 0;},
                                    ParticleTemplate::normalDist(0.,200.), ParticleTemplate::uniformDist(0.,2*M_PI),
                                    [](){return sf::seconds(ParticleTemplate::normalDist(.1,.2)());},
                                    [](double, double, double vx, double vy, sf::Time)->std::array<double,2>{return {-2*vx, -2*vy+2000};},
                                    [](double, double, double vx, double vy, sf::Time t)->sf::Color{return {255, std::min<sf::Uint8>(2*sqrt(t.asSeconds())*sqrt(vx*vx+vy*vy),255), std::min<sf::Uint8>(4*pow(t.asSeconds(),2.)*sqrt(vx*vx+vy*vy),255)};} );

    ParticleTemplate partTpltRain(ParticleTemplate::uniformDist(-2000,1024), ParticleTemplate::uniformDist(-4000,768),
                                  ParticleTemplate::normalDist(600,10), ParticleTemplate::normalDist(M_PI/3.,M_PI/100.),
                                  [](){return sf::seconds(ParticleTemplate::normalDist(6,1)());},
                                  [](double, double, double, double, sf::Time)->std::array<double,2>{return {0,0};},
                                  [](double, double, double, double, sf::Time)->sf::Color{return {100, 200, 255};} );

    ParticleTemplate partTpltFirework([](){return 0;}, [](){return 0;},
                                  ParticleTemplate::normalDist(300,150), ParticleTemplate::uniformDist(0.,2*M_PI),
                                  [](){return sf::seconds(ParticleTemplate::normalDist(1.2,.5)());},
                                  [](double, double, double vx, double vy, sf::Time)->std::array<double,2>{return { -2*vx, 100-2*vy};},
                                  [](double, double, double, double, sf::Time t)->sf::Color{return {255*pow(t.asSeconds(),0.25), 255*pow(t.asSeconds(),0.25), 255*pow(1-t.asSeconds(),0.25)};} );
    /**************************************/

    sf::Clock clock;

    while (window.isOpen())
    {
        /****** MANAGING EVENTS ******/
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space)
                    partEngine.createParticleEffect(20, 256,256, partTpltSparks);
                if (event.key.code == sf::Keyboard::B)
                    partEngine.createParticleEffect(3000, 0,0, partTpltRain);
                if (event.key.code == sf::Keyboard::N)
                    partEngine.createParticleEffect(1000, 512,200, partTpltFirework);
            }

            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
        }
        /*****************************/


        /****** UPDATE TIMES THINGS ******/
        auto elapsedTime = clock.restart();
        partEngine.update(elapsedTime);
        /**********************************/

        /****** DISPLAY EVERYTHING ******/
        window.clear();
        window.draw(partEngine);
        window.display();
        /********************************/
    }

    return 0;
}
