#ifndef EFFECTLIST_H
#define EFFECTLIST_H
#include "effect.h"
#include <string.h>

using namespace sf;

class EffectList
{
    float * time;
    std::vector < Effect > eList;
    RenderWindow * window;
    Image eImage;
    Texture eTexture;
public:
    EffectList(RenderWindow *window, float * time);
    void add(float x, float y, char type, char tartype, char dir, void * target);
    void update();
};

#endif // EFFECTLIST_H
