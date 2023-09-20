
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

std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>> jsonReader::parse_data()
{
    // Файл не прочитан или ошибка чтения, возвращает пустой указатель.
    if (!status_file_ || !json_document_.isObject()) return std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>>();

    QJsonObject data;

    int count = 0;
    ptr_points_ = new std::map<std::string, std::deque<std::list<gp_Pnt>>>;

    data = json_document_.object();


    for (QJsonObject::iterator it = data.begin(); it < data.end(); it++){


        QJsonObject set_points = it->toObject();
        double z = set_points["z"].toDouble();

        // 1
        QJsonArray x = set_points["x_cx"].toArray();
        QJsonArray y = set_points["y_cx"].toArray();

        qsizetype size_array = x.size();


        ptr_points_->operator[]("cx").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("cx").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        // 2
        x = set_points["x_le"].toArray();
        y = set_points["y_le"].toArray();

        size_array = x.size();

        ptr_points_->operator[]("le").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("le").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));

        }

        // 3
        x = set_points["x_cv"].toArray();
        y = set_points["y_cv"].toArray();

        size_array = x.size();

        ptr_points_->operator[]("cv").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("cv").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        // 4
        x = set_points["x_re"].toArray();
        y = set_points["y_re"].toArray();

        size_array = x.size();

        ptr_points_->operator[]("re").push_back(std::list<gp_Pnt>());
        for(qsizetype i = 0; i < size_array; i++){
            ptr_points_-> operator[]("re").operator[](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        count++;
    }

    //
    ptr_points_->operator[]("up").push_back(std::list<gp_Pnt>());

    auto it = ptr_points_-> operator[]("cx").front().begin();
    auto endIt = ptr_points_-> operator[]("cx").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").operator[](0).push_back(*it);
    }

    it = ptr_points_-> operator[]("le").front().begin();
    endIt = ptr_points_-> operator[]("le").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").operator[](0).push_back(*it);
    }

     it = ptr_points_-> operator[]("cv").front().begin();
     endIt = ptr_points_-> operator[]("cv").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").operator[](0).push_back(*it);
    }

    it = ptr_points_-> operator[]("re").front().begin();
    endIt = ptr_points_-> operator[]("re").front().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("up").operator[](0).push_back(*it);
    }

    //
    ptr_points_->operator[]("dw").push_back(std::list<gp_Pnt>());

    it = ptr_points_-> operator[]("cx").back().begin();
    endIt = ptr_points_-> operator[]("cx").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").operator[](0).push_back(*it);
    }

    it = ptr_points_-> operator[]("le").back().begin();
    endIt = ptr_points_-> operator[]("le").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").operator[](0).push_back(*it);
    }

    it = ptr_points_-> operator[]("cv").back().begin();
    endIt = ptr_points_-> operator[]("cv").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").operator[](0).push_back(*it);
    }

    it = ptr_points_-> operator[]("re").back().begin();
    endIt = ptr_points_-> operator[]("re").back().end();
    for(;it != endIt; it++){
        ptr_points_->operator[]("dw").operator[](0).push_back(*it);
    }

    //
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


    return std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>> (ptr_points_);

}
