#include "vm_mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vm_MainWidget w;
    w.show();

    return a.exec();
}
