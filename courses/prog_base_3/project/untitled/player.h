#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "map.h"

using namespace sf;

enum directories {IDLE=-1,GO_UP,GO_LEFT,GO_DOWN,GO_RIGHT};

class Player
{
    float x, y, w, h, dx, dy,speed = 0;
    String imgname;
    Image image;
    Texture texture;
    int dir=0;
    public:
    float currentFrame = 0;
    Sprite sprite;
    Player(String imgname,int X, int Y, int W, int H){
        this->imgname = imgname;
        w = W, h = H;
        image.loadFromFile("images/"+imgname);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0,0,w,h));
        x = X, y =Y;

    }

    void changespeed(int speed){
        this->speed = speed;
    }

    void changedir(int dir){
        this->dir = dir;
    }

    void update(float time){

        if(dir>=0&&dir<4){

            currentFrame+=0.005*time;

            switch(dir){



                case GO_UP:
                    sprite.move(0,-0.1*time);
                    sprite.setTextureRect(IntRect(w*((int)currentFrame%3),h*3,w,h));
                    dx = 0;
                    dy = -speed;
                    break;
                case GO_LEFT:
                    sprite.move(-0.1*time,0);
                    sprite.setTextureRect(IntRect(w*((int)currentFrame),h,w,h));
                    dx = -speed;
                    dy = 0;
                    break;
                case GO_DOWN:
                    sprite.move(0,0.1*time);
                    sprite.setTextureRect(IntRect(w*((int)currentFrame),0,w,h));
                    dx = 0;
                    dy = speed;
                    break;
                case GO_RIGHT:
                    sprite.move(0.1*time,0);
                    sprite.setTextureRect(IntRect(w*((int)currentFrame),h*2,w,h));
                    dx = speed;
                    dy =0;
                    break;
                default:
                    changespeed(0);
                    break;
                    }
                        }

        else
            changespeed(0);


        x+=dx*time;
        y+=dy*time;

        speed=0;

        if(currentFrame>=3)
            currentFrame-=3;
    }
};

#endif // PLAYER_H
