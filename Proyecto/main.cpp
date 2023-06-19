#include "analizador.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Analizador w;
    w.show();
    return a.exec();
}
