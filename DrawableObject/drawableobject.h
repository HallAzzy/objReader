#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <QMatrix4x4>

namespace Drawable {
class DrawableObject
{
public:
    DrawableObject() = default;
    DrawableObject(const DrawableObject &other) = delete;
    virtual ~DrawableObject() = default;
    virtual void draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) = 0;
    DrawableObject &operator=(const DrawableObject &other) = delete;
};
}

#endif // DRAWABLEOBJECT_H
