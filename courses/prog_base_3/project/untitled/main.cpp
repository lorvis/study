#include <SFML/Graphics.hpp>
#include <windows.h>
#include "character.h"
#include "map.h"
#include "view.h"
#include "npc.h"
#include "projectilelist.h"
#include "effectlist.h"
#include "enemylist.h"
#include "sqlite3.h"
#include "sqlite.hpp"

using namespace sf;

bool gameStartUp(Character *player, EnemyList *enemies, ProjectileList *projectiles, char gStatus);
void gameShutDown(Character *player, EnemyList *enemies, ProjectileList *projectiles, char gStatus, int mapCount);
char intro(int *mapCount);
char outro(char gStatus, int *mapCount);
void outroWin();
char outroDefeat();

int main()
{
    int mapCount;
    char gStatus = intro(&mapCount);
    if(GS_NEWGAME)
        mapCount = 1;
    if(mapCount == 0){
        gStatus = GS_NEWGAME;
        mapCount = 1;
    }
    float time = 0;
    Image pImg;
    pImg.loadFromFile("images/pSprite2.png");
    charSBpack sbPack;
    sbPack.absSB.loadFromFile("sounds/absorbing.wav");
    sbPack.deathSB.loadFromFile("sounds/death.wav");
    sbPack.shotSB.loadFromFile("sounds/shot.wav");
    Texture pTexture;
    pTexture.loadFromImage(pImg);

    while(mapCount > 0 && mapCount < 4 && (gStatus == GS_NEXT || gStatus == GS_NEWGAME || gStatus == GS_LOADED)){
        if(gStatus == GS_NEXT)
            gStatus = GS_NEWGAME;
    RenderWindow window(VideoMode(1280, 1024), "some sheet");
    window.setVerticalSyncEnabled(true);
    char mapName[5];
    sprintf(mapName,"map%i",mapCount);
    Map map(mapName,"tiles.png",&window,gStatus);
    EffectList effects(&window,&time);
    ProjectileList projectiles(&window,&time,&map,&effects);
    Character player(&map,&window,&time,200,100,&pTexture,&projectiles,&sbPack);
    EnemyList enemies(&window,&map,&player,&projectiles,&time,&sbPack);

    gameStartUp(&player, &enemies, &projectiles, gStatus);

    sf::Font eFont;
    player.energyInfo.setFont(eFont);
    eFont.loadFromFile("text/biting my nails.ttf");
    Camera cam(0,0,1280,1024);
    Clock clock;
//    NPC npcSample();

    sf::Text levelText;
    char levelChars[50] = " ";
    sprintf(levelChars,"LEVEL %i",mapCount);
    levelText.setFont(eFont);
    levelText.setCharacterSize(72);
    levelText.setColor(Color(100,100,255));
    levelText.setPosition(Vector2f(500,450));
    levelText.setString(levelChars);
    window.clear();
    window.draw(levelText);
    window.display();
    Sleep(500);
    window.clear();

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
                gStatus = GS_CLOSED;
                gameShutDown(&player,&enemies,&projectiles,GS_CLOSED,mapCount);
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
        if(enemies.allDefeated) {
            gStatus = GS_WIN;
            gameShutDown(&player,&enemies,&projectiles,GS_WIN,mapCount);
            window.close();
        }
        if(player.defeated) {
            gStatus = GS_DEFEAT;
            gameShutDown(&player,&enemies,&projectiles,GS_DEFEAT,mapCount);
            window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            gStatus = GS_CLOSED;
            gameShutDown(&player,&enemies,&projectiles,GS_CLOSED,mapCount);
            window.close();
        }
    }

    gStatus = outro(gStatus,&mapCount);

    }


    return 0;

    }



