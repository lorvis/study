#ifndef PROJECTILELIST_H
#define PROJECTILELIST_H
#include "projectile.h"
#include "map.h"
#include <vector>

class ProjectileList
{
    int currentID = 0;
    int targetID = -1;
    sf::RenderWindow *window;
    sf::Texture * projTexture;
    float * time;
    std::vector < Projectile > pList;
public:
    ProjectileList(sf::RenderWindow *window, float * time, sf::Texture * projTexture);
    void add(float energy, float x, float y, float xSpeed, float ySpeed, int type);
    void updateList();
    Projectile * get(int index);
    void checkForPresence(float x, float y, float width, float height);
};

#endif // PROJECTILELIST_H
