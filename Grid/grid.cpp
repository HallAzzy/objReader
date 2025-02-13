#include "grid.h"

namespace Drawable {

Grid::Grid(float size, int blockAmount, QColor color):
    m_size(size),
    m_blockAmount(blockAmount),
    m_color(color)
{
}

} // namespace Drawable
