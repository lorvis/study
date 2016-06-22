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

void ProjectileList::add(float energy, float x, float y, float xSpeed, float ySpeed, int type){
    pList.push_back(Projectile(energy,window,x,y,xSpeed,ySpeed,type,time,currentID,&projTexture));
    currentID++;
}

Projectile * ProjectileList::get(int index){
    return &(pList.at(index));
}

void ProjectileList::updateList(){
    for(unsigned int i = 0; i < pList.size();i++){
        if(!isProjectileCollide(pList.at(i)))
            pList.at(i).update();
        else
        {
            Projectile * toDel = &pList.at(i);
            effects->add(toDel->getX(),toDel->getY(),ENERGYBOOM,EFFECT_NOTYPE,toDel->getDir(),NULL);
            pList.erase(pList.begin()+i);
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

void ProjectileList::deleteByIndex(int index){
    if(index >=0 && index < pList.size())
     pList.erase(pList.begin()+index);
}
