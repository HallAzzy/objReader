#ifndef MYMESH_BOUNDINGBOX_H
#define MYMESH_BOUNDINGBOX_H
#include <QVector>
#include <QVector3D>

namespace MyMesh {

class BoundingBox
{
public:
    BoundingBox() = default;
    BoundingBox(const QVector3D &nearestLeftBottom, const QVector3D &farthestRightTop);
    static BoundingBox fromVertices(const QVector<QVector3D> &vertices);
    const QVector3D nearestLeftBottom() const;
    const QVector3D farthestRightTop() const;
    bool operator==(const BoundingBox &other) const;

private:
    QVector3D m_nearestLeftBottom;
    QVector3D m_farthestRightTop;
};

} // namespace MyMesh

#endif // MYMESH_BOUNDINGBOX_H
