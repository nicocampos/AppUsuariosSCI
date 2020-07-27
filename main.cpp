#include "usuarioconfig.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Usuarioconfig w;
    w.show();

    return a.exec();
}
