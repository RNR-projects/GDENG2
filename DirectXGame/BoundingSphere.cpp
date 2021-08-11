#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(Vector3D pos, float radius)
{
    this->position = pos;
    this->radius = radius;
}

BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::setPosition(Vector3D newPos)
{
    this->position = newPos;
}

void BoundingSphere::setRadius(float newRadius)
{
    this->radius = newRadius;
}

float BoundingSphere::checkRaycast(Vector3D rayOrigin, Vector3D rayDirection)
{
    //using equation (dist between center and rayOrigin) = radius
    float xDist = rayOrigin.x - this->position.x;
    float yDist = rayOrigin.y - this->position.y;
    float zDist = rayOrigin.z - this->position.z;
    
    float a = rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z;
    float b = 2.0f * (xDist * rayDirection.x + yDist * rayDirection.y + zDist * rayDirection.z);
    float c = xDist * xDist + yDist * yDist + zDist * zDist - this->radius * this->radius;
    //use quadratic equation to find the intersection points, if b^2 - 4ac < 0 then it misses so return false instead of getting sqrt of negative
    if (b * b - 4.0f * a * c < 0)
        return false;
    else
    {
        float t1 = (-b + sqrtf(b * b - 4.0f * a * c)) / (2 * a);
        float t2 = (-b - sqrtf(b * b - 4.0f * a * c)) / (2 * a);
        //check if both are negative meaning miss, else return true
        if (t1 < 0 && t2 < 0)
            return -9999;
        else 
        {
            if (t1 >= 0 && t2 >= 0)
                return fminf(t1, t2);
            else if (t1 < 0)
                return t2;
            else
                return t1;
        }
    }
}
