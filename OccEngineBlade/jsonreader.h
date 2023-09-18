
#ifndef JSONREADER_H
#define JSONREADER_H

#include <memory>
#include <list>
#include <deque>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

#include <gp_Pnt.hxx>

// пусть этот класс считывает точки и делает множество точек (x, y, z) для одного слайна, нихуя себе)
// взял стиль из stl так что в рот манал!

class jsonReader
{
public:
    jsonReader(QString filename = "");
    ~jsonReader();

    bool is_open();
    bool open_file(QString filename);

    std::shared_ptr<std::deque<std::list<gp_Pnt>>> parse_data();
private:
    QJsonDocument json_document_;

    QFile file_;
    bool status_file_;

    std::deque<std::list<gp_Pnt>>* deque_points_;


};

#endif // JSONREADER_H
