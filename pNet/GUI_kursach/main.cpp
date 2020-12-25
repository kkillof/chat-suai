#include "GUI_kursach.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI_kursach w;
    w.show();
    return a.exec();
}
