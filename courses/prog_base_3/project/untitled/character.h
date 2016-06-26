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
enum charType {UNKNOWN = 0, PLAYER = 2, SOLDIER = 4};
enum status {IDLE=0,REFLEXIVE=1,JUMP=2,BACKWARD=4,COACH=8,FORWARD=16,SHOOTING=32,STOPPED=64,ABSORBING=128};
enum dir {NODIR=0,UP=2,LEFT=4,DOWN=8,RIGHT=16,SPIN=32,STAND=64};

class Character
{
    bool isSpinning = false;
    char checkTileAtP(char dir, int tile);
    void absorb(int energy);
protected:
    float specialAnimCounter;
    float heat;
    float * time;
    float speed;
    float energy;
    float currentFrame;
    char debugText[1000];
    char type;
    RenderWindow * window;
    Sprite cSprite;
    ProjectileList * pList;
    void checkDir();
    void debugChar();
    void showEnergy();
    virtual void checkstatus();
    virtual void enspeed();
    virtual void updateFrame();
    virtual void die();
    virtual bool collision();
    void shoot(float power, bool toLeft, char type);
public:
    Map * area;
    Text debugInfo;
    Text energyInfo;
    Character(Map * pMap, RenderWindow * pWindow, float * time, float x, float y, sf::Texture *cTexture, ProjectileList * allProj);
    float x = 100;
    float y = 200;
    float dx = 0;
    float getX();
    float getY();
    float dy = 0;
    unsigned char status = IDLE;
    unsigned char curDir = NODIR;
    virtual bool checkForProj();
    virtual void update();
    bool defeated = false;
};

#endif // PLAYER_H
