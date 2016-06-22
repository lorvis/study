#include "effect.h"
#include "projectile.h"
Effect::Effect(float x, float y, float * time, sf::RenderWindow * window, char type, char tarType, sf::Texture * eTexture, char dir, void * target)
{
    if(target == NULL)
        xyPointed = false;
    *(this->x) = x;
    *(this->y) = y;
    this->type = type;
    this->dir = dir;
    this->time = time;
    this->window = window;
    if(type & ENERGYBOOM || type & EPROJ)
    {
        effectTimer = 4;
        animationSpeed = 0.009;
        effectWidth = 50;
        effectHeight = 20;
    }
    switch(type){
    case ENERGYBOOM :
        effectTextureY = 20;
        break;
    case EPROJ :
        effectTextureY = 0;
        break;
    }
    this->eTexture = eTexture;
    this->tarType = tarType;
    this->target = target;
    toDelete = false;
    eSprite.setTexture(*eTexture);
}

void Effect::update(){
    effectTimer -= animationSpeed*(*time);
    if(effectTimer <= 0)
        toDelete = true;
    else {
        eSprite.setTextureRect(sf::IntRect((int)effectTimer*effectWidth,effectHeight,effectWidth,effectHeight));
        if(dir == ERIGHT){
            eSprite.setScale(-1,1);
            eSprite.setPosition(sf::Vector2f(*x+8,*y+8));
        }
        else
            eSprite.setPosition(sf::Vector2f(*x,*y));
            window->draw(eSprite);
            eSprite.setScale(1,1);
    }
}
