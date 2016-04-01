#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>


enum class Tile
{
    EMPTY, GROUND, WALL, DOOR, WINDOW
};

class Map : public sf::Drawable
{
public:
    Map(int width, int height);

    void setTile(int x, int y, Tile newTile);
    void setTiles(const std::vector<Tile> &newTiles);

    void update();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    int _width, _height;
    std::vector<Tile> _tiles;
    sf::VertexArray _varray; //(sf::Quads, 4*32*24);
    sf::RenderTexture _stitched;
};


#endif // MAP_H
