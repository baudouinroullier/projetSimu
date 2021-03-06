#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "drawlib/map.h"
#include "drawlib/animatedsprite.h"
#include "drawlib/particleengine.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Projet Simu!");  // create window
    window.setVerticalSyncEnabled(true);
    auto wndSize = window.getSize();
    sf::View view({0,0, (float)wndSize.x, (float)wndSize.y});
    window.setView(view);


    /****** TESTING MAPS ******/
    Map map(32,24);

    // tiles for the terrain -> should be read from a level design file
    std::vector<VisualTile> tiles(32*24,VisualTile::EMPTY);
    for (int i=131; i<141; i++)
        tiles[i] = VisualTile::WALL;
    for (int i=259; i<269; i++)
        tiles[i] = VisualTile::GROUND;
    tiles[163] = VisualTile::WALL;
    tiles[172] = VisualTile::WALL;
    tiles[195] = VisualTile::WALL;
    tiles[204] = VisualTile::WINDOW;
    tiles[227] = VisualTile::DOOR;
    tiles[236] = VisualTile::WALL;

    for (int i=503; i<508; i++)
        tiles[i] = VisualTile::WALL;
    for (int i=535; i<540; i++)
        tiles[i] = VisualTile::DOOR;
    for (int i=567; i<572; i++)
        tiles[i] = VisualTile::GROUND;

    // set the tiles we created
    map.setTiles(tiles);
    map.setTile(7,7,VisualTile::DOOR);
    map.update();
    /**************************/

    /****** TESTING ANIMATED SPRITES ******/
    sf::Clock clock;
    /**** single animation ****/
    AnimationSteps steps;
    steps.push_back({0,sf::milliseconds(200)});
    steps.push_back({2,sf::milliseconds(200)});
    steps.push_back({4,sf::milliseconds(200)});
    steps.push_back({6,sf::milliseconds(200)});
    steps.push_back({8,sf::milliseconds(200)});
    steps.push_back({6,sf::seconds(1)});
    steps.push_back({8,sf::seconds(1)});
    steps.push_back({4,sf::seconds(1)});
    steps.push_back({0,sf::seconds(1)});
    steps.push_back({2,sf::seconds(1)});
    AnimatedSprite anime("../img/animated.png", steps);
    anime.move(256,128);

    /**** multi animation ****/
    MultiAnimationSteps multisteps;
    AnimationSteps rightSteps, leftSteps, upSteps, downSteps;
    rightSteps.push_back({0,sf::milliseconds(200)});
    rightSteps.push_back({1,sf::milliseconds(200)});
    rightSteps.push_back({2,sf::milliseconds(200)});
    rightSteps.push_back({3,sf::milliseconds(200)});
    leftSteps.push_back({4,sf::milliseconds(400)});
    leftSteps.push_back({5,sf::milliseconds(600)});
    leftSteps.push_back({6,sf::milliseconds(400)});
    leftSteps.push_back({7,sf::milliseconds(600)});
    upSteps.push_back({8,sf::milliseconds(200)});
    upSteps.push_back({9,sf::milliseconds(200)});
    downSteps.push_back({10,sf::milliseconds(400)});
    downSteps.push_back({11,sf::milliseconds(400)});
    multisteps.insert({"right", rightSteps});
    multisteps.insert({"left", leftSteps});
    multisteps.insert({"up", upSteps});
    multisteps.insert({"down", downSteps});

    AnimatedSprite multianime("../img/multianimated.png", multisteps);
    multianime.move(256,256);

    /**** walking guy ****/
    MultiAnimationSteps multiwalk;
    AnimationSteps rightWalk, leftWalk, upWalk, downWalk;
    downWalk.push_back({0,sf::milliseconds(200)});
    downWalk.push_back({1,sf::milliseconds(200)});
    downWalk.push_back({2,sf::milliseconds(200)});
    downWalk.push_back({1,sf::milliseconds(200)});
    leftWalk.push_back({3,sf::milliseconds(200)});
    leftWalk.push_back({4,sf::milliseconds(200)});
    leftWalk.push_back({5,sf::milliseconds(200)});
    leftWalk.push_back({4,sf::milliseconds(200)});
    rightWalk.push_back({6,sf::milliseconds(200)});
    rightWalk.push_back({7,sf::milliseconds(200)});
    rightWalk.push_back({8,sf::milliseconds(200)});
    rightWalk.push_back({7,sf::milliseconds(200)});
    upWalk.push_back({9,sf::milliseconds(200)});
    upWalk.push_back({10,sf::milliseconds(200)});
    upWalk.push_back({11,sf::milliseconds(200)});
    upWalk.push_back({10,sf::milliseconds(200)});
    multiwalk.insert({"right", rightWalk});
    multiwalk.insert({"left", leftWalk});
    multiwalk.insert({"up", upWalk});
    multiwalk.insert({"down", downWalk});

    AnimatedSprite guy("../img/walkingguy.png", multiwalk);
    guy.move(256,256);
    /**************************************/

    /****** TESTING PARTICLE EFFECTS ******/
    ParticleEngine partEngine;
    ParticleTemplate partTpltSparks([]()->double{return 0;}, []()->double{return 0;},
                                    ParticleTemplate::normalDist(0.,200.), ParticleTemplate::uniformDist(0.,2*M_PI),
                                    []()->sf::Time{return sf::seconds(ParticleTemplate::normalDist(.1,.2)());},
                                    [](double, double, double vx, double vy, sf::Time)->std::array<double,2>{return {-2*vx, -2*vy+2000};},
                                    [](double, double, double vx, double vy, sf::Time t)->sf::Color{return {255, std::min<sf::Uint8>(2*sqrt(t.asSeconds())*sqrt(vx*vx+vy*vy),255), std::min<sf::Uint8>(4*pow(t.asSeconds(),2.)*sqrt(vx*vx+vy*vy),255)};} );

    ParticleTemplate partTpltRain(ParticleTemplate::uniformDist(-2000,1000), ParticleTemplate::uniformDist(-2000,1000),
                                  ParticleTemplate::normalDist(600,10), ParticleTemplate::normalDist(M_PI/3.,M_PI/100.),
                                  []()->sf::Time{return sf::seconds(ParticleTemplate::normalDist(8,0)());},
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
                    partEngine.createParticleEffect(100, guy.getPosition()[0], guy.getPosition()[1], partTpltSparks);
                if (event.key.code == sf::Keyboard::B)
                    partEngine.createParticleEffect(2000, guy.getPosition()[0], guy.getPosition()[1], partTpltRain);
            }

            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
        }
        /*****************************/

        /****** MOVING THE SPRITE LIKE A PLAYER ******/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            guy.move(4,0);
            guy.chooseAnimation("right");
            multianime.chooseAnimation("right");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            guy.move(-4,0);
            guy.chooseAnimation("left");
            multianime.chooseAnimation("left");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            guy.move(0,4);
            guy.chooseAnimation("down");
            multianime.chooseAnimation("down");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            guy.move(0,-4);
            guy.chooseAnimation("up");
            multianime.chooseAnimation("up");
        }

        auto pos = guy.getPosition();
        if (pos[0] < view.getSize().x/2)
            pos[0] = view.getSize().x/2;
        if (pos[0] > 64*32 - view.getSize().x/2)
            pos[0] = 64*32 - view.getSize().x/2;
        if (pos[1] < view.getSize().y/2)
            pos[1] = view.getSize().y/2;
        if (pos[1] > 64*24 - view.getSize().y/2)
            pos[1] = 64*24 - view.getSize().y/2;
        view.setCenter(pos[0], pos[1]);
        window.setView(view);
        /*********************************************/

        /****** UPDATE TIMES THINGS ******/
        auto elapsedTime = clock.restart();
        anime.rotate(elapsedTime.asMilliseconds()*M_PI/180/4);
        anime.updateAnimation(elapsedTime);
        multianime.updateAnimation(elapsedTime);
        guy.updateAnimation(elapsedTime);
        partEngine.update(elapsedTime);
        /**********************************/

        /****** DISPLAY EVERYTHING ******/
        window.clear();
        window.draw(map);
        window.draw(anime);
        window.draw(multianime);
        window.draw(guy);
        window.draw(partEngine);
        window.display();
        /********************************/
    }

    return 0;
}
