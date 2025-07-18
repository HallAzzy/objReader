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
    QMatrix4x4 projectionMatrix;

       if (m_projectionType == Perspective) {
           float ySide = m_clipPlaneNear * tan(degToRad(m_fovY) / 2);
           float xMax = ySide * screenAspectRatio;
           float yMax = ySide;
           float xMin = -xMax;
           float yMin = -yMax;
           projectionMatrix.frustum(xMin, xMax, yMin, yMax, m_clipPlaneNear, m_clipPlaneFar);
       } else {
           float halfHeight = m_orthographicSize / 2.0f;
           float halfWidth = halfHeight * screenAspectRatio;
           projectionMatrix.ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, m_clipPlaneNear, m_clipPlaneFar);
       }
       return projectionMatrix;
}

void Camera::setFov(float fov)
{
    m_fovY = fov;
}

void Camera::setClipPlaneNear(float zNear)
{
    m_clipPlaneNear = zNear;
}

Camera::ProjectionType Camera::projectionType() const
{
    return m_projectionType;
}

bool Camera::isOrthographic() const
{
    return m_projectionType == Orthographic;
}

bool Camera::isPerspective() const
{
    return m_projectionType == Perspective;
}

void Camera::setProjectionType(Camera::ProjectionType type)
{
    m_projectionType = type;
}

void Camera::setClipPlaneFar(float zFar)
{
    m_clipPlaneFar = zFar;
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

QVector3D Camera::unproject(const QMatrix4x4 &projectionMatrix, const QPointF &normScreenPoint, float depth)
{
    float zEye;
    if (projectionMatrix(3, 3) == 0) // ortho
        zEye = (depth - projectionMatrix(2, 3)) / projectionMatrix(2, 2);
    else // persp
        zEye = -depth;
    float w = projectionMatrix(3, 2) * zEye + projectionMatrix(3, 3) * 1;
    const float xClip = normScreenPoint.x() * w;
    const float yClip = normScreenPoint.y() * w;
    const float zClip = (projectionMatrix(2, 2) * zEye + projectionMatrix(2, 3));
    QVector4D ndcPoint(xClip, yClip, zClip, w);
    bool invertible = true;
    const QMatrix4x4 projectionMatrixInv = projectionMatrix.inverted(&invertible);
    Q_ASSERT(invertible);
    return QVector3D(projectionMatrixInv * ndcPoint);
}

QPointF Camera::screenPointToNormScreenPoint(const QPoint &screenPoint, const QSize &screenSize)
{
    float xNorm = 2 * (screenPoint.x()) / float(screenSize.width()) - 1;
    float yNorm = 1 - 2 *(screenPoint.y()) / float(screenSize.height());
    return QPointF(xNorm, yNorm);
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
    return degree / 180.0f * M_PI;
}
} // namespace Viewport
