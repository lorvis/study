#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include "character.h"
#include "map.h"
#include "view.h"
#include "npc.h"
#include "projectile.h"

using namespace sf;

bool gameStartUp(Character * player);
void gameShutDown(Character * player);


int main()
{
    float time = 0;
    RenderWindow window(VideoMode(1280, 1024), "some sheet");
    window.setVerticalSyncEnabled(true);

    Map map("test","tiles.png",&window);
    sf::Image projImage;
    projImage.loadFromFile("images/Projectile.png");
    sf::Texture projTexure;
    projTexure.loadFromImage(projImage);
    ProjectileList projectiles(&window,&time,&projTexure);

    Character player(&map,&window,&time,200,100,(char *)"pSprite2.png",&projectiles);
    Character * enemy;
    NPC newEnemy(&map,&window,&time,300,100,(char *)"EnemySoldier.png",&projectiles,SOLDIER,&player);
        enemy = &newEnemy;

    gameStartUp(&player);

#ifdef CHAR_DEBUG
    sf::Font font;
    font.loadFromFile("text/arial.ttf");
    player.debugInfo.setFont(font);
    newEnemy.debugInfo.setFont(font);
#endif

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
        enemy->update();
        projectiles.updateList();
        cam.setPos(player.getX(),player.getY());
        window.setView(cam.getView());
        window.display();
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

