#include "projectilelist.h"
#include <vector>

ProjectileList::ProjectileList(sf::RenderWindow * window, float *time, sf::Texture *projTexture)
{
    this->projTexture = projTexture;
    this->window = window;
    this->time = time;
}

void ProjectileList::add(float energy, float x, float y, float xSpeed, float ySpeed, int type){
    pList.push_back(Projectile(energy,window,x,y,xSpeed,ySpeed,type,time,currentID,projTexture));
    currentID++;
}

Projectile * ProjectileList::get(int index){
    return &(pList.at(index));
}

void ProjectileList::updateList(){
    for(unsigned int i = 0; i < pList.size();i++){
        targetID = -1;
        pList.at(i).update();
        if(targetID >= 0)
            for(unsigned int j = 0; j < pList.size();i++){
                if(pList.at(j).getID() == targetID)
                    pList.erase(pList.begin()+j);
            }
    }
}
