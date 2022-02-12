#include "Cone.hpp"

Cone::Cone() {};
Cone::Cone(float radius, float height, float angle, Point center, Point axis, Material mat)
{
    this->radius = radius;
    this->height = height;
    this->angle = angle;
    this->center = center;
    this->axis = axis;
    this->origin = center + axis * height;
    this->mat = mat;
};

//Utilizar Vertex
void Cone::applyTransform(Matriz transform)
{
    Vertex cb = Vertex(this->center[0], this->center[1], this->center[2], 1);
    cb = transform * cb;
    this->center = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = transform * axisv;

    this->origin = this->center + this->axis * this->height;
};
//Utilizar Vertex
void Cone::setCameraCoordinates(Matriz worldToCamera)
{
    Vertex cb = Vertex(this->center[0], this->center[1], this->center[2], 1);
    cb = worldToCamera * cb;
    this->center = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = worldToCamera * axisv;

    this->origin = this->center + this->axis * this->height;
};
//Utilizar Vertex
void Cone::setWorldCoordinates(Matriz cameraToWorld)
{
    Vertex cb = Vertex(this->center[0], this->center[1], this->center[2], 1);
    cb = cameraToWorld * cb;
    this->center = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = cameraToWorld * axisv;

    this->origin = this->center + this->axis * this->height;
};

Point Cone::planeIntersectBase(Point rayOrigin, Point rayDirection)
{
    Point v = this->center - rayOrigin;
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
        intersection[3] = 1;
        return intersection;
    }
};

bool Cone::validate(Point p, Point ray)
{
    Point aux = p - ray;
    float s = aux.dot(this->axis);

    return ((s >= 0) && (s <= this->height));
}

Point Cone::base_intesection(Point rayOrigin, Point rayDirection)
{
    Point v = this->center - rayOrigin;
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

        float d = sqrt(pow(intersection[0] - this->center[0], 2) + pow(intersection[1] - this->center[1], 2) + pow(intersection[2] - this->center[2], 2));

        if (d <= this->radius)
        {
            return intersection;
        }
        else
        {
            return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
        }
    }


}

void Cone::scaling(Point scale) // 0, 1, 1
{
    this->radius    *= scale[0];
    this->height    *= scale[1];
    this->origin = this->center + this->axis * this->height;
};

void Cone::rotate(Matriz rotate)
{
    this->center = VertexToPoint(rotate * PointToVertex(this->center));
    this->axis   = VertexToPoint(rotate * PointToVertex(this->axis));
    this->origin = VertexToPoint(rotate * PointToVertex(this->origin));
}

void Cone::translating(Point translate)
{
    this->center += translate;
    //this->axis   += translate;
    this->origin += translate;
}

//Point* Cone::Bounds()
//{
//    Point max_bounds = this->center + this->height * this->axis;
//    Point min_bounds = this->center - this->height * this->axis;
//
//    Point p = Point(1, 0, 0);
//
//    if (this->axis[1] != 1)
//    {
//        p = this->axis * Point(0, 1, 0);
//    }
//    Point p2 = (this->axis).cross(p);
//
//    for (int i = 0; i < 4; i++)
//    {
//        if (this->center[0] > max_bounds[0])
//        {
//            max_bounds[0] = this->center[0];
//        }
//        if (this->center[0] < min_bounds[0])
//        {
//            min_bounds[0] = this->center[0];
//        }
//        if (this->center[1] > max_bounds[1])
//        {
//            max_bounds[1] = this->center[1];
//        }
//        if (this->center[1] < min_bounds[1])
//        {
//            min_bounds[1] = this->center[1];
//        }
//        if (this->center[2] > max_bounds[2])
//        {
//            max_bounds[2] = this->center[2];
//        }
//        if (this->center[2] < min_bounds[2])
//        {
//            min_bounds[2] = this->center[2];
//        }
//
//        p = p2;
//        p2 = (this->axis).cross(p);
//    }
//
//    return new Point(min_bounds, max_bounds);
//}

Point Cone::rayIntersect(Point rayOrigin, Point rayDirection)
{
    float cos_theta = this->height / sqrt(pow(this->height, 2) + pow(this->radius, 2));

    Point normal_aux = this->axis * this->height;

    Point vertex = this->center + normal_aux;

    Point d = rayDirection.normalized();

    Point v = vertex - rayOrigin;

    float a = pow(d.dot(this->axis), 2) - (d.dot(d) * pow(cos_theta, 2));

    float b = d.dot(v) * pow(cos_theta, 2) - ((d.dot(this->axis) * v.dot(this->axis)));

    float c = pow(v.dot(this->axis), 2) - (pow(cos_theta, 2) * v.dot(v));

    float delta = b*b - (a * c);

    float t1, t2;
    Point pi = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    if (delta > 0)
    {
        if (a != 0)
        {
            t1 = (-b + sqrt(delta)) / a;
            t2 = (-b - sqrt(delta)) / a;
        }
        else
        {
            t1 = -c / (2 * b);
            t2 = -c / (2 * b);
        }

        Point p1 = rayOrigin + d * t1;
        Point p2 = rayOrigin + d * t2;

        Point bi = base_intesection(rayOrigin, d);
        if (validate(this->origin, p1))
        {
            pi = p1;
        }
        else if (bi[0] < MAXFLOAT)
        {
            pi = bi;
        }

        float d1 = MAXFLOAT;
        if (pi[0] < MAXFLOAT)
        {
            d1 = sqrt(pow(pi[0] - rayOrigin[0], 2) + pow(pi[1] - rayOrigin[1], 2) + pow(pi[2] - rayOrigin[2], 2));
        }

        float d2 = sqrt(pow(p2[0] - rayOrigin[0], 2) + pow(p2[1] - rayOrigin[1], 2) + pow(p2[2] - rayOrigin[2], 2));
        if (validate(this->origin, p2))
        {
            if (!(pi[0] < MAXFLOAT) || d2 < d1)
            {
                pi = p2;
            }

        }
        else if (bi[0] < MAXFLOAT)
        {
            pi = bi;
        }
    }
    else if (delta == 0 && b != 0 && a != 0)
    {
        t1 = -b + sqrt(delta) / a;
        Point p1 = rayOrigin + d * t1;
        Point bi = base_intesection(rayOrigin, d);
        float db = sqrt(pow(bi[0] - rayOrigin[0], 2) + pow(bi[1] - rayOrigin[1], 2) + pow(bi[2] - rayOrigin[2], 2));
        float dp = sqrt(pow(p1[0] - rayOrigin[0], 2) + pow(p1[1] - rayOrigin[1], 2) + pow(p1[2] - rayOrigin[2], 2));
        if (validate(this->origin, p1))
        {
            pi = p1;
        }
        else if (bi[0] < MAXFLOAT && (!(pi[0] < MAXFLOAT) || db < dp))
        {
            pi = bi;
        }
    }
    return pi;
};

Point Cone::normal(Point point)
{
    Point v = this->height * this->axis;
    Point n = this->center + v;
    Point a = point - this->center;

    float f = a.dot(this->axis);
    Point p = this->center + f * this->axis;

    Point a2 = point - p;
    Point a3 = n - point;

    Point T = a2.cross(a3);
    Point N = (a3.cross(T)).normalized();

    return N;

};