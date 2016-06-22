#ifndef EFFECT_H
#define EFFECT_H
#include <SFML/Graphics.hpp>
#include <typeinfo>
#define BOOM_WIDTH 50
#define BOOM_HEIGHT 20

enum effectDiretions {EFFECT_NODIR = 0, ELEFT = 2, EDOWN = 4, ERIGHT = 8, EUP = 16};
enum effectTypes {EFFECT_NOTYPE = 0, ENERGYBOOM = 2, ASHIELD_EFFECT = 4, EPROJ = 8, CYCLED = 16};
enum targetType {NOTARGET = 0, XYVECTOR = 2, CHARACTER = 4};

class Effect
{
    float * x = new float;
    float * y = new float;
    float effectTimer = 0;
    float * time;
    float animationSpeed;
    int type;
    int tarType;
    int selfPos;
    int effectTextureY;
    int effectWidth;
    int effectHeight;
    char dir;
    sf::Texture * eTexture;
    sf::Sprite eSprite;
    sf::RenderWindow *window;
    bool xyPointed;
    void boomUpdate();
    void *target;
public:
    Effect(float x, float y, float * time, sf::RenderWindow * window, char type, char tarType, sf::Texture * eTexture, char dir, void * target);
    bool toDelete;
    void update();
};

#endif // EFFECT_H
