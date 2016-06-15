#ifndef NPC_H
#define NPC_H
#include "character.h"
#include "projectile.h"

enum {UNKNOWN = 0, SOLDIER = 2};

class NPC : public Character
{
char type;
Character * player;
float jumpSpeed;
public:
    NPC(Map * pMap, RenderWindow * pWindow, float * time, float x, float y, char * imageName, char cType, Character * player) : Character(pMap,pWindow,time,x,y,imageName){
        type = cType;
        this->player = player;
    }
 void update();
 void updateFrame();
 void checkstatus();
 void enspeed();
 void shoot();
};
#endif // NPC_H
