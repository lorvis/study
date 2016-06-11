#include <SFML/Graphics.hpp>
#include <windows.h>
#include "player.h"
#include "map.h"
#include "view.h"

using namespace sf;
int main()
{
    int startX = 100;
    int startY = 200;
    float time = 0;
    RenderWindow window(VideoMode(1280, 1024), "some sheet");
    window.setVerticalSyncEnabled(true);
    Map map("test","tiles.png",&window);
    Character player(startX*2,startY*2,&map,&window,&time);
    sf::Font font;
    font.loadFromFile("text/arial.ttf");
    player.debugInfo.setFont(font);
    Camera cam(0,0,300,300);
    Clock clock;



    while (window.isOpen())
    {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/160;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color(86,50,68));
        map.update();
        player.update();
        cam.setPos(player.getX(),player.getY());
        player.debugInfo.setPosition(cam.getPos().x-200,cam.getPos().y-200);
        window.setView(cam.getView());
        window.draw(player.debugInfo);
        window.display();
    }

    return 0;

    };

