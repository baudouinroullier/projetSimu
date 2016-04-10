#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "../src/drawlib/animatedsprite.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Projet Simu!");  // create window
    window.setVerticalSyncEnabled(true);
    auto wndSize = window.getSize();
    sf::View view({0,0, (float)wndSize.x, (float)wndSize.y});
    window.setView(view);

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
        /**********************************/

        /****** DISPLAY EVERYTHING ******/
        window.clear();
        window.draw(anime);
        window.draw(multianime);
        window.draw(guy);
        window.display();
        /********************************/
    }

    return 0;
}
