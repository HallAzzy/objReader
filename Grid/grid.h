#ifndef DRAWABLE_GRID_H
#define DRAWABLE_GRID_H

#include <QColor>
#include <QOpenGLBuffer>
#include "DrawableObject/drawableobject.h"

namespace Drawable {

class Grid : public Drawable::DrawableObject
{
public:
    Grid() = default;
    Grid(double size, int nSegments, QColor color);
    void draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) override;

protected:      
    double m_size = 1.0;
    int m_blockAmount = 10;
    QColor m_color = QColor(0, 255, 0);
};

} // namespace Drawable

#endif // DRAWABLE_GRID_H
