#include "axx.hpp"

class Cone : public Shape
{
public:
    float radius;
    float height;
    float angle;
    Point center;
    Point axis;
    Point origin;
    Cone();
    Cone(float radius, float height, float angle, Point center, Point axis, Material mat);
    void  applyTransform(Matriz transform);
    void  setCameraCoordinates(Matriz worldToCamera);
    void  setWorldCoordinates(Matriz cameraToWorld);
    Point rayIntersect(Point rayOrigin, Point rayDirection);
    Point planeIntersectBase(Point rayOrigin, Point rayDirection);
    Point normal(Point point);
    void  scaling(Point scale);
    void  rotate(Matriz rotate);
    void  translating(Point translate);
    bool  validate(Point p, Point ray);
    Point base_intesection(Point rayOrigin, Point rayDirection);
    //Point* Bounds();
};