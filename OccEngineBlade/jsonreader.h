
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

// Класс считывает точки из json файла, возвращает множество точек gp_Pnt,
// представленные в виде map <string, deque < list<gp_Pnt>>>
// string - имя поверхности лопатки.
// каждый list - срез лопатки.
//
// взят стиль из stl.

class jsonReader
{
public:
    jsonReader(QString filename = "");
    ~jsonReader();

    bool is_open();
    bool open_file(QString filename);

    std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>> parse_data();
private:
    QJsonDocument json_document_;

    QFile file_;
    bool status_file_;

    std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>> ptr_points_;
};

#endif // JSONREADER_H
