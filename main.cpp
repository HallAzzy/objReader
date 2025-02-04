#include <QCoreApplication>
#include "QDebug"
#include "objreader.h"

int main()
{
    QVector3D vertex;
    QStringList lst = {"v", "5", "2", "2"};
    QString error;
    ObjReader::parseToVertex(lst, vertex, error);
    bool isOk = true;
    error.toFloat(&isOk);
    //qDebug() << error.size();
    //ObjReader::ObjReaderTest test;
    //QTest::qExec(&test);
}
