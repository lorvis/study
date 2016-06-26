#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include "character.h"
#include "map.h"
#include "view.h"
#include "npc.h"
#include "projectilelist.h"
#include "effectlist.h"
#include "enemylist.h"

using namespace sf;

bool gameStartUp(Character * player);
void gameShutDown(Character * player);

enum gameStatus { GS_NONE = 0, GS_NEWGAME = 2, GS_LOADED = 4, GS_WIN = 8, GS_DEFEAT = 16 };

int main()
{
    float time = 0;
    RenderWindow window(VideoMode(1280, 1024), "some sheet");
    window.setVerticalSyncEnabled(true);
    sf::Image pImg;
    pImg.loadFromFile("images/pSprite2.png");
    sf::Texture pTexture;
    pTexture.loadFromImage(pImg);

    Map map("test","tiles.png",&window);
    EffectList effects(&window,&time);
    ProjectileList projectiles(&window,&time,&map,&effects);
    Character player(&map,&window,&time,200,100,&pTexture,&projectiles);
    EnemyList enemies(&window,&map,&player,&projectiles,&time);
    enemies.add(300,100,SOLDIER);
    enemies.add(600,100,SOLDIER);

    gameStartUp(&player);

#ifdef CHAR_DEBUG
    sf::Font dFont;
    dFont.loadFromFile("text/arial.ttf");
    player.debugInfo.setFont(dFont);
#endif

    sf::Font eFont;
    player.energyInfo.setFont(eFont);
    eFont.loadFromFile("text/biting my nails.ttf");
    Camera cam(0,0,1280,1024);
    Clock clock;
//    NPC npcSample();

    while (window.isOpen())
    {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/320;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                gameShutDown(&player);
                window.close();
            }
        }

        window.clear(Color(20,20,20));
        map.update();
        player.update();
        enemies.update(enemies);
        projectiles.updateList();
        effects.update();
        cam.setPos(player.getX(),player.getY());
        window.setView(cam.getView());
        window.display();
        if(player.defeated || enemies.allDefeated) {
            gameShutDown(&player);
            window.close();
        }
    }

    return 0;

    }



bool gameStartUp(Character * player){
    std::ifstream saveFile;
    saveFile.open("save/CharSaves.txt");
    std::string curLine;
    std::getline(saveFile,curLine);
    if(curLine.compare("--OK--")==0){
    while(!saveFile.eof())
    {
       std::getline(saveFile,curLine);
       if(curLine.find("x ")!=std::string::npos && curLine.find("dx ")==std::string::npos)
           player->x = atof(curLine.substr(strlen("x "),curLine.length()).c_str());
       if(curLine.find("y ")!=std::string::npos && curLine.find("dy ")==std::string::npos)
           player->y = atof(curLine.substr(strlen("y "),curLine.length()).c_str());
       if(curLine.find("dx ")!=std::string::npos)
           player->dx = atof(curLine.substr(strlen("dx "),curLine.length()).c_str());
       if(curLine.find("dy ")!=std::string::npos)
           player->dy = atof(curLine.substr(strlen("dy "),curLine.length()).c_str());
       if(curLine.find("status ")!=std::string::npos)
           player->status = curLine.at(strlen("status "));
       if(curLine.find("dir ")!=std::string::npos)
           player->curDir = player->status = curLine.at(strlen("dir "));
    }
        saveFile.close();
    }
    else
        return false;
    return true;
}

void gameShutDown(Character * player){
    std::ofstream saveStream;
    saveStream.open("save/CharSaves.txt",std::ios_base::trunc);
    saveStream << "--OK--\n";
    saveStream << "x " << player->x << '\n';
    saveStream << "y " << player->y << '\n';
    saveStream << "dx " << player->dx << '\n';
    saveStream << "dy " << player->dy << '\n';
    saveStream << "status " << player->status << '\n';
    saveStream << "dir " << player->curDir << '\n';
}

