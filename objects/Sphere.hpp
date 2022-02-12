#pragma once
#include "axx.hpp"

class Sphere : public Shape {
public:
    float radius;
    Point center;
    Sphere();
    Sphere(float radius, Point center, Material mat);
    void  applyTransform(Matriz transform);
    void  setCameraCoordinates(Matriz worldToCamera);
    void  setWorldCoordinates(Matriz cameraToWorld);
    Point rayIntersect(Point rayOrigin, Point rayDirection);
    Point normal(Point point);
    void  scaling(Point scale);
    void  rotate(Matriz rotate);
    void  translating(Point translate);
    //Point* Bounds();
};