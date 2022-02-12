#pragma once
#include "axx.hpp"

class Camera {
public:
    Point eye;
    Point lookAt;
    Point viewUp;
    Point k;
    Point i;
    Point j;
    double d;
    double plano_tamanho;
    Camera();
    Camera(Point eye, Point lookAt, Point viewUp, int d, int plano_tamanho);
    Matriz worldToCamera();
    Matriz cameraToWorld();
    void update();
    void moveX(float x);
    void moveY(float y);
    void moveZ(float z);
    void moveTo(Point eye);
};