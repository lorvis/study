#ifndef NPC_H
#define NPC_H
#include "character.h"
#include "projectile.h"

enum aiAction {AI_IDLE = 0, AI_UP = 2, AI_LEFT = 4, AI_DOWN = 8, AI_RIGHT = 16, AI_SHOOT = 32, AI_MOVE = 64,AI_JUMP = 128};

class NPC : public Character
{
    bool isTargetDetected;
    bool * wClosed;
    int logicAction;
    float logicTimer;
    Character * player;
    float health;
    float jumpSpeed;
    float xLogicAnchor;
    float *xLogicTarget;
    void updateLogic();
    bool checkForWall(float x1, float x2, float y1, float y2, int precision);
public:
    void spriteInit(sf::Texture *cTexture);
    NPC(Map * pMap, RenderWindow * pWindow, float * time, float x, float y, sf::Texture *cTexture, ProjectileList * allProj, char cType , Character * player) : Character(pMap,pWindow,time,x,y,cTexture,allProj){
        type = cType;
        logicAction = AI_IDLE;
        xLogicTarget = new float;
        *xLogicTarget = x;
        isTargetDetected = false;
        xLogicAnchor = x;
        logicTimer = 10;
        if(type == SOLDIER)
            health = 150;
        this->player = player;
    }
     void update();
     void updateFrame();
     void checkstatus();
     void enspeed();
     void jump();
     void targetPlayer();
     bool checkForProj();
};
#endif // NPC_H
