#include <QMouseEvent>

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

void Viewport::Viewport::mousePressEvent(QMouseEvent *event)
{
    bool altPressed = (event->modifiers() == Qt::AltModifier);
    bool startPanning = (event->buttons() == Qt::RightButton);
    bool startRotating = (event->buttons() == Qt::LeftButton);
    if (startPanning) {
        m_state = State::Pan;
        m_prevPos = event->pos();
    }
    bool startZooming = (event->buttons() == Qt::RightButton) && altPressed;
    if (startZooming) {
        m_state = State::Zoom;
        m_prevPos = event->pos();
    }
    if (startRotating) {
        m_state = State::Rotate;
        m_prevPos = event->pos();
        m_cameraRotation = m_camera->rotation();
    }
}

void Viewport::Viewport::mouseMoveEvent(QMouseEvent *event)
{
    if (m_state == State::Zoom)
        zooming(event->pos());
    if (m_state == State::Rotate)
        rotation(event->pos());
    if (m_state == State::Pan)
        panning(event->pos());
}

void Viewport::Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_state = State::None;
}

void Viewport::Viewport::wheelEvent(QWheelEvent *event)
{
    wheelZooming(event->delta());
}

void Viewport::Viewport::zooming(const QPoint &dstPos)
{
    const QPoint diff = dstPos - m_prevPos;
    float shift = -diff.x() - diff.y();
    QVector3D origin = m_camera->origin() * (1 + shift * 1e-3);
    m_camera->setOrigin(origin);
    m_prevPos = dstPos;
    update();
}

void Viewport::Viewport::rotation(const QPoint &dstPos)
{
    QPoint shift = dstPos - m_prevPos;
    float rotationSpeed = 0.1f;
    float angleX = -shift.y() * rotationSpeed;
    float angleY = -shift.x() * rotationSpeed;
    QQuaternion srcRotation = m_cameraRotation;
    QQuaternion dstRotationX = QQuaternion::fromAxisAndAngle(1, 0, 0, angleX);
    QQuaternion dstRotationY = QQuaternion::fromAxisAndAngle(0, 1, 0, angleY);
    QQuaternion dstRotation = dstRotationY * srcRotation * dstRotationX;
    m_cameraRotation = dstRotation;
    m_camera->setRotation(dstRotation);
    m_prevPos = dstPos;
    update();
}

void Viewport::Viewport::panning(const QPoint &dstPos)
{
    QMatrix4x4 projectionMatrix = m_camera->projectionMatrix(aspectRatio());
    float depth = m_camera->origin().z();
    QVector3D srcPos3D = unprojectScreenPointToEye(m_prevPos, depth, projectionMatrix, size());
    QVector3D dstPos3D = unprojectScreenPointToEye(dstPos, depth, projectionMatrix, size());
    QVector3D shift = dstPos3D - srcPos3D;
    m_camera->setOrigin(m_camera->origin() - shift);
    m_camera->setTarget(m_camera->target() - shift);
    m_prevPos = dstPos;
    update();
}

void Viewport::Viewport::wheelZooming(float delta)
{
    QVector3D origin = m_camera->origin();
    float speed = 1e-3f;
    origin += -delta * origin * speed;
    m_camera->setOrigin(origin);
    update();
}

QVector3D Viewport::Viewport::unprojectScreenPointToEye(const QPoint &pos, float depth, const QMatrix4x4 &projectionMatrix, const QSize &screenSize)
{
    QPointF normPos = Camera::screenPointToNormScreenPoint(pos, screenSize);
    return Camera::unproject(projectionMatrix, normPos, depth);
}
