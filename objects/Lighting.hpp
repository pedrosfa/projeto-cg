#pragma once
#include "axx.hpp"

class Lighting {
public:
    float r;
    float g;
    float b;
    virtual float difuseFactor(Point point, Point normal) = 0;
    virtual float specularFactor(Point point, Point normal) = 0;
    virtual Point difuseIntensity(Point point, Point normal, Material mat) = 0;
    virtual Point specularIntensity(Point point, Point normal, Material mat) = 0;
    virtual void setCameraCoordinates(Matriz worldToCamera) = 0;
    virtual void setWorldCoordinates(Matriz cameraToWorld) = 0;
    Lighting();
};

class AmbientLighting
{
public:
    float r;
    float g;
    float b;
    AmbientLighting();
    Point ambientIntensity(Point point, Material mat);
    AmbientLighting(float r, float g, float b);
};

class SpotLighting : public Lighting
{
public:
    Point position;
    Point direction;
    float angle;
    SpotLighting(float r, float g, float b, Point position, Point direction, float angle);
    float difuseFactor(Point point, Point normal);
    float specularFactor(Point point, Point normal);
    Point difuseIntensity(Point point, Point normal, Material mat);
    Point specularIntensity(Point point, Point normal, Material mat);
    void setCameraCoordinates(Matriz worldToCamera);
    void setWorldCoordinates(Matriz cameraToWorld);
};

class FarLighting : public Lighting
{
public:
    Point direction;
    FarLighting(float r, float g, float b, Point direction);
    float difuseFactor(Point point, Point normal);
    float specularFactor(Point point, Point normal);
    Point difuseIntensity(Point point, Point normal, Material mat);
    Point specularIntensity(Point point, Point normal, Material mat);
    void setCameraCoordinates(Matriz worldToCamera);
    void setWorldCoordinates(Matriz cameraToWorld);
};

class PointLighting : public Lighting
{
public:
    Point position;
    PointLighting(float r, float g, float b, Point position);
    float difuseFactor(Point point, Point normal);
    float specularFactor(Point point, Point normal);
    Point difuseIntensity(Point point, Point normal, Material mat);
    Point specularIntensity(Point point, Point normal, Material mat);
    void setCameraCoordinates(Matriz worldToCamera);
    void setWorldCoordinates(Matriz cameraToWorld);
};