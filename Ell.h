#pragma once

#include "Vector3.h"
#include "Curve.h"

class Ell : public Curve
{
    float r1, r2;
public:
    Ell(float radius1, float radius2);
    ~Ell();
    Vector3 GetPoint(float t);
    Vector3 GetFirstDerivativeVector(float t);
    CurveType GetType();
};