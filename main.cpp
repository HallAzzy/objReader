#include <QCoreApplication>
#include "QDebug"
#include "unitTests/objreadertest.h"

int main()
{
    ObjReader::Test::ObjReaderTest test;
    return QTest::qExec(&test);
}
