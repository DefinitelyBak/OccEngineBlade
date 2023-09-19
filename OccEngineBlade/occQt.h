/*
*    Copyright (c) 2018 Shing Liu All Rights Reserved.
*
*           File : occQt.h
*         Author : Shing Liu(eryar@163.com)
*           Date : 2018-01-08 20:00
*        Version : OpenCASCADE7.2.0 & Qt5.7.1
*
*    Description : OpenCASCADE in Qt.
*/

#ifndef OCCQT_H
#define OCCQT_H

#include "ui_occQt.h"
#include "jsonreader.h"
#include "builderaisshape.h"

#include <AIS_ViewController.hxx>

class OccView;

// Главный виджет, внутри него будет происходить магия.

// Честно сказать класс спизжен, но отредактирован ^_^

class occQt : public QMainWindow
{
    Q_OBJECT

public:
    occQt(QWidget *parent = nullptr);
    ~occQt();

protected:

    void createActions(void);
    void createMenus(void);
    void createToolBars(void);


private slots:

    void about(void);

private:
    Ui::occQtClass ui;

    // wrapped the widget for occ.
    OccView* myOccView;


    jsonReader reader;
    builderAisShape builder;
};

#endif // OCCQT_H
