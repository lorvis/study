#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "effect.h"
#define PROJ_WIDTH 50
#define PROJ_HEIGHT 20
#define PROJ_DEBUG

enum projType {UNDEFINED = 0,ENERGYBLAST = 2, BULLETSHOT = 4, LASER = 8, PLAYERS = 16, ENEMYS = 32};
enum projOrigin {ORIGIN_UNDEFINED = 0, ORIGIN_PLAYER = 2, ORIGIN_SOLDIER = 4};

class Projectile {
    float dx = 0;
    float dy = 0;
    float currentFrame = 0;
    float * time;
    int id;
    void updateFrame();
    sf::Sprite projSprite;
    sf::RenderWindow * window;
public:
#ifdef PROJ_DEBUG
    sf::Text debugInfo;
#endif
    Projectile(float energy, sf::RenderWindow * window, float x, float y, float xSpeed, float ySpeed, int type, float * time, int id, sf::Texture * projTexture, char origin);
    float xSpeed;
    float ySpeed;
    float energy;
    float x;
    float y;
    int type;
    char origin;
    int getID();
    char getDir();
    float getEnergy();
    float getX();
    float getY();
    void (*hitEffect)(int energy);
    void update();
    void accelerate(float xAccel, float yAccel);
    bool isThere(float x, float y, float width, float height);
    bool isHit();

};

#endif // PROJECTILE_H
