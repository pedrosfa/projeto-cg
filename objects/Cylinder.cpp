#include "Cylinder.hpp"

Cylinder::Cylinder() {};
Cylinder::Cylinder(float radius, float height, Point center_base, Point axis, Material mat)
{
    this->radius = radius;
    this->height = height;
    this->center_base = center_base;
    this->center_top = center_base + axis * height;
    this->axis = axis;
    this->mat = mat;
};

/*Adicionar VERTEX*/
void Cylinder::applyTransform(Matriz transform)
{
    Vertex cb = Vertex(this->center_base[0], this->center_base[1], this->center_base[2], 1);
    cb = transform * cb;
    this->center_base = Point(cb[0], cb[1], cb[2]);

 /*   Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = transform * axisv;*/

    //this->axis = Point(axisv[0], axisv[1], axisv[2]);
    this->center_top = this->center_base + this->axis * this->height;
};
/*Adicionar VERTEX*/
void Cylinder::setCameraCoordinates(Matriz worldToCamera)
{
    Vertex cb = Vertex(this->center_base[0], this->center_base[1], this->center_base[2], 1);
    cb = worldToCamera * cb;
    this->center_base = Point(cb[0], cb[1], cb[2]);

    //Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    //axisv = worldToCamera * axisv;

    //this->axis = Point(axisv[0], axisv[1], axisv[2]);
    this->center_top = VertexToPoint(worldToCamera * PointToVertex(this->center_top));
};
/*Adicionar VERTEX*/
void Cylinder::setWorldCoordinates(Matriz cameraToWorld)
{
    Vertex cb = Vertex(this->center_base[0], this->center_base[1], this->center_base[2], 1);
    cb = cameraToWorld * cb;
    this->center_base = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = cameraToWorld * axisv;

    this->axis = Point(axisv[0], axisv[1], axisv[2]);
    this->center_top = this->center_base + this->axis * this->height;
};

Point Cylinder::planeIntersectBase(Point rayOrigin, Point rayDirection)
{
    Point v = this->center_base - rayOrigin;
    float p = this->axis.dot(v);
    float t = this->axis.dot(rayDirection);

    if (t == 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        float s = p / t;
        Point intersection = rayOrigin + rayDirection * s;
        return intersection;
    }
};

Point Cylinder::planeIntersectTop(Point rayOrigin, Point rayDirection)
{
    Point v = this->center_top - rayOrigin;
    float p = this->axis.dot(v);
    float t = this->axis.dot(rayDirection);

    if (t == 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        float s = p / t;
        Point intersection = rayOrigin + rayDirection * s;

        return intersection;
    }
};

bool Cylinder::validate(Point p)
{
    Point pb = p - this->center_base;
    float pi = pb.dot(this->axis);

    return (0 <= pi && pi <= this->height);
}

//Point* Cylinder::Bounds()
//{
//    Point max_bounds = this->center_base + this->axis * this->height;
//    Point min_bounds = this->center_base + this->axis * this->height;
//
//    Point p = Point(1, 0, 0);
//
//    if (this->axis[1] != 1)
//    {
//        p = this->axis.cross(Point(0, 1, 0));
//    }
//    Point p2 = p.cross(this->axis);
//
//    for (int i = 0; i < 4; i++)
//    {
//        Point pb = this->center_base + p * this->radius + p2 * this->radius;
//
//        if (pb[0] > max_bounds[0])
//        {
//            max_bounds[0] = pb[0];
//        }
//        if (pb[1] > max_bounds[1])
//        {
//            max_bounds[1] = pb[1];
//        }
//        if (pb[2] > max_bounds[2])
//        {
//            max_bounds[2] = pb[2];
//        }
//        if (pb[0] < min_bounds[0])
//        {
//            min_bounds[0] = pb[0];
//        }
//        if (pb[1] < min_bounds[1])
//        {
//            min_bounds[1] = pb[1];
//        }
//        if (pb[2] < min_bounds[2])
//        {
//            min_bounds[2] = pb[2];
//        }
//
//        Point pt = this->center_top + p * this->radius - p2 * this->radius;
//
//        if (pt[0] > max_bounds[0])
//        {
//            max_bounds[0] = pt[0];
//        }
//        if (pt[1] > max_bounds[1])
//        {
//            max_bounds[1] = pt[1];
//        }
//        if (pt[2] > max_bounds[2])
//        {
//            max_bounds[2] = pt[2];
//        }
//
//        p = p2;
//        p2 = p.cross(this->axis);
//    }
//
//    return new Point(min_bounds, max_bounds);
//}

