#ifndef DRAWABLE_GRID_H
#define DRAWABLE_GRID_H

#include "DrawableObject/drawableobject.h"
#include <QColor>

namespace Drawable {

class Grid : public Drawable::DrawableObject
{
public:
    Grid(float size, int nSegments, QColor color);

protected:
    float m_size = 1;
    int m_blockAmount = 10;
    QColor m_color = QColor(0, 255, 0);
};

} // namespace Drawable

#endif // DRAWABLE_GRID_H
