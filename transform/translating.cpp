#include "translating.hpp"

//Returns a scaling matrix

Matrix4f translating(float sx, float sy, float sz) {
    Matrix4f translate;
    translate << 1, 0, 0, sx,
                 0, 1, 0, sy,
                 0, 0, 1, sz,
                 0, 0, 0, 1;
    return translate;
}