#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    srand(0); // seed the randomiser

    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");  // create window

    // create vertex array and prepare stitched texture
    sf::VertexArray varray(sf::Quads, 20000);
    sf::RenderTexture stitched;
    stitched.create(500,50);
    stitched.clear({0,0,0,0});

    // load all texture files and stitch them together
    for (int i=0; i<10; i++)
    {
        sf::Texture texture;
        string name = "../../img/tile" + to_string(i) + ".png";
        texture.loadFromFile(name);

        // stitch textures together
        sf::Sprite sprite(texture);
        sprite.setPosition(50*i,0);
        stitched.draw(sprite);
    }

    sf::Clock clock;
    int cpt = 0;

    while (window.isOpen())
    {
        // manage events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // for all 5000 quads, randomise new position and new texture
        for (int i=0; i<5000; i++)
        {
            float x = rand()%600, y = rand()%600;
            varray[4*i  ].position = {x-25,y-25};
            varray[4*i+1].position = {x+24,y-25};
            varray[4*i+2].position = {x+24,y+24};
            varray[4*i+3].position = {x-25,y+24};
            float texOffset = 50*(rand()%10);
            varray[4*i  ].texCoords = {texOffset,0};
            varray[4*i+1].texCoords = {texOffset,49};
            varray[4*i+2].texCoords = {49+texOffset,49};
            varray[4*i+3].texCoords = {49+texOffset,0};
        }

        // update display
        window.clear();
        window.draw(varray, {&stitched.getTexture()});
        window.display();

        // every second, display the FPS
        cpt++;
        if (clock.getElapsedTime().asSeconds() >= 1)
        {
            cout << (double)cpt/clock.getElapsedTime().asSeconds() << endl;
            cpt = 0;
            clock.restart();
        }
    }

    return 0;
}
