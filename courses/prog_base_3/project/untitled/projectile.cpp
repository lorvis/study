#include "projectile.h"
#include "character.h"
#include "math.h"
Projectile::Projectile(Character * player, float x, float y, float xSpeed, float ySpeed, int type, float * time){
    this->player = player;
    this->x = x;
    this->y = y;
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
    this->type = type;
    this->time = time;
    sf::Image image;
    image.loadFromFile("images/Projectile.png");
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);
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
currentFrame += *time*0.03;
if(currentFrame >=3)
    currentFrame -= 3;
projSprite.setTextureRect(IntRect((int)currentFrame*PROJ_WIDTH,0,PROJ_WIDTH,PROJ_HEIGHT));
if(xSpeed > 0)
projSprite.setScale(-1,1);
projSprite.setPosition(Vector2f(x+dx,y+dy));
projSprite.setScale(1,1);
}

void Projectile::update(){
    dx = 0;
    dy = 0;
    if(abs(xSpeed - (xSpeed/fabs(xSpeed)*0.00002*(*time)))<0.001)
        xSpeed = 0.001;
    if(abs(xSpeed - (xSpeed/fabs(xSpeed)*0.00002*(*time)))>0.001)
        xSpeed = xSpeed - (xSpeed/fabs(xSpeed)*0.00002*(*time));
    if(abs(ySpeed - (ySpeed/fabs(ySpeed)*0.00002*(*time)))<0.001)
        ySpeed = 0.001;
    if(abs(ySpeed - (ySpeed/fabs(ySpeed)*0.00002*(*time)))>0.001)
        ySpeed = ySpeed - (ySpeed/fabs(ySpeed)*0.00002*(*time));
    dx = xSpeed;
    dy = ySpeed;
    updateFrame();
    x+= dx;
    y+= dy;
}

//bool Projectile::isHit(){
//if(!(type & LASER)) {
//    if(type)
//}
//}
