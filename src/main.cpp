#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "drawlib/map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Projet Simu!");  // create window

    // tiled terrain
    Map map(32,24);

    // tiles for the terrain -> should be read from a level design file
    std::vector<Tile> tiles(32*24,Tile::EMPTY);
    for (int i=131; i<141; i++)
        tiles[i] = Tile::WALL;
    for (int i=259; i<269; i++)
        tiles[i] = Tile::GROUND;
    tiles[163] = Tile::WALL;
    tiles[172] = Tile::WALL;
    tiles[195] = Tile::WALL;
    tiles[204] = Tile::WINDOW;
    tiles[227] = Tile::DOOR;
    tiles[236] = Tile::WALL;

    for (int i=503; i<508; i++)
        tiles[i] = Tile::WALL;
    for (int i=535; i<540; i++)
        tiles[i] = Tile::DOOR;
    for (int i=567; i<572; i++)
        tiles[i] = Tile::GROUND;

    // set the tiles we created
    map.setTiles(tiles);
    map.setTile(7,7,Tile::DOOR);
    map.update();

    auto wndSize = window.getSize();
    sf::View view({0,0, (float)wndSize.x, (float)wndSize.y});

    // main loop, TODO: move elsewhere
    while (window.isOpen())
    {
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
                    view.move(20,0);
                    break;
                case sf::Keyboard::Left:
                    view.move(-20,0);
                    break;
                case sf::Keyboard::Down:
                    view.move(0,20);
                    break;
                case sf::Keyboard::Up:
                    view.move(0,-20);
                    break;
                default:
                    break;
                }
            }
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
            }
        }

        window.setView(view);
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
