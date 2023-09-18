#include "mainwindow.h"

#include <QApplication>

#include "jsonreader.h"

// Приложение состоит из: главного окна, внутреннего виджета отображения и функционирования с OpenGl, я бы отделил чтение файла json и создание AIS_object

int main(int argc, char *argv[])
{


    jsonReader json_doc("../blade_data.json");
    qDebug() << json_doc.is_open();


    std::shared_ptr<std::deque<std::list<gp_Pnt>>> PTR_BLYAT = json_doc.parse_data();



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
