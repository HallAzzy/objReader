#ifndef DRAWABLE_DRAWABLEMESH_H
#define DRAWABLE_DRAWABLEMESH_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "DrawableObject/drawableobject.h"
#include "Mesh/mesh.h"

namespace Drawable {

class DrawableMesh : public DrawableObject
{
public:
    DrawableMesh();
    DrawableMesh(const DrawableMesh &other) = delete;
    ~DrawableMesh() override;
    void draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) override;
    DrawableMesh &operator=(const DrawableMesh &other) = delete;
    QVector<float> triangleCoordinatesVector(const QVector<int> &triangulatedVertices,
                                             const QVector<QVector3D> &vertices) const;
    
private:
    QOpenGLBuffer *m_vertexBuffer = nullptr;
    QOpenGLBuffer *m_normalBuffer = nullptr;
    QOpenGLShaderProgram *m_shader = nullptr;
    int m_verticesAmount = 0;
};

}

#endif // DRAWABLE_DRAWABLEMESH_H
