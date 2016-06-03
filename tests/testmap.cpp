#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "../src/drawlib/map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Test des map");  // create window
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

        /****** MOVING THE VIEW AROUND ******/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            view.move(10,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            view.move(-10,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            view.move(0,10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            view.move(0,-10);
        }

        window.setView(view);
        /************************************/


        /****** DISPLAY EVERYTHING ******/
        window.clear();
        window.draw(map);
        window.display();
        /********************************/
    }

    return 0;
}