bool gameStartUp(Character * player, EnemyList *enemies, ProjectileList *projectiles, char gStatus){
    if(gStatus == GS_LOADED){
        io::sqlite::db saveDB("save.db");
        io::sqlite::stmt playerStmt(saveDB,"SELECT * FROM Player");
        playerStmt.step();
        player->x = playerStmt.row().real(0);
        player->y = playerStmt.row().real(1);
        player->curDir = playerStmt.row().int32(2);
        player->energy = playerStmt.row().real(3);
//        playerStmt.~stmt();
        io::sqlite::stmt eStmt(saveDB,"SELECT * FROM Enemies");
        int i = 0;
        while(eStmt.step()){
            enemies->add(eStmt.row().real(0),eStmt.row().real(1),SOLDIER);
            enemies->npcVector.at(i).jumpSpeed = eStmt.row().real(2);
            enemies->npcVector.at(i).curDir = eStmt.row().int32(3);
            enemies->npcVector.at(i).energy = eStmt.row().real(4);
            enemies->npcVector.at(i).health = eStmt.row().real(5);
            i++;
        }
//        eStmt.~stmt();
        io::sqlite::stmt projStmt(saveDB,"SELECT * FROM Projectiles");
        while(projStmt.step()){
            projectiles->add( \
                        projStmt.row().real(5), \
                        projStmt.row().real(0), \
                        projStmt.row().real(1), \
                        projStmt.row().real(2), \
                        projStmt.row().real(3), \
                        projStmt.row().int32(4), \
                        projStmt.row().int32(6) \
                             );
        }
    }
    else
        return false;
    return true;
}

void gameShutDown(Character * player, EnemyList *enemies, ProjectileList *projectiles, char gStatus, int mapCount){

    std::ofstream saveStream;
    saveStream.open("shutDownStatus.txt",std::ios_base::trunc);
    switch(gStatus){

    case GS_CLOSED :
        saveStream << "---Closed---\n" << mapCount << std::endl;
        break;

    case GS_WIN :
        saveStream << "---Win---\n" << mapCount << std::endl;
        break;

    case GS_DEFEAT :
        saveStream << "---Defeat---\n" << mapCount << std::endl;
        break;

    }
    saveStream.close();

   if(gStatus == GS_CLOSED) {
       io::sqlite::db saveDB("save.db");
       saveDB.exec("DELETE FROM Player;");
       saveDB.exec("DELETE FROM Enemies;");
       saveDB.exec("DELETE FROM Projectiles;");

       io::sqlite::stmt stmt(saveDB,"INSERT INTO Player VALUES(?,?,?,?);");
       stmt.bind().real(1,player->x);
       stmt.bind().real(2,player->y);
       stmt.bind().int32(3,(int)(player->curDir));
       stmt.bind().real(4,player->energy);
       stmt.exec();

       for(int i = 0; (unsigned int)i < enemies->npcVector.size(); i++){
           io::sqlite::stmt stmt(saveDB,"INSERT INTO Enemies VALUES(?,?,?,?,?,?,?);");
           stmt.bind().real(1,enemies->npcVector.at(i).x);
           stmt.bind().real(2,enemies->npcVector.at(i).y);
           stmt.bind().real(3,enemies->npcVector.at(i).jumpSpeed);
           stmt.bind().int32(4,(int)(enemies->npcVector.at(i).curDir));
           stmt.bind().real(5,enemies->npcVector.at(i).energy);
           stmt.bind().real(6,enemies->npcVector.at(i).health);
           stmt.bind().int32(7,enemies->npcVector.at(i).logicAction);
           stmt.exec();
       }

       for(int i = 0; (unsigned int)i < projectiles->pVector.size(); i++){
           io::sqlite::stmt stmt(saveDB,"INSERT INTO Projectiles VALUES(?,?,?,?,?,?,?);");
           stmt.bind().real(1,projectiles->pVector.at(i).x);
           stmt.bind().real(2,projectiles->pVector.at(i).y);
           stmt.bind().real(3,projectiles->pVector.at(i).xSpeed);
           stmt.bind().real(4,projectiles->pVector.at(i).ySpeed);
           stmt.bind().int32(5,(int)(projectiles->pVector.at(i).type));
           stmt.bind().real(6,projectiles->pVector.at(i).energy);
           stmt.bind().int32(7,(int)projectiles->pVector.at(i).origin);
           stmt.exec();
       }

       saveDB.io::sqlite::db::~db();
   }
}

