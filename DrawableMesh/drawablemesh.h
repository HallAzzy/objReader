#ifndef DRAWABLE_DRAWABLEMESH_H
#define DRAWABLE_DRAWABLEMESH_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "DrawableObject/drawableobject.h"

namespace Drawable {

class DrawableMesh : public DrawableObject
{
public:
    DrawableMesh();
    DrawableMesh(
            const QVector<int> &triangulatedVertices,
            const QVector<QVector3D> &vertices);
    DrawableMesh(const DrawableMesh &other) = delete;
    DrawableMesh &operator=(const DrawableMesh &other) = delete;

    ~DrawableMesh() override;
    void draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) override;
    static QVector<float> triangleCoordinatesVector(
            const QVector<int> &triangulatedVertices,
            const QVector<QVector3D> &vertices);
    static QVector<float> calcNormals(
            const QVector<int> &triangulatedVertices,
            const QVector<QVector3D> &vertices);
private:
    QOpenGLBuffer *m_vertexBuffer = nullptr;
    QOpenGLBuffer *m_normalBuffer = nullptr;
    QOpenGLShaderProgram *m_shader = nullptr;
    int m_verticesAmount = 0;

    QOpenGLShaderProgram *createShaderProgram(QString vertexShaderFileName, QString fragmentShaderFileName);
};

}

#endif // DRAWABLE_DRAWABLEMESH_H
