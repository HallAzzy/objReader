#include <QCoreApplication>
#include "QDebug"
#include "objreader.h"
#include "objreadertest.h"

int main()
{
    QVector3D vertex;
    QStringList lst = {"v", "5", "2", "2"};
    QString error;
    ObjReader::parseVertex(lst, vertex, error);
    bool isOk = true;
    error.toFloat(&isOk);
    ObjReader::ObjReaderTest test;
    QTest::qExec(&test);
}
