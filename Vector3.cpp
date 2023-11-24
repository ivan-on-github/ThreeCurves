#include <math.h>
#include "Vector3.h"

Vector3::Vector3(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
{
}

void Vector3::Normalize(void)
{
    float length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    x /= length;
    y /= length;
    z /= length;
}