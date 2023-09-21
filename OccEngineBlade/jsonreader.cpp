
#include "jsonreader.h"

jsonReader::jsonReader(QString filename): status_file_(false)
{
    if(filename == "") return;

    file_.setFileName(filename);
    if (file_.open(QIODevice::ReadOnly | QIODevice::Text)){
        status_file_ = true;
        json_document_ = QJsonDocument::fromJson(QString(file_.readAll()).toUtf8());
        return;
    }
}

jsonReader::~jsonReader()
{
    file_.close();
}


bool jsonReader::is_open(){
    return status_file_;
}

bool jsonReader::open_file(QString filename){
    file_.close();

    file_.setFileName(filename);
    if (file_.open(QIODevice::ReadOnly | QIODevice::Text)){
        status_file_ = true;
        json_document_ = QJsonDocument::fromJson(QString(file_.readAll()).toUtf8());
    }
    else
        status_file_ = false;

    return status_file_;
}

// Данный метод разбить на функции проблемотично, так как одни и теже точки входят в разные поферхности.
// лопатка имеет 4 поверхности:
// cx - convex - спинка (более арочная)
// cv - concave - корыто (менее арочная)
// le - left edge - левая кромка (окружность)
// re - right edge - правая кромка (окружность)

std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>> jsonReader::parse_data()
{
    // Файл не прочитан или ошибка чтения, возвращает пустой указатель.
    if (!status_file_ || json_document_.isEmpty()) return std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>>();

    QJsonObject data;

    int count = 0;
    ptr_points_ = std::make_shared<std::map<std::string, std::deque<std::list<gp_Pnt>>>>();

    data = json_document_.object();


    for (QJsonObject::iterator it = data.begin(); it < data.end(); it++){


        QJsonObject set_points = it->toObject();
        double z = set_points["z"].toDouble();

        // Чтение cx
        QJsonArray x = set_points["x_cx"].toArray();
        QJsonArray y = set_points["y_cx"].toArray();

        qsizetype size_array = x.size();


        ptr_points_->operator[]("cx").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("cx").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        // Чтение le
        x = set_points["x_le"].toArray();
        y = set_points["y_le"].toArray();

        size_array = x.size();

        ptr_points_->operator[]("le").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("le").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));

        }

        // Чтение cv
        x = set_points["x_cv"].toArray();
        y = set_points["y_cv"].toArray();

        size_array = x.size();

        ptr_points_->operator[]("cv").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("cv").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        // Чтение re
        x = set_points["x_re"].toArray();
        y = set_points["y_re"].toArray();

        size_array = x.size();

        ptr_points_->operator[]("re").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("re").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        count++;
    }

    // построение множества точек крышки лопатки
    ptr_points_->operator[]("up").push_back(std::list<gp_Pnt>());

    auto it = ptr_points_-> operator[]("cx").front().begin();
    auto endIt = ptr_points_-> operator[]("cx").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").front().push_back(*it);
    }

    it = ptr_points_-> operator[]("le").front().begin();
    endIt = ptr_points_-> operator[]("le").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").front().push_back(*it);
    }

     it = ptr_points_-> operator[]("cv").front().begin();
     endIt = ptr_points_-> operator[]("cv").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").front().push_back(*it);
    }

    it = ptr_points_-> operator[]("re").front().begin();
    endIt = ptr_points_-> operator[]("re").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").front().push_back(*it);
    }

    // построение множества точек дна лопатки
    ptr_points_->operator[]("dw").push_back(std::list<gp_Pnt>());

    it = ptr_points_-> operator[]("cx").back().begin();
    endIt = ptr_points_-> operator[]("cx").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").front().push_back(*it);
    }

    it = ptr_points_-> operator[]("le").back().begin();
    endIt = ptr_points_-> operator[]("le").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").front().push_back(*it);
    }

    it = ptr_points_-> operator[]("cv").back().begin();
    endIt = ptr_points_-> operator[]("cv").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").front().push_back(*it);
    }

    it = ptr_points_-> operator[]("re").back().begin();
    endIt = ptr_points_-> operator[]("re").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").front().push_back(*it);
    }

    // добавление крайних точек le и re в cv и cx
    for(int i = 0; i < count; i++){
        ptr_points_-> operator[]("cx").operator[](i).push_back(ptr_points_-> operator[]("le").operator[](i).front());
    }

    for(int i = 0; i < count; i++){
        ptr_points_-> operator[]("cv").operator[](i).push_front(ptr_points_-> operator[]("le").operator[](i).back());
    }

    for(int i = 0; i < count; i++){
        ptr_points_-> operator[]("cv").operator[](i).push_back(ptr_points_-> operator[]("re").operator[](i).front());
    }

    for(int i = 0; i < count; i++){
        ptr_points_-> operator[]("cx").operator[](i).push_front(ptr_points_-> operator[]("re").operator[](i).back());
    }


    return ptr_points_;

}
