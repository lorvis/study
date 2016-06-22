#include "projectile.h"
#include "character.h"
#include "math.h"
#include "effect.h"
Projectile::Projectile(float energy, sf::RenderWindow * window, float x, float y, float xSpeed, float ySpeed, int type, float * time, int id, sf::Texture * projTexture){
    this->energy = energy;
    this->x = x;
    this->y = y;
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
    this->type = type;
    this->time = time;
    this->id = id;
    projSprite.setTexture(*projTexture);
    this->window = window;
#ifdef PROJ_DEBUG
    debugInfo.setColor(Color(255,0,0));
    debugInfo.setCharacterSize(12);
    debugInfo.setStyle(sf::Text::Regular);
#endif
}

float Projectile::getX(){
return x;
}

float Projectile::getY(){
return y;
}

void Projectile::accelerate(float xAccel, float yAccel){
xSpeed+=xAccel;
ySpeed+=yAccel;
}

void Projectile::updateFrame(){
currentFrame += *time*0.003;
if(currentFrame >=3)
    currentFrame -= 3;
projSprite.setTextureRect(IntRect((int)currentFrame*PROJ_WIDTH,0,PROJ_WIDTH,PROJ_HEIGHT));
if(xSpeed > 0)
projSprite.setScale(-1,1);
projSprite.setPosition(Vector2f(x+dx,y+dy));
window->draw(projSprite);
projSprite.setScale(1,1);
}

void Projectile::update(){
    if(std::abs(xSpeed) > 0.8)
        xSpeed -= 0.00002*(*time)*(xSpeed/std::abs(xSpeed))*abs(xSpeed)*energy;
    if(std::abs(ySpeed) > 0.8)
        ySpeed -= 0.00002*(*time)*(ySpeed/std::abs(ySpeed))*energy;
    dx = xSpeed*energy;
    dy = ySpeed*energy;
    updateFrame();
    x+= dx;
    y+= dy;
#ifdef PROJ_DEBUG
    char debugData[200];
    sprintf(debugData,"\nCoord:[%.2f,%.2f]\n"
                      "TileCoord:[%i,%i]\n"
                      "dx = %f\n"
                      "dy = %f\n"
                      "xSpeed = %f\n"
                      "ySpeed = %f\n"
                        ,x,y,(int)x/32,(int)y/32,dx,dy,xSpeed,ySpeed
                        );
    sf::String median = std::string(debugData);
    debugInfo.setString(median);
    debugInfo.setPosition(Vector2f(x-100,y-100));
    window->draw(debugInfo);
#endif
}

int Projectile::getID(){
    return id;
}

bool Projectile::isThere(float x, float y, float width, float height){
    if(this->x > x && this->y > y && this->x < x+width && this->y < y+height)
        return true;
    else
        return false;
}

char Projectile::getDir(){
    if(std::abs(dx) > std::abs(dy)){
        if(dx > 0)
            return ERIGHT;
        else
            return ELEFT;
    }
    else if (std::abs(xSpeed) < std::abs(ySpeed)) {
        if(dy > 0)
            return EDOWN;
        else
            return EUP;
    }
    else return NODIR;
}