char intro(int *mapCount){
    bool MouseOver1 = false;
    bool MouseOver2 = false;
    SoundBuffer mOverSB;
    SoundBuffer mLMBSB;
    mOverSB.loadFromFile("sounds/menuMouseOver.wav");
    mLMBSB.loadFromFile("sounds/menuLMB.wav");
    Sound mOverS(mOverSB);
    Sound mLMBS(mLMBSB);
    mOverS.setVolume(1);
    mLMBS.setVolume(1);
    char result = GS_NONE;
    std::ifstream sdCheck("shutDownStatus.txt");
    std::string sdStatus;
    std::string mapNo;
    std::getline(sdCheck,sdStatus);
    std::getline(sdCheck,mapNo);
    *mapCount = atoi(mapNo.c_str());
    if(sdStatus.compare("---Win---") == 0 || sdStatus.compare("---Defeat---") == 0)
        return GS_NEWGAME;
    if(sdStatus.compare("---Closed---") == 0)
    {
        int ngX = 100;
        int ngY = 100;
        int lgX = 100;
        int lgY = 155;
        RenderWindow introWindow(VideoMode(500, 300), "some sheet");
        Event introEvent;
        Texture introElements;
        introElements.loadFromFile("images/introElements.png");
        Sprite ngSSprite(introElements);
        Sprite ngESprite(introElements);
        Sprite lgSSprite(introElements);
        Sprite lgESprite(introElements);
        ngSSprite.setTextureRect(IntRect(0,0,305,55));
        ngESprite.setTextureRect(IntRect(0,55,305,55));
        lgSSprite.setTextureRect(IntRect(0,110,305,55));
        lgESprite.setTextureRect(IntRect(0,165,305,55));
        ngSSprite.setPosition(Vector2f(ngX,ngY));
        ngESprite.setPosition(Vector2f(ngX,ngY));
        lgSSprite.setPosition(Vector2f(lgX,lgY));
        lgESprite.setPosition(Vector2f(lgX,lgY));
        while(introWindow.isOpen()) {
            int wX = introWindow.getPosition().x;
            int wY = introWindow.getPosition().y;
            introWindow.clear(Color(0,0,0));
            if(Mouse::getPosition().x > wX+ngX && Mouse::getPosition().x < wX+ngX+350 && Mouse::getPosition().y > ngY+wY+25 && Mouse::getPosition().y < ngY+80+wY)
            {
                if(MouseOver1 == false)
                {
                    mOverS.play();
                    MouseOver1 = true;
                }
                introWindow.draw(ngESprite);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mLMBS.play();
                    result = GS_NEWGAME;
                }
            }
            else
            {
                introWindow.draw(ngSSprite);
                MouseOver1 = false;

            }
            if(Mouse::getPosition().x > wX+lgX && Mouse::getPosition().x < wX+lgX+350 && Mouse::getPosition().y > lgY+wY+25 && Mouse::getPosition().y < lgY+80+wY)
            {
                if(MouseOver2 == false)
                {
                    mOverS.play();
                    MouseOver2 = true;
                }
                introWindow.draw(lgESprite);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mLMBS.play();
                    result = GS_LOADED;
                }
            }
            else
            {
                introWindow.draw(lgSSprite);
                MouseOver2 = false;
            }

            while (introWindow.pollEvent(introEvent))
            {
                if (introEvent.type == Event::Closed)
                {
                    Sleep(1000);
                    introWindow.close();
                    exit(0);
                }
            }

            introWindow.display();

            if(result!=GS_NONE){
                introWindow.close();
                return result;
            }

        }
    }
    return GS_NEWGAME;
}

