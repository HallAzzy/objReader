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

    enum ProjectionType {
        Perspective,
        Orthographic
    };

    Camera();
    QMatrix4x4 viewMatrix() const;
    QMatrix4x4 projectionMatrix(float screenAspectRatio) const;
    void setFov(float fov);
    void setClipPlaneNear(float zNear);
    void setClipPlaneFar(float zFar);
    void setOrigin(const QVector3D &origin);
    void setTarget(const QVector3D &target);
    void setRotation(const QQuaternion &rotation);
    QQuaternion rotation() const;
    QVector3D origin() const;
    QVector3D target() const;
    static QVector3D unproject(
            const QMatrix4x4 &projectionMatrix,
            const QPointF &normScreenPoint, float depth);
    static QPointF screenPointToNormScreenPoint(
            const QPoint &screenPoint,
            const QSize &screenSize);

    void setProjectionType(ProjectionType type);
    ProjectionType projectionType() const;
    void setOrthographicSize(float size);
    bool isOrthographic() const;
    bool isPerspective() const;

private:
    float m_fovY = 60;
    float m_clipPlaneNear = 0.01;
    float m_clipPlaneFar = 1000;
    QVector3D m_origin = {0, 0, 150};
    QVector3D m_target = {0, 0, 0};
    QQuaternion m_rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -15);

    ProjectionType m_projectionType = Perspective;
    float m_orthographicSize = 100;

    QMatrix4x4 cameraToWorldMatrix() const;
    static float degToRad(float degree);
};

} // namespace Viewport

#endif // VIEWPORT_CAMERA_H
