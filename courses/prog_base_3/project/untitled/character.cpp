#include "character.h"
#include <math.h>
#include <string.h>
#define PI 3.141592653589793

Character::Character(Map * pMap, RenderWindow * pWindow, float * time, float x, float y, Texture *cTexture, ProjectileList *allProj, charSBpack *sbPack)
{
    type = PLAYER;
    cSprite.setTexture(*cTexture);
    specialAnimCounter = 0;
    this->x = x;
    this->y = y;
    energy = 0;
    heat = 0;
    currentFrame = 0;
    speed = 1;
    pList = allProj;
    dx =0;
    dy =0;
    status = IDLE;
    area = pMap;
    window = pWindow;
    this->time = time;
    energyInfo.setColor(Color(40,40,255));
    energyInfo.setCharacterSize(36);
    energyInfo.setStyle(sf::Text::Regular);
    curDir = RIGHT | STAND;
    shotS.setBuffer(sbPack->shotSB);
    deathS.setBuffer(sbPack->deathSB);
    absorbS.setBuffer(sbPack->absSB);
    shotS.setVolume(5);
    deathS.setVolume(1);
    absorbS.setVolume(5);
}

float Character::getX() {
    return x;
}

float Character::getY() {
    return y;
}


void Character::updateFrame(){
    currentFrame+=(*time)*0.003;
    if(curDir == NODIR){
        cSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
        cSprite.setPosition(Vector2f(x+dx,y+dy));
    }
    if(currentFrame>=4)
    {
        isSpinning = false;
        currentFrame = 0;
    }
    //STAND
        if((curDir & STAND)!=0)
        {
            isSpinning = false;
            currentFrame = 0;
            if((curDir & LEFT)!=0)
            {
                cSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
               cSprite.setPosition(Vector2f(x+dx,y+dy));
                       }
            else
            {
                cSprite.setTextureRect(IntRect(2*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                cSprite.setScale(-1,1);
                cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
            }
    }
        if(!isSpinning && (curDir & SPIN)!=0)
        {
            currentFrame = 0;
            isSpinning = true;
        }
        //SPIN
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
                    cSprite.setTextureRect(IntRect((int)(3 - currentFrame)*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
                    cSprite.setPosition(Vector2f(x+dx,y+dy));
                }
                if((curDir & RIGHT)!=0)
                {
                    cSprite.setTextureRect(IntRect((int)(3 - currentFrame)*PLAYER_SIZE,PLAYER_SIZE*2,PLAYER_SIZE,PLAYER_SIZE));
                    cSprite.setScale(-1,1);
                    cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                }

        }
        }
        else
        {
            //SIMPLE
            if((curDir & STAND)==0)
            {
                if((curDir & RIGHT)!=0){
                    if((curDir & UP)!=0)
                    {
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setScale(-1,1);
                        cSprite.setPosition(Vector2f(x+dx+PLAYER_SIZE,y+dy));
                    }
                    else
                    if((curDir & DOWN)!=0)
                    {
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
                        cSprite.setTextureRect(IntRect((int)currentFrame*PLAYER_SIZE,PLAYER_SIZE*3,PLAYER_SIZE,PLAYER_SIZE));
                        cSprite.setPosition(Vector2f(x+dx,y+dy));
                    }
                    else
                    if((curDir & DOWN)!=0)
                    {
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

void Character::checkstatus() {

    status = IDLE;

    if(heat > 0)
        heat -= 0.05*(*time);
    if(heat < 0)
        heat = 0;

    if(!(boostTimer > 0))
    {
        boostTimer = 0;
        speed = 1;
    }
    else
    {
        boostTimer-=0.03*(*time);
        speed = 3;
    }

    if(Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A)) {
       status |= BACKWARD;
        }

    if(Keyboard::isKeyPressed(Keyboard::Q)||Keyboard::isKeyPressed(Keyboard::E)) {
      energy = 160;
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
    if(Keyboard::isKeyPressed(Keyboard::Z)||Keyboard::isKeyPressed(Keyboard::O)) {
        status ^= ABSORBING;
    }
    if(!(status & ABSORBING))
    {

        if(Keyboard::isKeyPressed(Keyboard::Space)||Keyboard::isKeyPressed(Keyboard::LShift))
        {
            if(energy > 150)
            shoot(150,(curDir & LEFT),ENERGYBLAST);
        }
    }
    if((Keyboard::isKeyPressed(Keyboard::X)||Keyboard::isKeyPressed(Keyboard::I))&& boostTimer == 0 && energy > 50) {
        boostTimer = 50;
        energy-=50;
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

    collision();


}

bool Character::collision(){
    bool dxhalt = false;
    bool dyhalt = false;
    if(dx < 0) {
        for(int i = 0; i < PLAYER_SIZE/TILE_SIZE; i++){
            if(area->tileTypeXY(x+dx-16,y+dy+TILE_SIZE*i)!='_')
            {
                dxhalt = true;
                dx = 0;
            }
        }
        if(dxhalt == false && area->tileTypeXY(x+dx,y+dy+PLAYER_SIZE-1)!='_') {
            dxhalt = true;
            dx = 0;
        }
    }
    if(dx > 0 && !dxhalt) {
        for(int i = 0; i < PLAYER_SIZE/TILE_SIZE; i++){
            if(area->tileTypeXY(x+dx+PLAYER_SIZE+16,y+dy+TILE_SIZE*i)!='_')
            {
                dxhalt = true;
                dx = 0;
            }
        }
        if(dxhalt == false && area->tileTypeXY(x+dx+TILE_SIZE*3-1,y+dy+TILE_SIZE*3-1)!='_') {
            dxhalt = true;
            dx = 0;
        }
    }
    if(dy < 0) {
        for(int i = 0; i < PLAYER_SIZE/TILE_SIZE; i++){
            if(area->tileTypeXY(x+dx+TILE_SIZE*i,y+dy-1)!='_')
            {
                dyhalt = true;
                dy = 0;
            }
        }
        if(dyhalt == false && area->tileTypeXY(x+dx+TILE_SIZE*3,y+dy)!='_') {
            dyhalt = true;
            dy = 0;
        }
    }
    if(dy > 0) {
        for(int i = 0; i < PLAYER_SIZE/TILE_SIZE; i++){
            if(area->tileTypeXY(x+dx+TILE_SIZE*i,y+dy+TILE_SIZE*3)!='_')
            {
                dyhalt = true;
                dy = 0;
            }
        }
        if(dyhalt == false && area->tileTypeXY(x+dx+TILE_SIZE*3,y+dy+TILE_SIZE*3)!='_') {
            dyhalt = true;
            dy = 0;
        }
    }
    return dxhalt || dyhalt;
}

void Character::checkDir(){
    bool determined = false;
    if((curDir & LEFT)!=0 && dx == 0 && dy == 0)
    {
        curDir = STAND | LEFT;
        determined = true;
    }
    else
    if((curDir & RIGHT)!=0 && dx == 0 && dy == 0)
    {
        curDir = STAND | RIGHT;
        determined = true;
    }
    else {

    if((curDir & LEFT)!=0 && dx > 0 )
    {
        if(dy == 0)
        {
            curDir = RIGHT | SPIN;
            determined = true;
        }
        if(dy > 0)
        {
            curDir = RIGHT | DOWN | SPIN;
            determined = true;
        }
        if(dy < 0)
        {
            curDir = RIGHT | UP | SPIN;
            determined = true;
        }
    }
    else
        if((curDir & RIGHT)!=0 && (dx > 0 || (dx==0 && dy!=0)))
        {
            if(dy == 0)
            {
                curDir = RIGHT;
                determined = true;
            }
            if(dy > 0)
            {
                curDir = RIGHT | DOWN;
                determined = true;
            }
            if(dy < 0)
            {
                curDir = RIGHT | UP;
                determined = true;
            }
        }
    if((curDir & RIGHT)!=0 && dx < 0 )
    {
        if(dy == 0)
        {
            curDir = LEFT | SPIN;
            determined = true;
        }
        if(dy > 0)
        {
            curDir = LEFT | DOWN | SPIN;
            determined = true;
        }
        if(dy < 0)
        {
            curDir = LEFT | UP | SPIN;
            determined = true;
        }
    }
    else
        if((curDir & LEFT)!=0 && (dx < 0 || (dx==0 && dy!=0)))
        {
            if(dy == 0)
            {
                curDir = LEFT;
                determined = true;
            }
            if(dy > 0)
            {
                curDir = LEFT | DOWN;
                determined = true;
            }
            if(dy < 0)
            {
                determined = true;
                curDir = LEFT | UP;
            }
        }
    }
    if(determined == false)
        curDir |= RIGHT;
}

void Character::update() {
    checkstatus();
    enspeed();
    checkDir();
    updateFrame();
    x+=dx;
    y+=dy;
    checkForProj();
    showEnergy();
}

void Character::shoot(float power, bool toLeft, char type){
    char origin;
    if(this->type == PLAYER)
        origin = ORIGIN_PLAYER;
    if(this->type == SOLDIER)
        origin = ORIGIN_SOLDIER;
    if(heat == 0 && power > 0 && power <= energy){
        shotS.setVolume(0.03*power);
        shotS.play();
        pList->add(power,x+TILE_SIZE*2+6-pow(TILE_SIZE,(float)toLeft)*2,y+TILE_SIZE+6,0.18*pow((-1),(float)toLeft),0,type,origin);
        energy -= power;
        heat += power;
    }
}

void Character::die(){
defeated = true;
}

void Character::absorb(int energy){
    if(this->energy+energy <= 300 && (status & ABSORBING)){
        absorbS.play();
        this->energy+=energy;
    }
    else{
        die();
    }
}

bool Character::checkForProj(){
    bool hit = false;
    if(type==PLAYER)
    {
    }
    for(int i = 0; i < pList->pVector.size();i++){
        if(pList->checkRect(i,ORIGIN_PLAYER,x+1,y+TILE_SIZE+1,x+PLAYER_SIZE,y+PLAYER_SIZE)){
            pList->effects->add(pList->pVector.at(i).x,pList->pVector.at(i).y,ASHIELD_EFFECT,NOTARGET,EFFECT_NODIR,NULL);
            Vector2i recievedP = pList->remove(i);
            if(!(status & ABSORBING)){
                die();
            }
            else
                absorb(recievedP.x);
            hit = true;
        }
    }
    return hit;
}

void Character::showEnergy(){
    char energyText[30];
    sprintf(energyText,"Energy %.0f",energy);
    energyInfo.setString(energyText);
    energyInfo.setPosition(x-500,y+300);
    window->draw(energyInfo);
}
