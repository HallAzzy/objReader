#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "Camera/camera.h"
#include "DrawableObject/drawableobject.h"

namespace Viewport {

class Viewport : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit Viewport(QWidget *parent = nullptr, Camera *camera = nullptr);
    ~Viewport();
    void addModel(Drawable::DrawableObject *drawableObject);
    void removeModel(Drawable::DrawableObject *drawableObject);
    void clearModels();
    Viewport(const Viewport &other) = delete;
    Viewport &operator=(const Viewport &other) = delete;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void zooming(const QPoint &dstPos);
    void rotation(const QPoint &dstPos);
    void panning(const QPoint &dstPos);
    void wheelZooming(float delta);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    enum class State {
        None,
        Pan,
        Zoom,
        Rotate
    };

    QVector<Drawable::DrawableObject *> m_models;
    Camera *m_camera = nullptr;
    QQuaternion m_cameraRotation;
    QColor m_backgroundColor = QColor(100, 100, 100);
    State m_state = State::None;
    QPoint m_prevPos;

    float aspectRatio() const;
    static QVector3D unprojectScreenPointToEye(
            const QPoint &pos,
            float depth,
            const QMatrix4x4 &projectionMatrix,
            const QSize &screenSize);
};
}
#endif // VIEWPORT_H
