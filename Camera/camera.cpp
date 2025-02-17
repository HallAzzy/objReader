#include "camera.h"

namespace Viewport {

Camera::Camera()
{

}

QMatrix4x4 Camera::viewMatrix() const
{
    QMatrix4x4 cameraToWorld = cameraToWorldMatrix();
    bool invertible = true;
    QMatrix4x4 worldToCamera = cameraToWorld.inverted(&invertible);
    if (!invertible)
        qFatal("Can't invert camera matrix");
    return worldToCamera;
}

QMatrix4x4 Camera::projectionMatrix(float screenAspectRatio) const
{
    float ySide = m_zNear * tan(degToRad(m_fovY) / 2);
    float xMax = ySide * screenAspectRatio;
    float yMax = ySide;
    float xMin = -xMax;
    float yMin = -yMax;
    QMatrix4x4 projectionMatrix;
    projectionMatrix.frustum(xMin, xMax, yMin, yMax, m_zNear, m_zFar);
    return projectionMatrix;
}

void Camera::setFov(float fov)
{
    m_fovY = fov;
}

void Camera::setZNear(float zNear)
{
    m_zNear = zNear;
}

void Camera::setZFar(float zFar)
{
    m_zFar = zFar;
}

void Camera::setOrigin(const QVector3D &origin)
{
    m_origin = origin;
}

void Camera::setTarget(const QVector3D &target)
{
    m_target = target;
}

void Camera::setRotation(const QQuaternion &rotation)
{
    m_rotation = rotation;
}

QQuaternion Camera::rotation() const
{
    return m_rotation;
}

QVector3D Camera::origin() const
{
    return m_origin;
}

QVector3D Camera::target() const
{
    return m_target;
}

QMatrix4x4 Camera::cameraToWorldMatrix() const
{
    QMatrix4x4 camToWorld;
    camToWorld.translate(m_target);
    camToWorld.rotate(m_rotation);
    camToWorld.translate(m_origin);
    return camToWorld;
}

float Camera::degToRad(float degree)
{
    return degree / 180 * M_PI;
}
} // namespace Viewport
