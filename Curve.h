#pragma once

#include "Utility.h"

class Curve
{
public:
    virtual Vector3 GetPoint(float t) = 0;
    virtual Vector3 GetFirstDerivativeVector(float t) = 0;
    virtual CurveType GetType() = 0;
};