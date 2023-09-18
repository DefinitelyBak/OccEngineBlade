
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

std::shared_ptr<std::deque<std::list<gp_Pnt>>> jsonReader::parse_data()
{
    if (!status_file_) return std::shared_ptr<std::deque<std::list<gp_Pnt>>>();

    //qDebug() << json_document_;
    QJsonObject data;

    int count = 0;;
    deque_points_ = new std::deque<std::list<gp_Pnt>>;

    if (json_document_.isObject())  data = json_document_.object();

    for (QJsonObject::iterator it = data.begin(); it < data.end(); it++){
        deque_points_->push_back(std::list<gp_Pnt>());

        QJsonObject set_points = it->toObject();
        double z = set_points["z"].toDouble();

        // 1
        QJsonArray x = set_points["x_cx"].toArray();
        QJsonArray y = set_points["y_cx"].toArray();

        qsizetype size_array = x.size();


        for(qsizetype i = 0; i < size_array; i++){
            deque_points_->operator [](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        // 2
        x = set_points["x_le"].toArray();
        y = set_points["y_le"].toArray();

        size_array = x.size();

        for(qsizetype i = 0; i < size_array; i++){
            deque_points_->operator [](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        // 3
        x = set_points["x_cv"].toArray();
        y = set_points["y_cv"].toArray();

        size_array = x.size();

        for(qsizetype i = 0; i < size_array; i++){
            deque_points_->operator [](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        // 4
        x = set_points["x_re"].toArray();
        y = set_points["y_re"].toArray();

        size_array = x.size();

        for(qsizetype i = 0; i < size_array; i++){
            deque_points_->operator [](count).push_back(gp_Pnt(x[i].toDouble(), y[i].toDouble(), z));
        }

        count++;
    }

    return std::shared_ptr<std::deque<std::list<gp_Pnt>>>(deque_points_);

}
