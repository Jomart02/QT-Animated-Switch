#include <QApplication>
#include "TestWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWindow *n = new TestWindow();
    n->show();
    return a.exec();
}