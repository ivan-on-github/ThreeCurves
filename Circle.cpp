#include <math.h>
#include "Circle.h"

Circle::Circle(float radius)
    : r(radius > MIN_CIRCLE_R ? radius : MIN_CIRCLE_R)
{
}

Circle::~Circle()
{
}

float Circle::GetRadius()
{
    return r;
}

Vector3 Circle::GetPoint(float t)
{
    return Vector3(cos(t) * r, sin(t) * r, 0);
}

Vector3 Circle::GetFirstDerivativeVector(float t)
{
    return Vector3(-sin(t), cos(t), 0);
}

CurveType Circle::GetType()
{
    return CurveType::CIRCLE;
}