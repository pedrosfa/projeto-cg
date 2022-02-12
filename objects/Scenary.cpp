#include "Scenary.hpp"
#include <numeric>

Scenary::Scenary() {
    canvas_opengl = new float[HEIGHT * WIDTH * 3];
};

void Scenary::addShape(Shape* shape)
{
    this->shapes.push_back(shape);
};

void Scenary::addLight(Lighting* light)
{
    this->lights.push_back(light);
};

void Scenary::setCamera(Camera camera)
{
    this->camera = camera;
};

void Scenary::setAmbientLight(AmbientLighting ambientLight)
{
    this->ambientLight = ambientLight;
};

//void Scenary::setWorldCoordinates()
//{
//    for (int i = 0; i < this->shapes.size(); i++) {
//        this->shapes[i]->setWorldCoordinates(this->camera.cameraToWorld());
//    }
//    for (int i = 0; i < this->lights.size(); i++) {
//        this->lights[i].setWorldCoordinates(this->camera.cameraToWorld());
//    }
//};

void Scenary::setCameraCoordinates()
{
    for (int i = 0; i < this->shapes.size(); i++) {
        this->shapes[i]->setCameraCoordinates(this->camera.worldToCamera());
    }

    //for (int i = 0; i < this->lights.size(); i++) {
    //    this->lights[i]->setCameraCoordinates(this->camera.worldToCamera());
    //}
};

void Scenary::rayCasting()
{
    this->setCameraCoordinates();
    Point intersect;

    double x, y, z;

    z = camera.d; // distancia

    double deslocamento = camera.plano_tamanho / HEIGHT; //só faço uma vez visto que os lados têm o mesmo tamanho

    int idx = 0;

    Point rayOrigin = Point(0, 0, 0);
    for (int j = 0; j < HEIGHT; j++)
    {
        y = -camera.plano_tamanho / 2 + deslocamento + j * deslocamento;
        for (int k = 0; k < WIDTH; k++)
        {
            x = -camera.plano_tamanho / 2 + deslocamento + k * deslocamento;

            Point nearest_point = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);

            Point rayDirection = Point(x, y, z);

            Shape* obj;

            for (int i = 0; i < this->shapes.size(); i++)
            {
                intersect = this->shapes[i]->rayIntersect(rayOrigin, rayDirection);
                if (intersect.norm() < nearest_point.norm()) {
                    nearest_point = intersect;
                    obj = shapes[i];
                }
            }

            if (nearest_point[2] < MAXFLOAT) {
                Point intensity = this->ambientLight.ambientIntensity(nearest_point, obj->mat);

                for (int l = 0; l < this->lights.size(); l++) {
                    intensity += this->lights[l]->difuseIntensity(nearest_point, obj->normal(nearest_point), obj->mat);
                    intensity += this->lights[l]->specularIntensity(nearest_point, obj->normal(nearest_point), obj->mat);
                }

                this->frame[idx * 3]     = intensity[0];
                this->frame[idx * 3 + 1] = intensity[1];
                this->frame[idx * 3 + 2] = intensity[2];
            }
            else
            {
                frame[idx * 3]   = ambientLight.r;
                frame[idx * 3+1] = ambientLight.g;
                frame[idx * 3+2] = ambientLight.b;
            }

            idx++;
        }
    }
};