#include <QMainWindow>
#include <QOffscreenSurface>
#include <QCoreApplication>

#include "ObjReaderUnitTest/objreadertest.h"
#include "ObjReader/objreader.h"
#include "MeshUnitTest/meshtest.h"
#include "Grid/grid.h"
#include "DrawableMesh/drawablemesh.h"
#include "Viewport/viewport.h"

int main(int argc, char *argv[])
{
//    ObjReader::Test::ObjReaderTest oTest;
//    MyMesh::Test::MeshTest mTest;
//    return QTest::qExec(&mTest) + QTest::qExec(&oTest);

    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

    QOpenGLContext *globalContext = QOpenGLContext::globalShareContext();
    Q_ASSERT(globalContext);
    QOffscreenSurface *surface = new QOffscreenSurface();
    surface->create();
    QOpenGLContext *glContext = new QOpenGLContext();
    glContext->setShareContext(globalContext);
    if (!glContext->create())
        qFatal("Can't create OpenGL context");
    glContext->makeCurrent(surface);

    QMainWindow window;

    MyMesh::Mesh mesh;
    ObjReader::readObj("/home/anton/objReader/ObjReader/ObjReaderUnitTest/teapot.obj", mesh);
    Drawable::DrawableMesh cube(mesh.triangulatedVertices(), mesh.vertices());


    Viewport::Camera camera;
    Viewport::Viewport viewport(&window, &camera);
    Drawable::Grid grid(100, 10, QColor::fromRgb(0, 255, 0));
    viewport.addModel(&cube);
    viewport.addModel(&grid);

    window.setCentralWidget(&viewport);
    window.resize(800, 600);
    window.show();
    return a.exec();
}