Point Cylinder::rayIntersect(Point rayOrigin, Point rayDirection)
{
    Point vetorNorm = rayDirection.normalized();

    Point C0P0 = rayOrigin - this->center_base;

    Point v = C0P0 - (this->axis * (C0P0.dot(this->axis)));

    Point w = vetorNorm - (this->axis * vetorNorm.dot(this->axis));

    float a = w.dot(w);

    float b = v.dot(w);

    float c = v.dot(v) - this->radius * this->radius;

    float delta = b * b - a * c;

    if (delta < 0) {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }

    float t1, t2;
    float closest_distance = MAXFLOAT;

    Point int_base = planeIntersectBase(rayOrigin, rayDirection);
    if (int_base[0] < MAXFLOAT) {
        float d = sqrt(pow(int_base[0] - this->center_base[0], 2) + pow(int_base[1] - this->center_base[1], 2) + pow(int_base[2] - this->center_base[2], 2));
        if (d > this->radius)
        {
            int_base = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
        }
        else
        {
            closest_distance = sqrt(pow(int_base[0] - rayOrigin[0], 2) + pow(int_base[1] - rayOrigin[1], 2) + pow(int_base[2] - rayOrigin[2], 2));
        }
    }

    Point int_top = planeIntersectTop(rayOrigin, rayDirection);
    float d = sqrt(pow(int_top[0] - this->center_top[0], 2) + pow(int_top[1] - this->center_top[1], 2) + pow(int_top[2] - this->center_top[2], 2));
    if (int_top[0] < MAXFLOAT && d <= this->radius) {
        float dist = sqrt(pow(rayOrigin[0] - int_top[0], 2) + pow(rayOrigin[1] - int_top[1], 2) + pow(rayOrigin[2] - int_top[2], 2));
        if (!(int_base[0] < MAXFLOAT) || dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_top;
        }
    }

    t1 = (- b + sqrt(delta)) / a;
    t2 = (- b - sqrt(delta)) / a;

    Point int_cyl1 = rayOrigin + vetorNorm.normalized() * t1;
    Point int_cyl2 = rayOrigin + vetorNorm.normalized() * t2;

    if (validate(int_cyl1))
    {
        double dist = sqrt(pow(rayOrigin[0] - int_cyl1[0], 2) + pow(rayOrigin[1] - int_cyl1[1], 2) + pow(rayOrigin[2] - int_cyl1[2], 2));
        if (dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_cyl1;
        }
    }

    if (validate(int_cyl2))
    {
        double dist = sqrt(pow(rayOrigin[0] - int_cyl2[0], 2) + pow(rayOrigin[1] - int_cyl2[1], 2) + pow(rayOrigin[2] - int_cyl2[2], 2));
        if (dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_cyl2;
        }
    }
    return int_base;
}


void Cylinder::scaling(Point scale) // 0, 1, 1
{
    this->radius *= scale[0];
    this->height *= scale[1];
    this->center_top = this->center_base + this->axis * this->height;
};

void Cylinder::rotate(Matriz rotate)
{
    this->center_base = VertexToPoint(rotate * PointToVertex(this->center_base));
    this->axis   = VertexToPoint(rotate * PointToVertex(this->axis));
    this->center_top = VertexToPoint(rotate * PointToVertex(this->center_top));
}
void Cylinder::translating(Point translate)
{
    this->center_base += translate;
    //this->axis        = 
    this->center_top  += translate;
}

Point Cylinder::normal(Point point)
{
    Point pointToCenter = point - this->center_base;
    float val = pointToCenter.dot(this->axis);
    Point a = this->axis * val;

    Point v = this->center_base + a;
    Point normal = point - v;
    normal = normal / this->radius;

    return normal;
}