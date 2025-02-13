#ifndef MESHTEST_H
#define MESHTEST_H

#include <QTest>
#include <QObject>
#include "Mesh/mesh.h"

namespace MyMesh::Test {
class MeshTest : public QObject
{
    Q_OBJECT

public:
    MeshTest() = default;

private slots:
//    void testEmptyMesh();
//    void testEmptyVertices();
//    void testEmptyFaces();
    void testMeshComparison();
    void testBoundBoxes();
    void testCreatingStartsVector();
    void testTriangulation();
    void testToFlat();
};
}
#endif // MESHTEST_H
