#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>


enum class VisualTile
{
    EMPTY, GROUND, WALL, DOOR, WINDOW
};

class Map : public sf::Drawable
{
public:
    Map(int width, int height);

    void setTile(int x, int y, VisualTile newTile);
    void setTiles(const std::vector<VisualTile> &newTiles);

    void update();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    int _width, _height;
    std::vector<VisualTile> _tiles;
    sf::VertexArray _varray;
    sf::RenderTexture _stitched;
};


#endif // MAP_H
