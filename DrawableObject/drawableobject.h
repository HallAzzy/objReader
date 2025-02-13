#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <QMatrix4x4>

namespace Drawable {
class DrawableObject
{
public:
    DrawableObject() = default;
    virtual ~DrawableObject() = default;
    virtual void draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) = 0;
};
}

#endif // DRAWABLEOBJECT_H
