#include "libs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(qApp->applicationDirPath() + "/resources/style.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    a.topLevelWindows();

    Game w;
    w.show();

    return a.exec();
}
