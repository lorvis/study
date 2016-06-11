#include "player.h"
#include <math.h>
#include <string.h>
#define PI 3.141592653589793

Character::Character(float startX, float startY, Map * pMap, RenderWindow * pWindow, float * time)
{
    pImage.loadFromFile("images/pSprite2.png");
    pTexture.loadFromImage(pImage);
    pSprite.setTexture(pTexture);
    x = startX;
    y = startY;
    area = pMap;
    window = pWindow;
    this->time = time;
    debugInfo.setColor(Color(255,0,0));
    debugInfo.setCharacterSize(12);
    debugInfo.setStyle(sf::Text::Regular);
}

float Character::getX() {
    return x;
}

float Character::getY() {
    return y;
}

void Character::updateFrame(char dir) {
    if(isSpinning){
        strcat(debugText,"1.Spinning : TRUE \n");
     currentFrame+=(*time)*0.0003;
    }
    else{
        currentFrame+=(*time)*0.003;
        strcat(debugText,"1.Spinning : FALSE \n");
    }
if(dir == (RIGHT | SPIN) || dir == (LEFT | SPIN)) {
    if(!isSpinning){
        isSpinning = true;
        currentFrame = 0;
    }
    //debug
    if(dir == (RIGHT | SPIN))
        strcat(debugText,"1.RIGHT | SPIN\n");
    else
        strcat(debugText,"1.LEFT | SPIN\n");
    //
}
if(currentFrame >= 4) {
    if(isSpinning)
        isSpinning = false;
    currentFrame-=4;
}
if(isSpinning) {
if((dir & RIGHT) !=0) {
    pSprite.setTextureRect(IntRect((int)(3 -currentFrame)*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setScale(-1,1);
    pSprite.setPosition(Vector2f(x+dx-PLAYER_SIZE,y+dy));
    //debug
    if((dir & UP) != 0)
        strcat(debugText,"1.RIGHT | UP\n");
    else if ((dir & DOWN) != 0)
        strcat(debugText,"1.RIGHT | DOWN\n");
    else
        strcat(debugText,"1.RIGHT\n");
    //
}
if((dir & LEFT) !=0) {
    pSprite.setTextureRect(IntRect((int)(3 -currentFrame)*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    //debug
    if((dir & UP) != 0)
        strcat(debugText,"1.LEFT | UP\n");
    else if ((dir & DOWN) != 0)
        strcat(debugText,"1.LEFT | DOWN\n");
    else
        strcat(debugText,"1.LEFT\n");
    //
}

}
else {
if(dir == NODIR){ //same as down
    pSprite.setTextureRect(IntRect(PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    strcat(debugText,"1.NODIR\n");
    }
if(dir == LEFT){
    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    strcat(debugText,"1.LEFT\n");
}
if(dir == RIGHT){
    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setScale(-1,1);
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    strcat(debugText,"1.RIGHT\n");
}
if(dir == (DOWN | RIGHT)){
    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setScale(-1,1);
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    strcat(debugText,"1.RIGHT | DOWN\n");
    }
if(dir == (DOWN | LEFT)){
    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setScale(-1,1);
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    strcat(debugText,"1.LEFT | DOWN\n");
}
if(dir == (UP | LEFT)){
    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    strcat(debugText,"1.LEFT | UP\n");
}
if(dir == (UP | RIGHT)){
    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
    pSprite.setScale(-1,1);
    pSprite.setPosition(Vector2f(x+dx,y+dy));
    strcat(debugText,"1.RIGHT | UP\n");
}
}
curDir = dir;
window->draw(pSprite);
pSprite.setScale(-1,1);
}

void Character::updateFrame(){
    currentFrame+=(*time)*0.003;
    if(curDir == NODIR){
        pSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
        pSprite.setPosition(Vector2f(x+dx,y+dy));
    }
    if(currentFrame>=4)
    {
        isSpinning = false;
        currentFrame = 0;
    }
        if((curDir & STAND)!=0)
        {
            isSpinning = false;
            currentFrame = 0;
            if((curDir & LEFT)!=0)
            {
                pSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
               pSprite.setPosition(Vector2f(x+dx,y+dy));
               strcat(debugText,"STAND LEFT \n");
                       }
            else
            {
                pSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                pSprite.setScale(-1,1);
                pSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                strcat(debugText,"STAND RIGHT \n");
            }
    }
        if(!isSpinning && (curDir & SPIN)!=0)
        {
            currentFrame = 0;
            isSpinning = true;
        }
        if(isSpinning){
            if(currentFrame>=4)
            {
                isSpinning = false;
                currentFrame = 0;
            }
            else
            {
                if((curDir & LEFT)!=0)
                {
                    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
                    pSprite.setPosition(Vector2f(x+dx,y+dy));
                    strcat(debugText,"SPIN LEFT \n");
                }
                if((curDir & RIGHT)!=0)
                {
                    pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
                    pSprite.setScale(-1,1);
                    pSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                    strcat(debugText,"SPIN RIGHT \n");
                }

        }
        }
        else
        {
            if((curDir & STAND)==0)
            {
                if((curDir & RIGHT)!=0){
                    if((curDir & UP)!=0)
                    {
                        pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                        pSprite.setScale(-1,1);
                        pSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                        strcat(debugText,"UP RIGHT \n");
                    }
                    else
                    if((curDir & DOWN)!=0)
                    {
                        pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        pSprite.setScale(-1,1);
                        pSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                        strcat(debugText,"DOWN RIGHT \n");
                    }
                    else
                    {
                        pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
                        pSprite.setScale(-1,1);
                        pSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                        strcat(debugText,"RIGHT \n");
                    }
                }
                if((curDir & LEFT)!=0){
                    if((curDir & UP)!=0)
                    {
                        pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                        pSprite.setPosition(Vector2f(x+dx,y+dy));
                        strcat(debugText,"UP LEFT \n");
                    }
                    else
                    if((curDir & DOWN)!=0)
                    {
                        pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,0,PLAYER_SIZE,PLAYER_SIZE));
                        pSprite.setPosition(Vector2f(x+dx,y+dy));
                        strcat(debugText,"DOWN LEFT \n");
                    }
                    else
                    {
                        pSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE,PLAYER_SIZE));
                        pSprite.setPosition(Vector2f(x+dx,y+dy));
                        strcat(debugText,"LEFT \n");
                    }
                }
            }
        }
    window->draw(pSprite);
    pSprite.setScale(1,1);
}

void Character::checkstatus() {

    status = IDLE;

    if(Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A)) {
       status |= BACKWARD;
        }
    if(Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D)) {
        status |= FORWARD;
       }
    if(Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::W)) {
        status |= JUMP;
        }
    if(Keyboard::isKeyPressed(Keyboard::Down)||Keyboard::isKeyPressed(Keyboard::S)) {
        status |= COACH;
    }
}

