#ifndef PROJECTILELIST_H
#define PROJECTILELIST_H
#include "projectile.h"
#include "map.h"
#include <vector>
#include "effectlist.h"

class ProjectileList
{
    int currentID = 0;
    int targetID = -1;
    float * time;
    sf::RenderWindow *window;
    sf::Image projImage;
    sf::Texture projTexture;
    Map * area;
    EffectList * effects;
public:
    Vector2i remove(int index);
    std::vector < Projectile > pVector;
    ProjectileList(sf::RenderWindow *window, float * time, Map * area, EffectList * effects);
    Projectile * get(int index);
    void add(float energy, float x, float y, float xSpeed, float ySpeed, int type, char origin);
    void updateList();
    bool isProjectileCollide(Projectile proj);
    bool checkRect(int index, char origin, float x1, float y1, float x2, float y2);
};

bool isInRect(float x, float y, float x1, float y1, float x2, float y2);

#endif // PROJECTILELIST_H
