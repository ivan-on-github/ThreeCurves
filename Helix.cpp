#define _USE_MATH_DEFINES
#include <math.h>
#include "Helix.h"

Helix::Helix(float radius, float step)
    : r(radius > MIN_HELIX_R ? radius : MIN_HELIX_R)
    , s(step > MIN_HELIX_S ? step : MIN_HELIX_S)
{
}

Helix::~Helix()
{
}

Vector3 Helix::GetPoint(float t)
{
    return Vector3(cos(t) * r, sin(t) * r, t / (2 * M_PI) * s);
}

Vector3 Helix::GetFirstDerivativeVector(float t)
{
    Vector3 tan(-sin(t) * 2 * M_PI * r, cos(t) * 2 * M_PI * r, s);
    tan.Normalize();
    return tan;
}

CurveType Helix::GetType()
{
    return CurveType::HELIX;
}