char outro(char gStatus, int * mapCount){
    if(gStatus == GS_WIN && *mapCount < 3)
    {
        (*mapCount)++;
        std::ofstream saveStream;
        saveStream.open("shutDownStatus.txt",std::ios_base::trunc);
        saveStream << "---Closed---\n" << *mapCount << std::endl;
        return GS_NEXT;
    }

    if(gStatus == GS_WIN && *mapCount >= 3)
    {
        outroWin();
        std::ofstream saveStream;
        saveStream.open("shutDownStatus.txt",std::ios_base::trunc);
        saveStream << "---Win---\n" << 0 << std::endl;
    }

    if(gStatus == GS_CLOSED)
    {
        return GS_CLOSED;
    }

    if(gStatus == GS_DEFEAT)
    {
        char oStatus = outroDefeat();
        if(oStatus == GS_NEWGAME){
            std::ofstream saveStream;
            *mapCount = 1;
        saveStream << "---Closed---\n" << *mapCount << std::endl;
        return oStatus;
        }
        if(oStatus == GS_NEXT){
            std::ofstream saveStream;
        saveStream << "---Closed---\n" << *mapCount << std::endl;
        return oStatus;
        }
        if(oStatus == GS_DEFEAT){
            *mapCount = 0;
        return oStatus;
        }
    }

    return GS_DEFEAT;

}

void outroWin(){
        bool MouseOver = false;
        SoundBuffer mOverSB;
        SoundBuffer mLMBSB;
        mOverSB.loadFromFile("sounds/menuMouseOver.wav");
        mLMBSB.loadFromFile("sounds/menuLMB.wav");
        Sound mOverS(mOverSB);
        Sound mLMBS(mLMBSB);
        mOverS.setVolume(1);
        mLMBS.setVolume(1);
        char result = GS_NONE;
        std::ifstream sdCheck("shutDownStatus.txt");
        std::string sdStatus;
        std::getline(sdCheck,sdStatus);

        if(sdStatus.compare("---Win---") == 0)
        {
            int wonX = 100;
            int wonY = 100;
            int qX = 100;
            int qY = 155;
            RenderWindow outroWindow(VideoMode(600, 400), "some sheet");
            Event outroEvent;
            Texture outroElements;
            outroElements.loadFromFile("images/outroElements.png");
            Sprite wonSprite(outroElements);
            Sprite qSSprite(outroElements);
            Sprite qESprite(outroElements);
            wonSprite.setTextureRect(IntRect(0,195,305,55));
            qSSprite.setTextureRect(IntRect(0,250-5,305,45));
            qESprite.setTextureRect(IntRect(0,313-5,305,45));
            qSSprite.setPosition(Vector2f(qX,qY));
            qESprite.setPosition(Vector2f(qX,qY));
            wonSprite.setPosition(Vector2f(wonX,wonY));
            while(outroWindow.isOpen()) {
                int wX = outroWindow.getPosition().x;
                int wY = outroWindow.getPosition().y;
                outroWindow.clear(Color(0,0,0));
                    outroWindow.draw(wonSprite);
                if(Mouse::getPosition().x > wX+qX+75 && Mouse::getPosition().x < wX+qX+250 && Mouse::getPosition().y > wY+qY+25 && Mouse::getPosition().y < wY+80+qY)
                {
                    if(MouseOver == false)
                    {
                        mOverS.play();
                        MouseOver = true;
                    }
                    outroWindow.draw(qESprite);
                    if(Mouse::isButtonPressed(Mouse::Left))
                    {
                        mLMBS.play();
                        result = GS_LOADED;
                    }
                }
                else
                {
                    outroWindow.draw(qSSprite);
                    MouseOver = false;
                }

                while (outroWindow.pollEvent(outroEvent))
                {
                    if (outroEvent.type == Event::Closed)
                    {
                        outroWindow.close();
                        return;
                    }
                }

                outroWindow.display();

                if(result!=GS_NONE){
                    Sleep(1000);
                    outroWindow.close();
                    return;
                }

            }
        }
        sdCheck.close();
        return;

}

