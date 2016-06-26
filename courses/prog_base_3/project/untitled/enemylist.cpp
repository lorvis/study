#include "enemylist.h"

EnemyList::EnemyList(RenderWindow *window, Map *area, Character *player, ProjectileList *pList, float *time)
{
    ememyImg.loadFromFile("images/EnemySoldier.png");
    enemyTexture.loadFromImage(ememyImg);
    dFont.loadFromFile("text/arial.ttf");
    this->time = time;
    this->window = window;
    this->area = area;
    this->player = player;
    this->pList = pList;
    allDefeated = false;
    update = &EnemyList::checkNPC;
}

void EnemyList::add(float x, float y, char cType){
    npcVector.push_back(NPC(area,window,time,x,y,&enemyTexture,pList,cType,player));
    npcVector.at(npcVector.size()-1).debugInfo.setFont(dFont);
}

void EnemyList::checkNPC(void){
    if(npcVector.size() > 0){
        Character *charPt;
        for(int i = 0; i < npcVector.size(); i++){
            charPt = &(npcVector.at(i));
            charPt->update();
            if(charPt->checkForProj()){
                npcVector.erase(npcVector.begin()+i);
                if(npcVector.size() == 0)
                    update = &EnemyList::win;
                else
                    i--;
            }
        }
    }
}

void EnemyList::win(){
    allDefeated = true;
}
