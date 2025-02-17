#ifndef VIEWPORT_CAMERA_H
#define VIEWPORT_CAMERA_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <math.h>

namespace Viewport {

class Camera
{
public:
    Camera();
    QMatrix4x4 viewMatrix() const;
    QMatrix4x4 projectionMatrix(float screenAspectRatio) const;
    void setFov(float fov);
    void setZNear(float zNear);
    void setZFar(float zFar);
    void setOrigin(const QVector3D &origin);
    void setTarget(const QVector3D &target);
    void setRotation(const QQuaternion &rotation);
    QQuaternion rotation() const;
    QVector3D origin() const;
    QVector3D target() const;

protected:
    float m_fovY = 60;
    float m_zNear = 0.01;
    float m_zFar = 1000;
    QVector3D m_origin = {0, 0, 5};
    QVector3D m_target = {0, 0, 0};
    QQuaternion m_rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -30);

    QMatrix4x4 cameraToWorldMatrix() const;
    static float degToRad(float degree);
};

} // namespace Viewport

#endif // VIEWPORT_CAMERA_H
