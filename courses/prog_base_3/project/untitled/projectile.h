#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#define PROJ_WIDTH 50
#define PROJ_HEIGHT 20
#define PROJ_DEBUG

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
    int id;
    int type;
    void updateFrame();
    sf::Sprite projSprite;
    sf::RenderWindow * window;
public:
#ifdef PROJ_DEBUG
    sf::Text debugInfo;
#endif
    Projectile(float energy, sf::RenderWindow * window, float x, float y, float xSpeed, float ySpeed, int type, float * time, int id, sf::Texture * projTexture);
    float getX();
    float getY();
    int getID();
    void (*hitEffect)(int energy);
    void update();
    void accelerate(float xAccel, float yAccel);
    bool isThere(float x, float y, float width, float height);
    bool isHit();
};

#endif // PROJECTILE_H
