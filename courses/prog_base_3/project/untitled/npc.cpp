#include "npc.h"
#include "character.h"
#include <string.h>

void NPC::update(){
    sprintf(debugText,"");
    checkstatus();
    enspeed();
    checkDir();
    updateFrame();
    x+=dx;
    y+=dy;
#ifdef CHAR_DEBUG
    char debugData[200];
    sprintf(debugData,"\nCoord:[%.2f,%.2f]\n"
                      "TileCoord:[%i,%i]\n"
                      "dx = %f\n"
                      "dy = %f\n"
                      "Jump speed = %f\n"
                      "|%c %c %c|\n"
                      "|%c %c %c|\n"
                      "|%c %c %c|\n"
                        ,x,y,(int)x/32,(int)y/32,dx,dy,jumpSpeed,
                        area->tileTypeXY(x,y),area->tileTypeXY(x+TILE_SIZE,y),area->tileTypeXY(x+TILE_SIZE*2,y),
                        area->tileTypeXY(x,y+TILE_SIZE),area->tileTypeXY(x+TILE_SIZE,y+TILE_SIZE),area->tileTypeXY(x+TILE_SIZE*2,y+TILE_SIZE),
                        area->tileTypeXY(x,y+TILE_SIZE*2+1),area->tileTypeXY(x+TILE_SIZE,y+TILE_SIZE*2+1),area->tileTypeXY(x+TILE_SIZE*2,y+TILE_SIZE*2+1)
                        );
    strcat(debugText,debugData);
    sf::String median = debugText;
    debugInfo.setString(median);
    debugInfo.setPosition(Vector2f(x-100,y-100));
#endif
    window->draw(debugInfo);
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

    if((status & BACKWARD) != 0 && (status & FORWARD) == 0) {
    dx+= *time*speed*(-0.1);
    }
    if((status & FORWARD) != 0 && (status & BACKWARD) == 0 ) {
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
        strcat(debugText,"IN AIR ");
    }

    if(jumpSpeed > 0)
        jumpSpeed = 0;

    if(jumpSpeed == 0)
    {
        status = IDLE;
    if(Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::W)) {
        status |= JUMP;
        strcat(debugText,"JUMPED ");
        jumpSpeed = -1;
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A)) {
       status |= BACKWARD;
       strcat(debugText,"BACKWARD");
        }
    if(Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D)) {
        status |= FORWARD;
        strcat(debugText,"FORWARD");
       }
    strcat(debugText,"\n");

}
