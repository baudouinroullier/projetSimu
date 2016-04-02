#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "drawlib/map.h"
#include "drawlib/animatedsprite.h"

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
    // create an animated sprite
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
    sf::Clock animationClock;
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
                switch (event.key.code)
                {
                case sf::Keyboard::Right:
                    view.move(32,0);
                    break;
                case sf::Keyboard::Left:
                    view.move(-32,0);
                    break;
                case sf::Keyboard::Down:
                    view.move(0,32);
                    break;
                case sf::Keyboard::Up:
                    view.move(0,-32);
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                default:
                    break;
                }
            }
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
        }
        /*****************************/

        /****** UPDATE ANIMATED SPRITES ******/
        anime.rotate(animationClock.getElapsedTime().asMilliseconds()*M_PI/180/4);
        anime.updateAnimation(animationClock.getElapsedTime());
        animationClock.restart();
        /**************************************/

        /****** DISPLAY EVERYTHING ******/
        window.clear();
        window.draw(map);
        window.draw(anime);
        window.display();
        /********************************/
    }

    return 0;
}
