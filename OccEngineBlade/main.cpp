#include <QApplication>

#include "occQt.h"

// Приложение состоит из: главного окна, внутреннего виджета отображения и функционирования с OpenGl, я бы отделил чтение файла json и создание AIS_object

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    occQt w;
    w.show();

    return a.exec();
}
