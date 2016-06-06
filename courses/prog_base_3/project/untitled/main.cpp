#include <SFML/Graphics.hpp>
#include <windows.h>
#include "player.h"
#include "map.h"
struct heropos {
int x;
int y;
};
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(1280, 1024), "some sheet");

    Player player("seiryuu.png",100,400,96,96);
    player.changespeed(1);

    Clock clock;

    Map map("test","tiles.png",window);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/320;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A)) {
            player.changedir(GO_LEFT);
            }
        if(Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D)) {
            player.changedir(GO_RIGHT);
           }
        if(Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::W)) {
            player.changedir(GO_UP);
            }
        if(Keyboard::isKeyPressed(Keyboard::Down)||Keyboard::isKeyPressed(Keyboard::S)) {
            player.changedir(GO_DOWN);
        }

        player.update(time);

        player.changedir(IDLE);

        window.clear();
        map.update();
        window.draw(player.sprite);
        window.display();


}

    return 0;

    }

