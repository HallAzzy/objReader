#include "viewport.h"

Viewport::Viewport::Viewport(QWidget *parent, Camera *camera) :
    QOpenGLWidget(parent),
    m_camera(camera)
{
}

Viewport::Viewport::~Viewport()
{
}

void Viewport::Viewport::addModel(Drawable::DrawableObject *drawableObject)
{
    m_models.append(drawableObject);
}

void Viewport::Viewport::removeModel(Drawable::DrawableObject *drawableObject)
{
    const int index = m_models.indexOf(drawableObject);
    if (index == -1)
        return;
    m_models.removeAt(index);
}

void Viewport::Viewport::clearModels()
{
    m_models.clear();
}

void Viewport::Viewport::initializeGL()
{
    initializeOpenGLFunctions();
}

void Viewport::Viewport::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Viewport::Viewport::paintGL()
{
    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), m_backgroundColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Drawable::DrawableObject *drawableObject : m_models)
        drawableObject->draw(m_camera->viewMatrix(), m_camera->projectionMatrix(aspectRatio()));
}

float Viewport::Viewport::aspectRatio() const
{
    Q_ASSERT(height() != 0);
    return width() / float(height());
}
