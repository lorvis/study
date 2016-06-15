#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "character.h"

#define PROJ_WIDTH 50
#define PROJ_HEIGHT 20

enum projType {UNDEFINED = 0,ENERGYBLAST = 2, BULLETSHOT = 4, LASER = 8, PLAYERS = 16, ENEMYS = 32};

class Projectile {
    float xSpeed;
    float ySpeed;
    float x;
    float y;
    float dx = 0;
    float dy = 0;
    float energy;
    float currentFrame = 0;
    float * time;
    int type;
    void (*hitEffect)(int energy);
    void updateFrame();
    void update();
    sf::Sprite projSprite;
    Character * player;
public:
    Projectile(Character * player, float x, float y, float xSpeed, float ySpeed, int type, float *time);
    float getX();
    float getY();
    void accelerate(float xAccel, float yAccel);
    bool isHit();
};

#endif // PROJECTILE_H
