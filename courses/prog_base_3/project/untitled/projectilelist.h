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
    std::vector < Projectile > pList;
    Map * area;
    EffectList * effects;
    void deleteByIndex(int index);
public:
    ProjectileList(sf::RenderWindow *window, float * time, Map * area, EffectList * effects);
    void add(float energy, float x, float y, float xSpeed, float ySpeed, int type);
    void updateList();
    Projectile * get(int index);
    void checkForPresence(float x, float y, float width, float height);
    bool isProjectileCollide(Projectile proj);
};

#endif // PROJECTILELIST_H
