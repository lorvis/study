#include "npc.h"
#include "character.h"
#include <string.h>

void NPC::update(){
    sprintf(debugText,"");
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
#ifdef CHAR_DEBUG
    char debugData[500];
    sprintf(debugData,"\nCoord:[%.2f,%.2f]\n"
                      "TileCoord:[%i,%i]\n"
                      "ENERGY = %f\n"
                      "HEAT = %f\n"
                      "dx = %f\n"
                      "dy = %f\n"
                      "Jump speed = %f\n"
                      "|%c %c %c|\n"
                      "|%c %c %c|\n"
                      "|%c %c %c|\n"
                        ,x,y,(int)x/32,(int)y/32,energy,heat,dx,dy,jumpSpeed,
                        area->tileTypeXY(x,y),area->tileTypeXY(x+TILE_SIZE,y),area->tileTypeXY(x+TILE_SIZE*2,y),
                        area->tileTypeXY(x,y+TILE_SIZE),area->tileTypeXY(x+TILE_SIZE,y+TILE_SIZE),area->tileTypeXY(x+TILE_SIZE*2,y+TILE_SIZE),
                        area->tileTypeXY(x,y+TILE_SIZE*2+1),area->tileTypeXY(x+TILE_SIZE,y+TILE_SIZE*2+1),area->tileTypeXY(x+TILE_SIZE*2,y+TILE_SIZE*2+1)
                        );
    strcat(debugText,debugData);
    sf::String median = debugText;
    debugInfo.setString(median);
    debugInfo.setPosition(Vector2f(x-100,y-100));
    window->draw(debugInfo);
#endif
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
               strcat(debugText,"STAND LEFT \n");
                       }
            else
            {
                if(type == SOLDIER)
                    cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
                else
                cSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                cSprite.setScale(-1,1);
                cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                strcat(debugText,"STAND RIGHT \n");
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
                        strcat(debugText,"UP RIGHT \n");
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
                        strcat(debugText,"DOWN RIGHT \n");
                    }
                    else
                    {
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setScale(-1,1);
                        cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                        strcat(debugText,"RIGHT \n");
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
                        strcat(debugText,"UP LEFT \n");
                    }
                    else
                    if((curDir & DOWN)!=0)
                    {
                        if(soldierBackFlag) //Same as LEFT | UP to SOLDIER
                            cSprite.setTextureRect(IntRect((3 - (int)currentFrame)*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        else
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setPosition(Vector2f(x+dx,y+dy));
                        strcat(debugText,"DOWN LEFT \n");
                    }
                    else
                    {
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setPosition(Vector2f(x+dx,y+dy));
                        strcat(debugText,"LEFT \n");
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

    if(jumpSpeed > 0)
        jumpSpeed = 0;

    strcat(debugText,"\n");

}

void NPC::updateLogic(){
    strcat(debugText,"LOGIC:\n");
    if(status & SHOOTING)
        status ^= SHOOTING;
    logicAction = AI_IDLE;
if(type == SOLDIER){
    if(std::abs(y-player->y)<=32 && ((player->x-x < 0 && (curDir & LEFT)) || (player->x-x > 0 && (curDir & RIGHT))) ){
        bool wallPresence = false;
        float curX = x;
        while(std::abs(curX-x)<std::abs(player->x-x)){
            if(area->tileTypeXY(curX,y+TILE_SIZE)!='_'){
                wallPresence = true;
                break;
            }
            else
            curX+=2*(player->x-x)/std::abs(player->x-x);
        }
        if(!wallPresence){
            strcat(debugText,"Player detected -> ");
            isTargetDetected = true;
            if(*xLogicTarget!=player->x){
            delete xLogicTarget;
            xLogicTarget = &player->x;
            }
            if(energy > 25 && heat == 0){
                strcat(debugText,"Shooting");
                specialAnimCounter = 3;
                status |= SHOOTING;
                shoot((int)energy%101,(x-player->x > 0),ENERGYBLAST);
            }
            strcat(debugText,"|\n");
        }
    }
    else {
        if(isTargetDetected){
            strcat(debugText,"Searching -> ");
            if(x-player->x > 0){
                logicAction |= AI_LEFT;
                strcat(debugText,"LEFT ");
            }
            else{
                logicAction |= AI_RIGHT;
                strcat(debugText,"RIGHT ");
            }
            if(y-player->x > 0){
                logicAction |= AI_DOWN;
                strcat(debugText,"+ DOWN ");
            }
            else{
                logicAction |= AI_UP;
                strcat(debugText,"+ UP ");
            }
           strcat(debugText,"|\n");
           if(logicAction & AI_RIGHT)
               if(((area->tileTypeXY(x+PLAYER_SIZE+16+dx,y+TILE_SIZE*2+16)!='_') || (area->tileTypeXY(x+PLAYER_SIZE+16+dx,y+TILE_SIZE+16)!='_')) && jumpSpeed >= 0){
                   jumpSpeed = -1;
                   logicAction |= AI_JUMP;
               }
           if(logicAction & AI_LEFT)
               if(((area->tileTypeXY(x-16+dx,y+TILE_SIZE*2+16)!='_') || (area->tileTypeXY(x-16+dx,y+TILE_SIZE+16)!='_')) && jumpSpeed >= 0){
                   jumpSpeed = -1;
                   logicAction |= AI_JUMP;
               }
        }
    }
}

}
