#ifndef ENEMYLIST_H
#define ENEMYLIST_H
#include "npc.h"
#include "functional"

class EnemyList
{
    std::vector < NPC > npcVector;
    sf::Image ememyImg;
    sf::Texture enemyTexture;
    sf::Font dFont;
    sf::RenderWindow *window;
    Character *player;
    Map *area;
    ProjectileList *pList;
    float *time;
public:
    EnemyList(sf::RenderWindow *window, Map * area, Character * player, ProjectileList * pList, float *time);
    void add(float x, float y, char cType);
    void winGame();
    void checkNPC();
    void win();
    std::function<void(EnemyList&)> update;
    bool allDefeated;
};

#endif // ENEMYLIST_H
