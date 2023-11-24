#pragma once

#include "Vector3.h"
#include "Curve.h"

class Helix : public Curve
{
    float r, s;
public:
    Helix(float radius, float step);
    ~Helix();
    Vector3 GetPoint(float t);
    Vector3 GetFirstDerivativeVector(float t);
    CurveType GetType();
};