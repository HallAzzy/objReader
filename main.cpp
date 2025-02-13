#include <QCoreApplication>
#include "ObjReaderUnitTest/objreadertest.h"
#include "ObjReader/objreader.h"
#include "MeshUnitTest/meshtest.h"
#include "Viewport/viewport.h"
#include <QMainWindow>
#include <QOffscreenSurface>

int main(int argc, char *argv[])
{
//    ObjReader::Test::ObjReaderTest oTest;
//    MyMesh::Test::MeshTest mTest;
//    return QTest::qExec(&mTest) + QTest::qExec(&oTest);

    QApplication app(argc, argv);

    QMainWindow window;
    Viewport::Viewport viewport;
    MyMesh::Mesh mesh;
    ObjReader::readObj("/home/anton/objReader/ObjReader/ObjReaderUnitTest/modelexp.obj", mesh);
    QVector<float> vertices = mesh.toFlat();
    window.setCentralWidget(&viewport);
    window.resize(800, 600);
    window.show();
    viewport.addObject(vertices);
    return app.exec();
}
