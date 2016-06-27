#ifndef NPC_H
#define NPC_H
#include <stdlib.h>
#include "character.h"
#include "projectile.h"

enum aiAction {AI_IDLE = 0, AI_UP = 2, AI_LEFT = 4, AI_DOWN = 8, AI_RIGHT = 16, AI_SHOOT = 32, AI_MOVE = 64,AI_JUMP = 128,AI_TARGETED = 256};

class NPC : public Character
{
    bool isTargetDetected;
    bool * wClosed;
    float logicTimer;
    float anchorDirTimer;
    Character * player;
    float xLogicAnchor;
    float *xLogicTarget;
    void updateLogic();
    bool checkForWall(float x1, float x2, float y1, float y2, int precision);
public:
    NPC(Map * pMap, RenderWindow * pWindow, float * time, float x, float y, sf::Texture *cTexture, ProjectileList * allProj, char cType , Character * player, charSBpack *sbPack) : Character(pMap,pWindow,time,x,y,cTexture,allProj,sbPack){
        type = cType;
        srand(1);
        logicAction = AI_IDLE;
        xLogicTarget = new float;
        *xLogicTarget = x;
        isTargetDetected = false;
        xLogicAnchor = x;
        logicTimer = 10;
        if(type == SOLDIER)
            health = 150;
        this->player = player;
        anchorDirTimer = rand()%60000;
    }
     int logicAction;
     void update();
     void updateFrame();
     void checkstatus();
     void enspeed();
     void jump();
     void targetPlayer();
     void dropAnchor();
     bool checkForProj();
     float jumpSpeed;
     float health;
     float getHealth();
};
#endif // NPC_H
