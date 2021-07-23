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

    return false;
}

void BoundingBox::updateEdges()
{
    edges[0] = Vector3D(-width / 2.0f, height / 2.0f, depth / 2.0f);
    edges[1] = Vector3D(width / 2.0f, height / 2.0f, depth / 2.0f);
    edges[2] = Vector3D(-width / 2.0f, -height / 2.0f, depth / 2.0f);
    edges[3] = Vector3D(width / 2.0f, -height / 2.0f, depth / 2.0f);
    edges[4] = Vector3D(-width / 2.0f, height / 2.0f, -depth / 2.0f);
    edges[5] = Vector3D(width / 2.0f, height / 2.0f, -depth / 2.0f);
    edges[6] = Vector3D(-width / 2.0f, -height / 2.0f, -depth / 2.0f);
    edges[7] = Vector3D(width / 2.0f, -height / 2.0f, -depth / 2.0f);

    facePoints[0] = Vector3D(-width / 2.0f, 0.0f, 0.0f);
    facePoints[1] = Vector3D(width / 2.0f, 0.0f, 0.0f);
    facePoints[2] = Vector3D(0.0f, -height / 2.0f, 0.0f);
    facePoints[3] = Vector3D(0.0f, height / 2.0f, 0.0f);
    facePoints[4] = Vector3D(0.0f, 0.0f, -depth / 2.0f);
    facePoints[5] = Vector3D(0.0f, 0.0f, depth / 2.0f);

    edges[0] = Quaternion::rotatePointEuler(edges[0], rotation);
    edges[1] = Quaternion::rotatePointEuler(edges[1], rotation);
    edges[2] = Quaternion::rotatePointEuler(edges[2], rotation);
    edges[3] = Quaternion::rotatePointEuler(edges[3], rotation);
    edges[4] = Quaternion::rotatePointEuler(edges[4], rotation);
    edges[5] = Quaternion::rotatePointEuler(edges[5], rotation);
    edges[6] = Quaternion::rotatePointEuler(edges[6], rotation);
    edges[7] = Quaternion::rotatePointEuler(edges[7], rotation);

    facePoints[0] = Quaternion::rotatePointEuler(facePoints[0], rotation);
    facePoints[1] = Quaternion::rotatePointEuler(facePoints[1], rotation);
    facePoints[2] = Quaternion::rotatePointEuler(facePoints[2], rotation);
    facePoints[3] = Quaternion::rotatePointEuler(facePoints[3], rotation);
    facePoints[4] = Quaternion::rotatePointEuler(facePoints[4], rotation);
    facePoints[5] = Quaternion::rotatePointEuler(facePoints[5], rotation);
}
