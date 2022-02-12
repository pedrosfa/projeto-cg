#include "Cube.hpp"
#include "../transform/rotation.hpp"
Cube::Cube() {};
Cube::Cube(float side, Point  center, Material mat)
{
    this->side = side;
    this->center = center;
    this->mat = mat;

    sidex = side;
    sidey = side;
    sidez = side;

    float sx = this->sidex / 2;
    float sy = this->sidey / 2;
    float sz = this->sidez / 2;
    //int t = 100;
    this->vertices[0] = Point(this->center[0] - sx, this->center[1] + sy, this->center[2] + sz);
    this->vertices[1] = Point(this->center[0] - sx, this->center[1] + sy, this->center[2] - sz);
    this->vertices[2] = Point(this->center[0] + sx, this->center[1] + sy, this->center[2] - sz);
    this->vertices[3] = Point(this->center[0] + sx, this->center[1] + sy, this->center[2] + sz);
    this->vertices[4] = Point(this->center[0] - sx, this->center[1] - sy, this->center[2] + sz);
    this->vertices[5] = Point(this->center[0] - sx, this->center[1] - sy, this->center[2] - sz);
    this->vertices[6] = Point(this->center[0] + sx, this->center[1] - sy, this->center[2] - sz);
    this->vertices[7] = Point(this->center[0] + sx, this->center[1] - sy, this->center[2] + sz);


    this->faces[0] = Face(this->vertices[2], this->vertices[3], this->vertices[7]);
    this->faces[1] = Face(this->vertices[2], this->vertices[7], this->vertices[6]);
    this->faces[2] = Face(this->vertices[2], this->vertices[1], this->vertices[0]);
    this->faces[3] = Face(this->vertices[2], this->vertices[0], this->vertices[3]);
    this->faces[4] = Face(this->vertices[3], this->vertices[0], this->vertices[7]);
    this->faces[5] = Face(this->vertices[0], this->vertices[4], this->vertices[7]);
    this->faces[6] = Face(this->vertices[1], this->vertices[4], this->vertices[0]);
    this->faces[7] = Face(this->vertices[1], this->vertices[5], this->vertices[4]);
    this->faces[8] = Face(this->vertices[7], this->vertices[4], this->vertices[6]);
    this->faces[9] = Face(this->vertices[4], this->vertices[5], this->vertices[6]);
    this->faces[10] = Face(this->vertices[2], this->vertices[6], this->vertices[1]);
    this->faces[11] = Face(this->vertices[6], this->vertices[5], this->vertices[1]);

    this->normal_intersect = Point(0, 0, 0);
}

void Cube::updateFaces1()
{
    float sx = this->sidex / 2;
    float sy = this->sidey / 2;
    float sz = this->sidez / 2;
    //int t = 100;
    this->vertices[0] = Point(this->center[0] - sx, this->center[1] + sy, this->center[2] + sz);
    this->vertices[1] = Point(this->center[0] - sx, this->center[1] + sy, this->center[2] - sz);
    this->vertices[2] = Point(this->center[0] + sx, this->center[1] + sy, this->center[2] - sz);
    this->vertices[3] = Point(this->center[0] + sx, this->center[1] + sy, this->center[2] + sz);
    this->vertices[4] = Point(this->center[0] - sx, this->center[1] - sy, this->center[2] + sz);
    this->vertices[5] = Point(this->center[0] - sx, this->center[1] - sy, this->center[2] - sz);
    this->vertices[6] = Point(this->center[0] + sx, this->center[1] - sy, this->center[2] - sz);
    this->vertices[7] = Point(this->center[0] + sx, this->center[1] - sy, this->center[2] + sz);


    this->faces[0] = Face(this->vertices[2], this->vertices[3],  this->vertices[7]);
    this->faces[1] = Face(this->vertices[2], this->vertices[7],  this->vertices[6]);
    this->faces[2] = Face(this->vertices[2], this->vertices[1],  this->vertices[0]);
    this->faces[3] = Face(this->vertices[2], this->vertices[0],  this->vertices[3]);
    this->faces[4] = Face(this->vertices[3], this->vertices[0],  this->vertices[7]);
    this->faces[5] = Face(this->vertices[0], this->vertices[4],  this->vertices[7]);
    this->faces[6] = Face(this->vertices[1], this->vertices[4],  this->vertices[0]);
    this->faces[7] = Face(this->vertices[1], this->vertices[5],  this->vertices[4]);
    this->faces[8] = Face(this->vertices[7], this->vertices[4],  this->vertices[6]);
    this->faces[9] = Face(this->vertices[4], this->vertices[5],  this->vertices[6]);
    this->faces[10] = Face(this->vertices[2], this->vertices[6], this->vertices[1]);
    this->faces[11] = Face(this->vertices[6], this->vertices[5], this->vertices[1]);

    //this->normal_intersect = Point(0, 0, 0);
}

