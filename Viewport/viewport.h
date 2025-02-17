#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "camera.h"
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

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QVector<Drawable::DrawableObject *> m_models;
    Camera *m_camera = nullptr;
    QQuaternion m_cameraRotation;
    QColor m_backgroundColor = QColor(170, 170, 180);

    float aspectRatio() const;
};
}
#endif // VIEWPORT_H
