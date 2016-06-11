#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "map.h"
#define PLAYER_SIZE 96

using namespace sf;

enum status {IDLE=0,REFLEXIVE=1,JUMP=2,BACKWARD=4,COACH=8,FORWARD=16,CLIMBABLE=32,STOPPED=64};
enum dir {NODIR=0,UP=2,LEFT=4,DOWN=8,RIGHT=16,SPIN=32,STAND=64};

class Character
{
    bool isSpinning = false;
    float * time;
    float x;
    float y;
    float speed = 1;
    float dx = 0;
    float dy = 0;
    float currentFrame = 0;
    char debugText[200];
    Map * area;
    RenderWindow * window;
    Image pImage;
    Texture pTexture;
    Sprite pSprite;
    char status = IDLE;
    char curDir = NODIR;
    char checkTileAtP(char dir, int tile);
    void checkDir();
    void enspeed();
    void checkstatus();
    void updateFrame(char dir);
    void updateFrame();
public:
    Text debugInfo;
    Character(float startX, float startY, Map * pMap, RenderWindow * pWindow, float * time);
    float getX();
    float getY();
    void update();
};

#endif // PLAYER_H
