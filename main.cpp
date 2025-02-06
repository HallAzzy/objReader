#include <QCoreApplication>
#include "QDebug"
#include "objreadertest.h"

int main()
{
    /*QString s = "# a  b c  d # comm";
    QStringList sl = s.split(" ", Qt::SkipEmptyParts);
    sl.pop_front();
    for (int i = 0; i < sl.size(); ++i) {
        if (sl[i].startsWith("#")) {
            sl = sl.mid(0, i); // Обрезаем список до текущего элемента
            break;
        }
    }
    qDebug() << q.isEmpty();*/

    ObjReader::Test::ObjReaderTest test;
    QTest::qExec(&test);
}
