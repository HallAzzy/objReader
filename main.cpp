#include <QMainWindow>
#include <QOffscreenSurface>
#include <QCoreApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>

#include "ObjReaderUnitTest/objreadertest.h"
#include "ObjReader/objreader.h"
#include "MeshUnitTest/meshtest.h"
#include "Grid/grid.h"
#include "DrawableMesh/drawablemesh.h"
#include "Viewport/viewport.h"

int main(int argc, char *argv[])
{
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
    window.setWindowTitle("3D Model Viewer");
    window.resize(1024, 768);

    Viewport::Camera camera;
    Viewport::Viewport* viewport = new Viewport::Viewport(&window, &camera);
    window.setCentralWidget(viewport);

    MyMesh::Mesh mesh;
    Drawable::Grid* grid = new Drawable::Grid(100, 10, QColor::fromRgb(70, 180, 130));
    viewport->addModel(grid);

    QMenuBar* menuBar = window.menuBar();
    QMenu* fileMenu = menuBar->addMenu("&File");
    QMenu* viewMenu = menuBar->addMenu("&Window");

    QToolBar* toolbar = window.addToolBar("Tools");
    toolbar->setIconSize(QSize(24, 24));
    toolbar->setMovable(false);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QAction* openAction = new QAction(QIcon(":/icons/open.png"), "Open File", &window);
    QAction* fullscreenAction = new QAction(QIcon(":/icons/fullscreen.png"), "Fullscreen", &window);
    QAction* gridAction = new QAction(QIcon(":/icons/grid.png"), "Grid", &window);
    gridAction->setCheckable(true);
    gridAction->setChecked(true);

    QAction* projectionAction = new QAction(QIcon(":/icons/camera.png"), "Projection Type", &window);
    projectionAction->setCheckable(true);
    projectionAction->setChecked(camera.isPerspective());
    projectionAction->setToolTip("Switch Projection");

    QAction* exitAction = new QAction(QIcon(":/icons/exit.png"), "Exit", &window);

    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    viewMenu->addAction(fullscreenAction);
    viewMenu->addAction(gridAction);

    toolbar->addAction(openAction);
    toolbar->addAction(fullscreenAction);
    toolbar->addAction(gridAction);
    toolbar->addAction(projectionAction);
    toolbar->addSeparator();
    toolbar->addAction(exitAction);


    QObject::connect(exitAction, &QAction::triggered, &a, &QApplication::quit);
    QObject::connect(fullscreenAction, &QAction::triggered, [&]() {
        if (window.isFullScreen()) {
            window.showNormal();
            toolbar->show();
            fullscreenAction->setText("Fullscrenn");
        } else {
            window.showFullScreen();
            toolbar->show();
            fullscreenAction->setText("Windowed");
        }
    });
    QObject::connect(gridAction, &QAction::toggled, [=](bool checked) {
        grid->setVisible(checked);
        viewport->update();
    });
    QObject::connect(openAction, &QAction::triggered, [&]() {
           QString fileName = QFileDialog::getOpenFileName(&window, "Open OBJ", "", "OBJ Files (*.obj)");

           if (!fileName.isEmpty()) {
               QCoreApplication::processEvents();

               try {
                   MyMesh::Mesh newMesh;
                   QString error = ObjReader::readObj(fileName, newMesh);

                   if (!error.isEmpty()) {
                       QMessageBox::critical(&window, "Error", "Cannot open:\n" + error);
                   } else {
                       Drawable::DrawableMesh* model = new Drawable::DrawableMesh(
                           newMesh.triangulatedVertices(), newMesh.vertices());
                       viewport->addModel(model);
                   }
               } catch (...) {
                   QMessageBox::critical(&window, "Error", "Fatal error during file reading");
               }
           }
       });
    QObject::connect(projectionAction, &QAction::toggled, [&](bool checked) {
        if (checked) {
            camera.setProjectionType(Viewport::Camera::Perspective);
            projectionAction->setIcon(QIcon(":/icons/perspective.png"));
            projectionAction->setToolTip("Switch to Orthographic");
        } else {
            camera.setProjectionType(Viewport::Camera::Orthographic);
            projectionAction->setIcon(QIcon(":/icons/orthographic.png"));
            projectionAction->setToolTip("Switch to Perspective");
        }
        viewport->update();
    });

//    ObjReader::readObj("/home/anton/objReader/ObjReader/ObjReaderUnitTest/WrapSkull.obj", mesh);
//    Drawable::DrawableMesh skull(mesh.triangulatedVertices(), mesh.vertices());
//    ObjReader::readObj("/home/anton/objReader/ObjReader/ObjReaderUnitTest/WrapJaw.obj", mesh);
//    Drawable::DrawableMesh jaw(mesh.triangulatedVertices(), mesh.vertices());
//    ObjReader::readObj("/home/anton/objReader/ObjReader/ObjReaderUnitTest/WrapFemaleBody.obj", mesh);
//    Drawable::DrawableMesh body(mesh.triangulatedVertices(), mesh.vertices());


//    viewport.addModel(&skull);
//    viewport.addModel(&jaw);
//    viewport->addModel(&body);
    viewport->addModel(grid);

    window.show();

    return a.exec();
}
