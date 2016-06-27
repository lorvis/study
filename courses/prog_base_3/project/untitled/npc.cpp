#include "npc.h"
#include "character.h"
#include <string.h>
#include <limits>

void NPC::update(){
    checkstatus();
    updateLogic();
    enspeed();
    checkDir();
    updateFrame();
    if(energy < 100)
        energy+=0.02*(*time);
    if(energy > 100)
        energy = 100;
    if(heat > 0)
        heat -= 0.03*(*time);
    if(heat < 0)
        heat = 0;
    x+=dx;
    y+=dy;
}
void NPC::updateFrame(){
    currentFrame+=(*time)*0.006;
    int soldierBackFlag = 0;
    if(curDir == NODIR){
        if(type == SOLDIER)
        cSprite.setTextureRect(IntRect(3*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
            else
        cSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
        cSprite.setPosition(Vector2f(x+dx,y+dy));
    }
    if(currentFrame>=4)
    {
        currentFrame = 0;
        if(type==SOLDIER)
            soldierBackFlag = !soldierBackFlag;
    }

    if(type == SOLDIER && specialAnimCounter != 0){
        specialAnimCounter -= 0.004*(*time);
        if(specialAnimCounter < 0)
            specialAnimCounter = 0;
       cSprite.setTextureRect(IntRect((int)specialAnimCounter*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
       if(curDir & RIGHT)
       {
           cSprite.setScale(-1,1);
           cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
       }
       else
           cSprite.setPosition(Vector2f(x+dx,y+dy));

    }
    else
    {

    //STAND
        if((curDir & STAND)!=0)
        {
            if((curDir & LEFT)!=0)
            {
                if(type == SOLDIER)
                    cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
                else
                cSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
               cSprite.setPosition(Vector2f(x+dx,y+dy));
                       }
            else
            {
                if(type == SOLDIER)
                    cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
                else
                cSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                cSprite.setScale(-1,1);
                cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
            }
    }

            //SIMPLE
            if((curDir & STAND)==0)
            {
                if((curDir & RIGHT)!=0){
                    if((curDir & UP)!=0)
                    {
                        if(type==SOLDIER) //Same as RIGHT | DOWN to SOLDIER
                        {
                            if(soldierBackFlag)
                            cSprite.setTextureRect(IntRect((3 - (int)currentFrame)*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                            else
                            cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        }
                        else
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setScale(-1,1);
                        cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                    }
                    else
                    if((curDir & DOWN)!=0)
                    {
                            if(soldierBackFlag) //Same as LEFT | DOWN to SOLDIER
                            cSprite.setTextureRect(IntRect((3 - (int)currentFrame)*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                            else
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setScale(-1,1);
                        cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                    }
                    else
                    {
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setScale(-1,1);
                        cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                    }
                }
                if((curDir & LEFT)!=0){
                    if((curDir & UP)!=0)
                    {
                        if(type==SOLDIER) //Same as LEFT | DOWN to SOLDIER
                        {
                            if(soldierBackFlag)
                            cSprite.setTextureRect(IntRect((3 - (int)currentFrame)*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                            else
                            cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        }
                        else
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setPosition(Vector2f(x+dx,y+dy));
                    }
                    else
                    if((curDir & DOWN)!=0)
                    {
                        if(soldierBackFlag) //Same as LEFT | UP to SOLDIER
                            cSprite.setTextureRect(IntRect((3 - (int)currentFrame)*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        else
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setPosition(Vector2f(x+dx,y+dy));
                    }
                    else
                    {
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setPosition(Vector2f(x+dx,y+dy));
                    }
                }
            }
    }
    window->draw(cSprite);
    cSprite.setScale(1,1);
}

void NPC::enspeed(){
    dx = 0;
    if(type == SOLDIER){
        dy+= 0.015*(*time) + jumpSpeed;
    }
    else
        if((status & JUMP) != 0 && (status & COACH) == 0 ) {
        dy+= *time*speed*(-0.1);
        }

    if(logicAction & AI_LEFT) {
    dx+= *time*speed*(-0.1);
    }
    if(logicAction & AI_RIGHT) {
    dx+= *time*speed*(0.1);
    }
    if((status & COACH) != 0 && (status & JUMP) == 0 ) {
    dy+= *time*speed*(0.1);
    }

    collision();


}

void NPC::checkstatus(){

    if(std::isnan(jumpSpeed))
        jumpSpeed = 0;

    if(jumpSpeed < 0)
    {
        status = JUMP;
        jumpSpeed += 0.0004*(*time);
    }
    if(jumpSpeed < -1)
    {
        jumpSpeed =-1;
    }

    if(jumpSpeed > 0)
        jumpSpeed = 0;


}

bool NPC::checkForWall(float x1, float x2, float y1, float y2, int precision){
    if(!(x1 >= 0 && x2 >=0 && y1 >=0 && y2 >=0))
        return true;
    if(x1 == x2 && y1 == y2)
        return area->tileTypeXY(x1,y2)!='_';
    int xIter;
    int yIter;
    if(x2-x1 >=0)
        xIter = 1;
    else
        xIter = -1;
    if(y2-y1 >=0)
        yIter = 1;
    else
        yIter = -1;
    float curX = x1;
    float curY = y1;
    while(std::abs(x1-x2) >= std::abs(x1-curX) && std::abs(y1-y2) >= std::abs(y1-curY)){
        if(area->tileTypeXY(curX,curY)!='_')
            return true;
        curX += xIter*std::abs(x1-x2)/precision;
        curY += yIter*std::abs(y1-y2)/precision;
    }
    return false;
}

void NPC::updateLogic(){
    anchorDirTimer = (int)anchorDirTimer%1000000;
    anchorDirTimer+=*time*(6+rand()%45);
    if(logicTimer > 0)
    logicTimer -= 0.002*(*time);
    if(logicTimer < 0)
    {
        dropAnchor();
        logicTimer = 0;
    }
    if(status & SHOOTING)
        status ^= SHOOTING;
    if(logicAction & AI_TARGETED)
        logicAction = AI_TARGETED;
    else logicAction = AI_IDLE;
if(type == SOLDIER){
    if(std::abs(y-player->y)<=96 && ((player->x-x < 0 && (curDir & LEFT)) || (player->x-x > 0 && (curDir & RIGHT))) ){
        bool wallPresence = checkForWall(x,player->x,y+TILE_SIZE+6,y+TILE_SIZE+6,200);
        if(!wallPresence && std::abs(y-player->y)<=32){
            targetPlayer();
            if(energy > 25 && heat == 0){
                specialAnimCounter = 3;
                status |= SHOOTING;
                shoot((int)energy%101,(x-player->x > 0),ENERGYBLAST);
            }
        }
        else
        {
            wallPresence = checkForWall(x,player->x,y+16,y+16,200) && checkForWall(x,player->x,y-16,y-16,200);
            if(!wallPresence){
                targetPlayer();
                jump();
                if(energy > 25 && heat == 0){
                    specialAnimCounter = 3;
                    status |= SHOOTING;
                    shoot((int)energy%101,(x-player->x > 0),ENERGYBLAST);
                }
            }
        }
    }
    else
        if(logicAction & AI_TARGETED){
            if(std::abs(player->x - x) < 96 && std::abs(player->y-y) >48)
                dropAnchor();
            else {
            if(x-player->x > 0){
                logicAction |= AI_LEFT;
            }
            else{
                logicAction |= AI_RIGHT;
            }
            if(y-player->y > 0){
                logicAction |= AI_DOWN;
            }
            else{
                logicAction |= AI_UP;
            }
           if(logicAction & AI_RIGHT)
               if((area->tileTypeXY(x+PLAYER_SIZE+16+dx,y+TILE_SIZE*2+16)!='_') || (area->tileTypeXY(x+PLAYER_SIZE+16+dx,y+TILE_SIZE+16)!='_')){
                jump();
               }
           if(logicAction & AI_LEFT)
               if((area->tileTypeXY(x-16+dx,y+TILE_SIZE*2+16)!='_') || (area->tileTypeXY(x-16+dx,y+TILE_SIZE+16)!='_')){
                jump();
               }
           if(logicAction & AI_UP)
               if(((area->tileTypeXY(x+TILE_SIZE*2+16+dx,y+PLAYER_SIZE+16)!='_') && ((area->tileTypeXY(x+PLAYER_SIZE+TILE_SIZE+16+dx,y+PLAYER_SIZE+16)=='_'))))
                jump();

    }
        }
    else
    if(((int)anchorDirTimer%100000) >= 50000){
            if((area->tileTypeXY(x+PLAYER_SIZE+16+dx,y+TILE_SIZE*2+16)!='_') || (area->tileTypeXY(x+PLAYER_SIZE+16+dx,y+TILE_SIZE+16)!='_')){
               logicAction |= AI_LEFT;
            }
            else logicAction |= AI_RIGHT;
    }
    else
        if((area->tileTypeXY(x-16+dx,y+TILE_SIZE*2+16)!='_') || (area->tileTypeXY(x-16+dx,y+TILE_SIZE+16)!='_')){
         logicAction |= AI_RIGHT;
        }
    else
            logicAction |= AI_LEFT;
}
}

void NPC::jump(){
    if(jumpSpeed == 0 && dy ==0)
    jumpSpeed = -1;
    logicAction |= AI_JUMP;
}

void NPC::targetPlayer(){
    logicTimer = 100;
    logicAction |= AI_TARGETED;
    if(xLogicTarget!=&player->x){
    delete xLogicTarget;
    xLogicTarget = &player->x;
    }
}

bool NPC::checkForProj(){
    char origin;
    if(type == SOLDIER)
        origin = ORIGIN_SOLDIER;
    for(int i = 0; i < pList->pVector.size();i++){
        if(pList->checkRect(i,origin,x+1,y+TILE_SIZE+1,x+PLAYER_SIZE,y+PLAYER_SIZE)){
            pList->remove(i);
            return true;
        }
    }
    return false;
}

float NPC::getHealth() {
   return this->health;
}

void NPC::dropAnchor(){
    logicTimer = 0;
    if(logicAction & AI_TARGETED)
        logicAction^=AI_TARGETED;
    if(xLogicTarget == &player->x)
        xLogicTarget = new float;
    *xLogicTarget = x;
}
