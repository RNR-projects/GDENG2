#include "BoundingBox.h"

BoundingBox::BoundingBox(Vector3D pos, Vector3D rotation, float width, float height, float depth)
{
    this->position = pos;
    this->rotation = rotation;
    this->width = width;
    this->height = height;
    this->depth = depth;

    updateEdges();
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::setPosition(Vector3D newPos)
{
    this->position = newPos;
}

void BoundingBox::setDimensions(float newWidth, float newHeight, float newDepth)
{
    this->width = newWidth;
    this->height = newHeight;
    this->depth = newDepth;

    updateEdges();
}

void BoundingBox::setRotation(Vector3D newRotation)
{
    this->rotation = newRotation;

    updateEdges();
}

bool BoundingBox::checkRaycast(Vector3D rayOrigin, Vector3D rayDirection)
{
    //get reverse rotation direction for converting
    Vector3D reverseRotation = Vector3D(-rotation.x, -rotation.y, -rotation.z);
    //face 1
    //check if ray is perpendicular with face normal
    float dot = Vector3D::dotProduct(rayDirection, facePoints[0]);
    if (dot != 0)
    {
        //convert ray direction and origin to object space
        Vector3D convertedOrigin = Quaternion::rotatePointEuler(rayOrigin - this->position, reverseRotation);
        Vector3D convertedDirection = Quaternion::rotatePointEuler(rayDirection, reverseRotation);
        //get the scalar where the ray's x component intersects with the plane's x component and possibly the plane itself
        float t = (-convertedOrigin.x - width / 2.0f) / convertedDirection.x;
        //if negative then the face in behind the camera and not actually being aimed at
        if (t >= 0)
        {
            Vector3D possibleLocation(0, convertedOrigin.y + convertedDirection.y * t, convertedOrigin.z + convertedDirection.z * t);
            //check if the intersection point is inside the face quadrilateral
            if (possibleLocation.y <= height / 2.0f && possibleLocation.y >= -height / 2.0f)
                if (possibleLocation.z <= depth / 2.0f && possibleLocation.z >= -depth / 2.0f)
                    return true;
        }
    }
    //face 2
    dot = Vector3D::dotProduct(rayDirection, facePoints[1]);
    if (dot != 0)
    {
        Vector3D convertedOrigin = Quaternion::rotatePointEuler(rayOrigin - this->position, reverseRotation);
        Vector3D convertedDirection = Quaternion::rotatePointEuler(rayDirection, reverseRotation);

        float t = (-convertedOrigin.x + width / 2.0f) / convertedDirection.x;
        if (t >= 0)
        {
            Vector3D possibleLocation(0, convertedOrigin.y + convertedDirection.y * t, convertedOrigin.z + convertedDirection.z * t);
            if (possibleLocation.y <= height / 2.0f && possibleLocation.y >= -height / 2.0f)
                if (possibleLocation.z <= depth / 2.0f && possibleLocation.z >= -depth / 2.0f)
                    return true;
        }
    }
    //face 3
    dot = Vector3D::dotProduct(rayDirection, facePoints[2]);
    if (dot != 0)
    {
        Vector3D convertedOrigin = Quaternion::rotatePointEuler(rayOrigin - this->position, reverseRotation);
        Vector3D convertedDirection = Quaternion::rotatePointEuler(rayDirection, reverseRotation);

        float t = (-convertedOrigin.y - height / 2.0f) / convertedDirection.y;
        if (t >= 0)
        {
            Vector3D possibleLocation(convertedOrigin.x + convertedDirection.x * t, 0, convertedOrigin.z + convertedDirection.z * t);
            if (possibleLocation.x <= width / 2.0f && possibleLocation.x >= -width / 2.0f)
                if (possibleLocation.z <= depth / 2.0f && possibleLocation.z >= -depth / 2.0f)
                    return true;
        }
    }
    //face 4
    dot = Vector3D::dotProduct(rayDirection, facePoints[3]);
    if (dot != 0)
    {
        Vector3D convertedOrigin = Quaternion::rotatePointEuler(rayOrigin - this->position, reverseRotation);
        Vector3D convertedDirection = Quaternion::rotatePointEuler(rayDirection, reverseRotation);

        float t = (-convertedOrigin.y + height / 2.0f) / convertedDirection.y;
        if (t >= 0)
        {
            Vector3D possibleLocation(convertedOrigin.x + convertedDirection.x * t, 0, convertedOrigin.z + convertedDirection.z * t);
            if (possibleLocation.x <= width / 2.0f && possibleLocation.x >= -width / 2.0f)
                if (possibleLocation.z <= depth / 2.0f && possibleLocation.z >= -depth / 2.0f)
                    return true;
        }
    }
    //face 5
    dot = Vector3D::dotProduct(rayDirection, facePoints[4]);
    if (dot != 0)
    {
        Vector3D convertedOrigin = Quaternion::rotatePointEuler(rayOrigin - this->position, reverseRotation);
        Vector3D convertedDirection = Quaternion::rotatePointEuler(rayDirection, reverseRotation);

        float t = (-convertedOrigin.z - depth / 2.0f) / convertedDirection.z;
        if (t >= 0)
        {
            Vector3D possibleLocation(convertedOrigin.x + convertedDirection.x * t, convertedOrigin.y + convertedDirection.y * t, 0);
            if (possibleLocation.x <= width / 2.0f && possibleLocation.x >= -width / 2.0f)
                if (possibleLocation.y <= height / 2.0f && possibleLocation.y >= -height / 2.0f)
                    return true;
        }
    }
    //face 6
    dot = Vector3D::dotProduct(rayDirection, facePoints[5]);
    if (dot != 0)
    {
        Vector3D convertedOrigin = Quaternion::rotatePointEuler(rayOrigin - this->position, reverseRotation);
        Vector3D convertedDirection = Quaternion::rotatePointEuler(rayDirection, reverseRotation);

        float t = (-convertedOrigin.z + depth / 2.0f) / convertedDirection.z;
        if (t >= 0)
        {
            Vector3D possibleLocation(convertedOrigin.x + convertedDirection.x * t, convertedOrigin.y + convertedDirection.y * t, 0);
            if (possibleLocation.x <= width / 2.0f && possibleLocation.x >= -width / 2.0f)
                if (possibleLocation.y <= height / 2.0f && possibleLocation.y >= -height / 2.0f)
                    return true;
        }
    }

    return false;
}

void BoundingBox::updateEdges()
{
    /*edges[0] = Vector3D(-width / 2.0f, height / 2.0f, depth / 2.0f);
    edges[1] = Vector3D(width / 2.0f, height / 2.0f, depth / 2.0f);
    edges[2] = Vector3D(-width / 2.0f, -height / 2.0f, depth / 2.0f);
    edges[3] = Vector3D(width / 2.0f, -height / 2.0f, depth / 2.0f);
    edges[4] = Vector3D(-width / 2.0f, height / 2.0f, -depth / 2.0f);
    edges[5] = Vector3D(width / 2.0f, height / 2.0f, -depth / 2.0f);
    edges[6] = Vector3D(-width / 2.0f, -height / 2.0f, -depth / 2.0f);
    edges[7] = Vector3D(width / 2.0f, -height / 2.0f, -depth / 2.0f);*/

    facePoints[0] = Vector3D(-width / 2.0f, 0.0f, 0.0f);//0 2 4 6
    facePoints[1] = Vector3D(width / 2.0f, 0.0f, 0.0f);//1 3 5 7
    facePoints[2] = Vector3D(0.0f, -height / 2.0f, 0.0f);//2 3 6 7
    facePoints[3] = Vector3D(0.0f, height / 2.0f, 0.0f);//0 1 4 5
    facePoints[4] = Vector3D(0.0f, 0.0f, -depth / 2.0f);//4 5 6 7
    facePoints[5] = Vector3D(0.0f, 0.0f, depth / 2.0f);//0 1 2 3

    facePoints[0] = Quaternion::rotatePointEuler(facePoints[0], rotation);
    facePoints[1] = Quaternion::rotatePointEuler(facePoints[1], rotation);
    facePoints[2] = Quaternion::rotatePointEuler(facePoints[2], rotation);
    facePoints[3] = Quaternion::rotatePointEuler(facePoints[3], rotation);
    facePoints[4] = Quaternion::rotatePointEuler(facePoints[4], rotation);
    facePoints[5] = Quaternion::rotatePointEuler(facePoints[5], rotation);
}
