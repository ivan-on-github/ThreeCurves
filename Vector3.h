#pragma once

class Vector3
{
public:
    float x, y, z;
    Vector3(float x, float y, float z);
    void Normalize(void);
};