char outroDefeat(){
    bool MouseOver1 = false;
    bool MouseOver2 = false;
    SoundBuffer mOverSB;
    SoundBuffer mLMBSB;
    mOverSB.loadFromFile("sounds/menuMouseOver.wav");
    mLMBSB.loadFromFile("sounds/menuLMB.wav");
    Sound mOverS(mOverSB);
    Sound mLMBS(mLMBSB);
    mOverS.setVolume(1);
    mLMBS.setVolume(1);
    char result = GS_NONE;
    std::ifstream sdCheck("shutDownStatus.txt");
    std::string sdStatus;
    std::getline(sdCheck,sdStatus);
    if(sdStatus.compare("---Defeat---") == 0)
    {
        int rsX = 100;
        int rsY = 100;
        int rtX = 100;
        int rtY = 155;
        RenderWindow outroWindow(VideoMode(500, 300), "some sheet");
        Event outroEvent;
        Texture outroElements;
        outroElements.loadFromFile("images/outroElements.png");
        Sprite rsSSprite(outroElements);
        Sprite rsESprite(outroElements);
        Sprite rtSSprite(outroElements);
        Sprite rtESprite(outroElements);
        rsSSprite.setTextureRect(IntRect(0,0,280,45));
        rsESprite.setTextureRect(IntRect(0,55,280,45));
        rtSSprite.setTextureRect(IntRect(0,103,280,45));
        rtESprite.setTextureRect(IntRect(0,151,280,45));
        rsSSprite.setPosition(Vector2f(rsX,rsY));
        rsESprite.setPosition(Vector2f(rsX,rsY));
        rtSSprite.setPosition(Vector2f(rtX,rtY));
        rtESprite.setPosition(Vector2f(rtX,rtY));
        while(outroWindow.isOpen()) {
            int wX = outroWindow.getPosition().x;
            int wY = outroWindow.getPosition().y;
            outroWindow.clear(Color(0,0,0));
            if(Mouse::getPosition().x > wX+rsX && Mouse::getPosition().x < wX+rsX+350 && Mouse::getPosition().y > rsY+wY+25 && Mouse::getPosition().y < rsY+80+wY)
            {
                if(MouseOver1 == false)
                {
                    mOverS.play();
                    MouseOver1 = true;
                }
                outroWindow.draw(rsESprite);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mLMBS.play();
                    result = GS_NEWGAME;
                }
            }
            else
            {
                outroWindow.draw(rsSSprite);
                MouseOver1 = false;

            }
            if(Mouse::getPosition().x > wX+rtX && Mouse::getPosition().x < wX+rtX+350 && Mouse::getPosition().y > rtY+wY+25 && Mouse::getPosition().y < rtY+80+wY)
            {
                if(MouseOver2 == false)
                {
                    mOverS.play();
                    MouseOver2 = true;
                }
                outroWindow.draw(rtESprite);
                if(Mouse::isButtonPressed(Mouse::Left))
                {
                    mLMBS.play();
                    result = GS_NEXT;
                }
            }
            else
            {
                outroWindow.draw(rtSSprite);
                MouseOver2 = false;
            }

            while (outroWindow.pollEvent(outroEvent))
            {
                if (outroEvent.type == Event::Closed)
                {
                    outroWindow.close();
                    exit(0);
                }
            }

            if(Keyboard::isKeyPressed(Keyboard::T))
            {
                outroWindow.draw(rtESprite);
                mLMBS.play();
                result = GS_NEXT;
            }

            if(Keyboard::isKeyPressed(Keyboard::R))
            {
                outroWindow.draw(rsESprite);
                mLMBS.play();

                result = GS_NEWGAME;
            }

            outroWindow.display();

            if(result!=GS_NONE){
                Sleep(1000);
                outroWindow.close();
                return result;
            }

        }
    }
    return GS_NEWGAME;
}

