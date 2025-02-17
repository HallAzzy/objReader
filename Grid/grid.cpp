#include "grid.h"

namespace Drawable {

Grid::Grid(double size, int blockAmount, QColor color):
    m_size(size),
    m_blockAmount(blockAmount),
    m_color(color)
{
}

void Grid::draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix)
{
    const double blockSize = m_size / m_blockAmount;
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(viewMatrix.data());
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projectionMatrix.data());
    glColor3f(m_color.redF(), m_color.greenF(), m_color.blueF());
    glBegin(GL_LINES);
    for (int i = 0; i < m_blockAmount * 2 + 1; ++i) {
        glVertex3f(-m_size + i * blockSize, 0, -m_size);
        glVertex3f(-m_size + i * blockSize, 0, m_size);
        glVertex3f(-m_size, 0, -m_size + i * blockSize);
        glVertex3f(m_size, 0, -m_size + i * blockSize);
    }
    glEnd();
}
} // namespace Drawable
