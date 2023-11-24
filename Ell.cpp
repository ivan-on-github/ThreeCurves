#include <math.h>
#include "Ell.h"

Ell::Ell(float radius1, float radius2)
    : r1(radius1 > MIN_ELLIPSE_R1 ? radius1 : MIN_ELLIPSE_R1)
    , r2(radius2 > MIN_ELLIPSE_R2 ? radius2 : MIN_ELLIPSE_R2)
{
}

Ell::~Ell()
{
}

Vector3 Ell::GetPoint(float t)
{
    return Vector3(cos(t) * r1, sin(t) * r2, 0);
}

Vector3 Ell::GetFirstDerivativeVector(float t)
{
    Vector3 p1(cos(t) * r1, sin(t) * r2, 0);
    Vector3 p2(cos(t + 0.0001) * r1, sin(t + 0.0001) * r2, 0);
    Vector3 tan(p2.x - p1.x, p2.y - p1.y, 0);
    tan.Normalize();
    return tan;
}

CurveType Ell::GetType()
{
    return CurveType::ELLIPSE;
}