#include "effectlist.h"
#include <string.h>

EffectList::EffectList(RenderWindow *window, float * time)
{
    eImage.loadFromFile("images/Effects.png");
    eTexture.loadFromImage(eImage);
    this->window = window;
    this->time = time;

}

void EffectList::add(float x, float y, char type, char tartype, char dir, void * target){
    eList.push_back(Effect(x,y,time,window,type,tartype,&eTexture,dir,target));
}

void EffectList::update(){
for (int i = 0; i < eList.size() ; i++){
    eList.at(i).update();
    if(eList.at(i).toDelete == true){
        eList.erase(eList.begin()+i);
    }
}
}
