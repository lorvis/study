#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#define TILE_SIZE 32

enum gameStatus { GS_NONE = 0, GS_NEWGAME = 2, GS_LOADED = 4, GS_WIN = 8, GS_DEFEAT = 16,GS_CLOSED = 32, GS_NEXT = 64 };

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
    Map(sf::String filename, sf::String tilesetFileName, sf::RenderWindow * window, char gStatus);
    char tileTypeXY(float x, float y);
    char ** charmap;
    void update();
    int getW();
    int getH();
};
#endif // MAP_H
