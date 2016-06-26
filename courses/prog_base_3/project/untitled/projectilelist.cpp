#include "projectilelist.h"
#include <vector>

ProjectileList::ProjectileList(sf::RenderWindow * window, float *time, Map *area, EffectList *effects)
{
    projImage.loadFromFile("images/Effects.png");
    projTexture.loadFromImage(projImage);
    this->window = window;
    this->time = time;
    this->area = area;
    this->effects = effects;
}

void ProjectileList::add(float energy, float x, float y, float xSpeed, float ySpeed, int type, char origin){
    pVector.push_back(Projectile(energy,window,x,y,xSpeed,ySpeed,type,time,currentID,&projTexture,origin));
    currentID++;
}

Projectile * ProjectileList::get(int index){
    return &(pVector.at(index));
}

Vector2i ProjectileList::remove(int index){
    Vector2i res;
    res.x = (int)pVector.at(index).getEnergy();
    res.y = (int)pVector.at(index).getOrigin();
    pVector.erase(pVector.begin()+index);
    return res;
}

void ProjectileList::updateList(){
    for(unsigned int i = 0; i < pVector.size();i++){
        if(!isProjectileCollide(pVector.at(i)))
            pVector.at(i).update();
        else
        {
            Projectile * toDel = &pVector.at(i);
            effects->add(toDel->getX(),toDel->getY(),ENERGYBOOM,EFFECT_NOTYPE,toDel->getDir(),NULL);
            pVector.erase(pVector.begin()+i);
            if(i > 0)
            i--;
        }
    }
}

bool ProjectileList::isProjectileCollide(Projectile proj){
    //50 -> PROJ_WIDTH, 20 -> PROJ HEIGHT
    return area->tileTypeXY(proj.getX(),proj.getY())!='_' \
            ||  area->tileTypeXY(proj.getX(),proj.getY()+10)!='_' \
            ||  area->tileTypeXY(proj.getX(),proj.getY()+20)!='_' \
            ||  area->tileTypeXY(proj.getX()+10,proj.getY())!='_' \
            ||  area->tileTypeXY(proj.getX()+10,proj.getY()+20)!='_' \
            ||  area->tileTypeXY(proj.getX()+10,proj.getY()+10)!='_';
}


bool ProjectileList::checkRect(int index,char origin, float x1, float y1, float x2, float y2){
    Projectile * toCheck = &(pVector.at(index));
    if(toCheck->getOrigin() == origin)
        return false;
    else
        if(isInRect(toCheck->getX(),toCheck->getY(),x1,y1,x2,y2))
        return true;
}

bool isInRect(float x, float y, float x1, float y1, float x2, float y2){
    if(std::abs(x1-x) <= std::abs(x1-x2) && std::abs(x2-x) <= std::abs(x1-x2) && std::abs(y1-y) <= std::abs(y1-y2) && std::abs(x2-x) <= std::abs(x1-x2) )
        return true;
    else
        return false;
}