char Character::checkTileAtP(char dir, int tile){
    if(tile < 0 || tile > 2)
    {
        std::cerr << "Wrong index in checkTileAtP" << std::endl;
        return '\0';
    }
    if(dir == RIGHT) {
        return area->tileTypeXY(x+PLAYER_SIZE+dx,y+dy+(tile)*TILE_SIZE);
    }
    if(dir == UP) {
        return area->tileTypeXY(x+dx+(tile)*TILE_SIZE,y+dy);
    }
    if(dir == LEFT) {
        return area->tileTypeXY(x+dx,y+dy+tile*TILE_SIZE);
    }
    if(dir == DOWN) {
        return area->tileTypeXY(x+dx+tile*TILE_SIZE,y+dy+PLAYER_SIZE);
    }
    if(dir == (DOWN | LEFT)) {
        return area->tileTypeXY(x+dx,y+PLAYER_SIZE);
    }
    if(dir == (DOWN | RIGHT)) {
        return area->tileTypeXY(x+dx+PLAYER_SIZE,y+dy+PLAYER_SIZE);
    }
    if(dir == (UP | LEFT)) {
        return area->tileTypeXY(x+dx,y+dy);
    }
    if(dir == (UP | RIGHT)) {
        return area->tileTypeXY(x+dx+PLAYER_SIZE,y+dy);
    }
    std::cerr << "Wrong direction in checkTileAtP" << std::endl;
    return '\0';
}

void Character::enspeed(){

    dx = 0;
    dy = 0;

    if((status & BACKWARD) != 0 && (status & FORWARD) == 0) {
    dx+= *time*speed*(-0.1);
    }
    if((status & FORWARD) != 0 && (status & BACKWARD) == 0 ) {
    dx+= *time*speed*(0.1);
    }
    if((status & JUMP) != 0 && (status & COACH) == 0 ) {
    dy+= *time*speed*(-0.1);
    }
    if((status & COACH) != 0 && (status & JUMP) == 0 ) {
    dy+= *time*speed*(0.1);
    }

    if(dx > 0){
       for(int i = 0; i < 3; i++){
           if(checkTileAtP(RIGHT,i)!='_') {
               dx =0;
               break;
           }
       }
    }
    if(dx < 0){
        for(int i = 0; i < 3; i++){
            if(checkTileAtP(LEFT,i)!='_') {
                dx =0;
                break;
            }
        }
    }
    if(dy > 0){
        for(int i = 0; i < 3; i++){
            if(checkTileAtP(DOWN,i)!='_') {
                dy =0;
                break;
            }
        }
    }
    if(dy < 0){
        for(int i = 0; i < 3; i++){
            if(checkTileAtP(UP,i)!='_') {
                dy =0;
                break;
            }
        }
    }

}

void Character::checkDir(){
    if((curDir & LEFT)!=0 && dx > 0 )
    {
        if(dy == 0)
            curDir = RIGHT | SPIN;
        if(dy > 0)
            curDir = RIGHT | DOWN | SPIN;
        if(dy < 0)
            curDir = RIGHT | UP | SPIN;
    }
    else
        if((dx > 0|| (dx==0 && dy!=0)))
        {
            if(dy == 0)
                curDir = RIGHT;
            if(dy > 0)
                curDir = RIGHT | DOWN;
            if(dy < 0)
                curDir = RIGHT | UP;
        }
    if((curDir & RIGHT)!=0 && dx < 0 )
    {
        if(dy == 0)
            curDir = LEFT | SPIN;
        if(dy > 0)
            curDir = LEFT | DOWN | SPIN;
        if(dy < 0)
            curDir = LEFT | UP | SPIN;
    }
    else
        if((dx < 0 || (dx==0 && dy!=0)))
        {
            if(dy == 0)
                curDir = LEFT;
            if(dy > 0)
                curDir = LEFT | DOWN;
            if(dy < 0)
                curDir = LEFT | UP;
        }
    if((curDir & LEFT)!=0 && dx == 0 && dy == 0)
        curDir = STAND | LEFT;
    if((curDir & RIGHT)!=0 && dx == 0 && dy == 0)
        curDir = STAND | RIGHT;
}

void Character::update() {
sprintf(debugText,"");
checkstatus();
enspeed();
checkDir();
updateFrame();
x+=dx;
y+=dy;
char dxdyInfo[100];
sprintf(dxdyInfo,"dx = %f\ndy = %f\n",dx,dy);
strcat(debugText,dxdyInfo);
sf::String median = debugText;
debugInfo.setString(median);
//window->draw(pDebugInfo);
}
