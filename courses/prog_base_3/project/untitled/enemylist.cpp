#include "enemylist.h"

EnemyList::EnemyList(RenderWindow *window, Map *area, Character *player, ProjectileList *pList, float *time, charSBpack *sbPack)
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
    this->sbPack = sbPack;
    deathS.setBuffer(sbPack->deathSB);
    deathS.setVolume(5);

    for(int i = 0; i < area->getW() ; i++){
        for(int j = 0; j < area->getH(); j++){
            if(area->charmap[i][j] == 'e')
                add(32*i+16,32*j+16,SOLDIER);
        }
    }
}

void EnemyList::add(float x, float y, char cType){
    npcVector.push_back(NPC(area,window,time,x,y,&enemyTexture,pList,cType,player,sbPack));
    npcVector.at(npcVector.size()-1).debugInfo.setFont(dFont);
}

void EnemyList::checkNPC(void){
    if(npcVector.size() > 0){
        Character *charPt;
        for(int i = 0; i < npcVector.size(); i++){
            charPt = &(npcVector.at(i));
            charPt->update();
            if(charPt->checkForProj()){
                deathS.play();
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