void Cube::updateFaces2() {
    this->faces[0] = Face(this->vertices[2], this->vertices[3], this->vertices[7]);
    this->faces[1] = Face(this->vertices[2], this->vertices[7], this->vertices[6]);
    this->faces[2] = Face(this->vertices[2], this->vertices[1], this->vertices[0]);
    this->faces[3] = Face(this->vertices[2], this->vertices[0], this->vertices[3]);
    this->faces[4] = Face(this->vertices[3], this->vertices[0], this->vertices[7]);
    this->faces[5] = Face(this->vertices[0], this->vertices[4], this->vertices[7]);
    this->faces[6] = Face(this->vertices[1], this->vertices[4], this->vertices[0]);
    this->faces[7] = Face(this->vertices[1], this->vertices[5], this->vertices[4]);
    this->faces[8] = Face(this->vertices[7], this->vertices[4], this->vertices[6]);
    this->faces[9] = Face(this->vertices[4], this->vertices[5], this->vertices[6]);
    this->faces[10] = Face(this->vertices[2], this->vertices[6], this->vertices[1]);
    this->faces[11] = Face(this->vertices[6], this->vertices[5], this->vertices[1]);
}



void Cube::Scalling(Point p)
{
    sidex *= p[0];
    sidey *= p[1];
    sidez *= p[2];

    updateFaces1();
}

//Utilizar Vertex
void Cube::Rotate(float angle, Point axis)
{
    Matriz Rx = rotateX(angle);
    Matriz Ry = rotateY(angle);
    Matriz Rz = rotateZ(angle);

    Matriz transform;

    for (int i = 0; i < 3; i++) {
        if (i == 0 && axis[0] > 0) {
            transform = Rx;
        }
        else if (i == 1 && axis[1] > 0) {
            transform = Ry;
        }
        else if (i == 2 && axis[2] > 0) {
            transform = Rz;
        }
        else {
            continue;
        }

        Vertex aux_center = Vertex(center[0], center[1], center[2], 1);

        aux_center = transform * aux_center;
        center[0] = aux_center[0];
        center[1] = aux_center[1];
        center[2] = aux_center[2];

        for (int i = 0; i < 8; i++)
        {
            Vertex v = Vertex(this->vertices[i][0], this->vertices[i][1], this->vertices[i][2], 1);
            Vertex p = transform * v;
            this->vertices[i] = Point(p[0], p[1], p[2]);
        }

        updateFaces2();
    }
}

void Cube::Translating(Point p) {
    //for (int i = 0; i < 8; i++) {
    //    this->vertices[i] += p;
    //}
    center = center + p;
    updateFaces1();
}
void Cube::Mirror(Point axis)
{
}
//Utilizar Vertex

void Cube::setCameraCoordinates(Matriz worldToCamera)
{
    this->center = VertexToPoint(worldToCamera * PointToVertex(this->center));
    for (int i = 0; i < 8; i++)
    {
        vertices[i] = VertexToPoint(worldToCamera * PointToVertex(this->vertices[i]));
    }

    updateFaces2();
}

//Utilizar Vertex
void Cube::setWorldCoordinates(Matriz cameraToWorld)
{
    //this->center = cameraToWorld * this->center;
    //for (int i = 0; i < 8; i++)
    //{
    //    vertices[i] = cameraToWorld * vertices[i];
    //}
    //updateFaces();
}

void Cube::setNormal(Point intersect)
{
    this->normal_intersect = intersect;
}

Point Cube::rayIntersect(Point rayOrigin, Point rayDirection) {
    double distance = MAXFLOAT;
    Point closest_intersection = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    for (int i = 0; i < 12; i++) {
        Face face = this->faces[i];
        Point intersection = face.rayIntersection(rayOrigin, rayDirection);
        double intersectionDistance = sqrt(pow(intersection[0] - rayOrigin[0], 2) + pow(intersection[1] - rayOrigin[1], 2) + pow(intersection[2] - rayOrigin[2], 2));
        if (intersection[2] < MAXFLOAT && intersectionDistance < distance)
        {
            distance = intersectionDistance;
            closest_intersection = intersection;
            setNormal(face.getNormal());
        }
    }
    return closest_intersection;
};

Point Cube::normal(Point point)
{
    return this->normal_intersect;
}

//Point* Cube::Bounds()
//{
//    Point minBounds = this->vertices[0];
//    Point maxBounds = this->vertices[0];
//    for (int i = 0; i < 8; i++)
//    {
//        if (vertices[i][0] > maxBounds[0])
//        {
//            maxBounds[0] = vertices[i][0];
//        }
//        if (vertices[i][1] > maxBounds[1])
//        {
//            maxBounds[1] = vertices[i][1];
//        }
//        if (vertices[i][2] > maxBounds[2])
//        {
//            maxBounds[2] = vertices[i][2];
//        }
//        if (vertices[i][0] < minBounds[0])
//        {
//            minBounds[0] = vertices[i][0];
//        }
//        if (vertices[i][1] < minBounds[1])
//        {
//            minBounds[1] = vertices[i][1];
//        }
//        if (vertices[i][2] < minBounds[2])
//        {
//            minBounds[2] = vertices[i][2];
//        }
//    }
//
//    return new Point(minBounds, maxBounds);
//}