#include "mainwindow.h"
#include <QApplication>

#define __DTSRC_

#include "CDatatypes.h"

const char AppName[] = "Datas";
CDebug __Debug(AppName);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
