#pragma once
#include "Vector3.h"
#include "Curve.h"

class Circle : public Curve
{
    float r;
public:
    Circle(float radius);
    ~Circle();
    float GetRadius();
    Vector3 GetPoint(float t);
    Vector3 GetFirstDerivativeVector(float t);
    CurveType GetType();
};
