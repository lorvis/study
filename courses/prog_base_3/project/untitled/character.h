#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "map.h"
#include "projectilelist.h"
#define PLAYER_SIZE 96
#define CHAR_DEBUG

using namespace sf;

enum status {IDLE=0,REFLEXIVE=1,JUMP=2,BACKWARD=4,COACH=8,FORWARD=16,SHOOTING=32,STOPPED=64,ABSORBING=128};
enum dir {NODIR=0,UP=2,LEFT=4,DOWN=8,RIGHT=16,SPIN=32,STAND=64};

class Character
{
    bool isSpinning = false;
    bool isAbsorbing = false;
    char checkTileAtP(char dir, int tile);
    void die(int energy);
    void absorb(int energy);
protected:
    float specialAnimCounter;
    float heat;
    float * time;
    float speed;
    float energy;
    float currentFrame;
    char debugText[200];
    Map * area;
    RenderWindow * window;
    Image cImage;
    Texture cTexture;
    Sprite cSprite;
    ProjectileList * pList;
    void checkDir();
    virtual void checkstatus();
    virtual void enspeed();
    virtual void updateFrame();
    virtual bool collision();
    void shoot(float power, bool toLeft, char type);
public:
    Text debugInfo;
    Character(Map * pMap, RenderWindow * pWindow, float * time, float x, float y, char * imageName, ProjectileList * allProj);
    float x = 100;
    float y = 200;
    float dx = 0;
    float dy = 0;
    unsigned char status = IDLE;
    unsigned char curDir = NODIR;
    float getX();
    float getY();
    virtual void update();
};

#endif // PLAYER_H
