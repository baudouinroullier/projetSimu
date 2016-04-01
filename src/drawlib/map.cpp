#include "map.h"
#include <string>


Map::Map(int width, int height) : _width(width), _height(height), _tiles(width*height, VisualTile::EMPTY), _varray(sf::Quads, 4*width*height)
{
    std::vector<std::string> nameList = {"ground", "wall", "door", "window"};
    _stitched.create((nameList.size()+1)*50,50);
    _stitched.clear({0,0,0,0});

    // load all texture files and stitch them together
    for (int i=0; i<nameList.size(); i++)
    {
        sf::Texture texture;
        std::string name = "../img/" + nameList[i] + ".png";
        texture.loadFromFile(name);

        // stitch textures together
        sf::Sprite sprite(texture);
        sprite.setPosition(50*(i+1),0);
        _stitched.draw(sprite);
    }

    for (int i=0; i<_width*_height; i++)
    {
        float x = 50*(i%_width), y = 50*(i/_width);
        _varray[4*i  ].position = {x, y};
        _varray[4*i+1].position = {x+50, y};
        _varray[4*i+2].position = {x+50, y+50};
        _varray[4*i+3].position = {x, y+50};
    }
}

void Map::setTile(int x, int y, VisualTile newTile)
{
    if (x<0 || x>=_width || y<0 || y>=_height)
        throw (std::logic_error("New tile position is out of bounds."));
    _tiles[_width*y + x] = newTile;
}

void Map::setTiles(const std::vector<VisualTile> &newTiles)
{
    if (newTiles.size() != _tiles.size())
        throw (std::logic_error("newTiles should be the same size as the map."));
    _tiles = newTiles;
}

void Map::update()
{
    float texOffset = 0;
    for (unsigned int i=0; i<_tiles.size(); i++)
    {
        texOffset = (float)_tiles[i];
        _varray[4*i  ].texCoords = {50*texOffset,50};
        _varray[4*i+1].texCoords = {50*texOffset+50,50};
        _varray[4*i+2].texCoords = {50*texOffset+50,0};
        _varray[4*i+3].texCoords = {50*texOffset,0};
    }
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(_varray, {&_stitched.getTexture()});
}
