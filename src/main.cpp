#include <SFML/Graphics.hpp>
#include <array>
#include <string>


enum class Tile
{
    EMPTY, GROUND, WALL, DOOR, WINDOW
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Projet Simu!");  // create window

    // prepare stitched texture
    sf::RenderTexture stitched;
    stitched.create(5*50,50);
    stitched.clear({255,255,255,255});

    // load all texture files and stitch them together
    std::string nameList[4] = {"ground", "wall", "door", "window"};
    for (int i=0; i<4; i++)
    {
        sf::Texture texture;
        std::string name = "../img/" + nameList[i] + ".png";
        texture.loadFromFile(name);

        // stitch textures together
        sf::Sprite sprite(texture);
        sprite.setPosition(50*(i+1),0);
        stitched.draw(sprite);
    }

    std::array<Tile, 32*24> map;
    map.fill(Tile::EMPTY);
    for (int i=131; i<141; i++)
        map[i] = Tile::WALL;
    for (int i=259; i<269; i++)
        map[i] = Tile::GROUND;
    map[163] = Tile::WALL;
    map[172] = Tile::WALL;
    map[195] = Tile::WALL;
    map[204] = Tile::WINDOW;
    map[227] = Tile::DOOR;
    map[236] = Tile::WALL;

    for (int i=503; i<508; i++)
        map[i] = Tile::WALL;
    for (int i=535; i<540; i++)
        map[i] = Tile::DOOR;
    for (int i=567; i<572; i++)
        map[i] = Tile::GROUND;

    sf::VertexArray varray(sf::Quads, 4*32*24);
    for (int i=0; i<varray.getVertexCount()/4; i++)
    {
        float x = 50*(i%32), y = 50*(i/32);
        varray[4*i  ].position = {x, y};
        varray[4*i+1].position = {x+50, y};
        varray[4*i+2].position = {x+50, y+50};
        varray[4*i+3].position = {x, y+50};

        float texOffset = 0;
        switch (map[i])
        {
        case Tile::GROUND:
            texOffset = 1;
            break;
        case Tile::WALL:
            texOffset = 2;
            break;
        case Tile::DOOR:
            texOffset = 3;
            break;
        case Tile::WINDOW:
            texOffset = 4;
            break;
        default:
        case Tile::EMPTY:
            texOffset = 0;
            break;
        }

        varray[4*i  ].texCoords = {50*texOffset,50};
        varray[4*i+1].texCoords = {50*texOffset+50,50};
        varray[4*i+2].texCoords = {50*texOffset+50,0};
        varray[4*i+3].texCoords = {50*texOffset,0};
    }

    sf::View view(sf::Vector2f(400, 300), sf::Vector2f(800, 600));

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
        window.draw(varray, {&stitched.getTexture()});
        window.display();
    }

    return 0;
}
