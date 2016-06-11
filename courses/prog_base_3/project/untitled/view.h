#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Camera {
    float x;
    float y;
    float w;
    float h;
    View view;
public:
    void setSize(double inW, double inH);
    void setPos(float inX, float inY);
    Camera(float x,float y,float w,float h);
    Vector2f getPos();
    View getView();
 };

#endif // VIEW_H
