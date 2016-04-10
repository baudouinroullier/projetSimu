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

    sf::Clock clock;

    /****** TESTING PARTICLE EFFECTS ******/
    ParticleEngine partMotor;
    ParticleTemplate partTpltSparks([]()->double{return 0;}, []()->double{return 0;},
                                    []()->double{return ParticleTemplate::normalDist(0.,200.);}, []()->double{return ParticleTemplate::uniformDist(0.,2*M_PI);},
                                    []()->sf::Time{return sf::seconds(ParticleTemplate::normalDist(.1,.2));},
                                    [](double, double, double vx, double vy, sf::Time)->std::array<double,2>{return {-2*vx, -2*vy+2000};},
                                    [](double, double, double vx, double vy, sf::Time t)->sf::Color{return {255, std::min<int>(2*sqrt(t.asSeconds())*sqrt(vx*vx+vy*vy),255), std::min<int>(4*pow(t.asSeconds(),2.)*sqrt(vx*vx+vy*vy),255)};} );

    ParticleTemplate partTpltRain([]()->double{return ParticleTemplate::uniformDist(-2000,1000);}, []()->double{return ParticleTemplate::uniformDist(-2000,1000);},
                                  []()->double{return ParticleTemplate::normalDist(200,0);}, []()->double{return ParticleTemplate::normalDist(M_PI/3.,0);},
                                  []()->sf::Time{return sf::seconds(ParticleTemplate::normalDist(8,0));},
                                  [](double, double, double, double, sf::Time)->std::array<double,2>{return {0,0};},
                                  [](double, double, double vx, double vy, sf::Time t)->sf::Color{return {100, 200, 255};} );

    /**************************************/

    // main loop, TODO: move elsewhere
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
                    partMotor.createParticleEffect(100, 256,256, partTpltSparks);
                if (event.key.code == sf::Keyboard::B)
                    partMotor.createParticleEffect(2000, 256,256, partTpltRain);
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
        partMotor.update(elapsedTime);
        /**********************************/

        /****** DISPLAY EVERYTHING ******/
        window.clear();
        window.draw(partMotor);
        window.display();
        /********************************/
    }

    return 0;
}
