#include <SFML/Graphics.hpp>
#include "view.h"

using namespace sf;

    Camera::Camera(float x,float y,float w,float h){
        view.reset(FloatRect(x,y,w,h));
    }

    void Camera::setPos(float inX, float inY){
        x = inX;
        y = inY;
        view.setCenter(Vector2f(x,y));
    }

    void Camera::setSize(double inW, double inH) {
        w = inW;
        h = inH;
    view.setSize(w,h);
    }

    Vector2f Camera::getPos(){
        return view.getCenter();
    }

    View Camera::getView(){
        return view;
    }

