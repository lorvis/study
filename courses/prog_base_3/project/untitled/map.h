#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#define TILE_SIZE 32

struct xyPVector {
    float * x;
    float * y;
};

class Map{

    sf::String layer;
    std::string median_string;
    std::ifstream mapfile;
    sf::Image tilesetImg;
    sf::Texture tilesetText;
    sf::Sprite tilesetSprite;
    sf::RenderWindow * window;
    int width;
    int height;
public:
    Map(sf::String filename, sf::String tilesetFileName, sf::RenderWindow * window);
    char tileTypeXY(float x, float y);
    char ** charmap;
    void update();
};
#endif // MAP_H
