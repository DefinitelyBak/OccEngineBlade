/*
*    Copyright (c) 2018 Shing Liu All Rights Reserved.
*
*           File : occQt.cpp
*         Author : Shing Liu(eryar@163.com)
*           Date : 2018-01-08 21:00
*        Version : OpenCASCADE7.2.0 & Qt5.7.1
*
*    Description : Qt main window for OpenCASCADE.
*/

#include "occQt.h"
#include "occView.h"

#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QDockWidget>

#include <AIS_Shape.hxx>
#include <QDebug>

occQt::occQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    myOccView = new OccView(this);

    setCentralWidget(myOccView);

    createActions();
    createMenus();
    createToolBars();

    reader.open_file("../blade_data.json");

    /*
    std::list<gp_Pnt> temp1{{21.749797821044922, 14.367202758789062, 137.6999969482422},
                           {17.14128875732422, 11.855399131774902, 137.6999969482422},
                           {17.82572364807129, 9.761122703552246, 120.55714416503906},
                           {22.580032348632812, 11.651630401611328, 120.55714416503906}};

    std::list<gp_Pnt> temp2{{17.14128875732422, 11.855399131774902, 137.6999969482422},
                            {12.563554763793945, 9.28793716430664, 137.6999969482422},
                            {13.101649284362793, 7.796238899230957, 120.55714416503906},
                            {17.82572364807129, 9.761122703552246, 120.55714416503906}};
    */
/*
    std::deque<std::list<gp_Pnt>> cx = reader.parse_data()->operator[]("cx");


    builder.set_points(*reader.parse_data());
    builder.make_solid();
    builder.make_ais_shape();
    myOccView->getContext()->Display(builder.get_AIS_shape(), false);

    std::deque<std::list<gp_Pnt>> le = reader.parse_data()->operator[]("le");

    builder.set_points(le);
    builder.make_solid();
    builder.make_ais_shape();
    myOccView->getContext()->Display(builder.get_AIS_shape(), false);

    std::deque<std::list<gp_Pnt>> cv = reader.parse_data()->operator[]("cv");

    builder.set_points(cv);
    builder.make_solid();
    builder.make_ais_shape();
    myOccView->getContext()->Display(builder.get_AIS_shape(), false);

    std::deque<std::list<gp_Pnt>> re = reader.parse_data()->operator[]("re");

    builder.set_points(re);
    builder.make_solid();
    builder.make_ais_shape();
    myOccView->getContext()->Display(builder.get_AIS_shape(), false);
*/

    //TopoDS_Face A1 = builder.primitiv_surface_Bezier(temp1);
    //TopoDS_Face A2 = builder.primitiv_surface_Bezier(temp2);

    //TopoDS_Shell shell;
    //TopoDS_Builder b;

    //b.MakeShell(shell);

    //b.Add(shell, A1);
    //b.Add(shell, A2);

    //Handle(AIS_Shape) ptr = new AIS_Shape(shell);

    //myOccView->getContext()->Display(ptr, true);

    /*

    if(reader.is_open()){
        builder.set_points(reader.parse_data());
        builder.make_solid();
        builder.make_ais_shape();
        myOccView->getContext()->Display(builder.get_AIS_shape(), true);
    }
    else{
        qDebug() << "ERRRRROOOOORRRR AAAAAAAA";
    }
*/


    builder.set_points(*reader.parse_data());
    builder.make_solid();
    builder.make_ais_shape();
    myOccView->getContext()->Display(builder.get_AIS_shape(), false);

}

occQt::~occQt()
{

}

void occQt::createActions( void )
{
    // File
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // View
    connect(ui.actionZoom, SIGNAL(triggered()), myOccView, SLOT(zoom()));
    connect(ui.actionPan, SIGNAL(triggered()), myOccView, SLOT(pan()));
    connect(ui.actionRotate, SIGNAL(triggered()), myOccView, SLOT(rotate()));

    connect(ui.actionReset, SIGNAL(triggered()), myOccView, SLOT(reset()));
    connect(ui.actionFitAll, SIGNAL(triggered()), myOccView, SLOT(fitAll()));

    // Help
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void occQt::createMenus( void )
{
}

void occQt::createToolBars( void )
{
    QToolBar* aToolBar = addToolBar(tr("&Navigate"));
    aToolBar->addAction(ui.actionZoom);
    aToolBar->addAction(ui.actionPan);
    aToolBar->addAction(ui.actionRotate);

    aToolBar = addToolBar(tr("&View"));
    aToolBar->addAction(ui.actionReset);
    aToolBar->addAction(ui.actionFitAll);

    aToolBar = addToolBar(tr("Help"));
    aToolBar->addAction(ui.actionAbout);
}

void occQt::about()
{
    QMessageBox::about(this, tr("About occQt"),
        tr("<h2>occQt 2.0</h2>"
        "<p>Copyright &copy; 2014 eryar@163.com"
        "<p>occQt is a demo applicaton about Qt and OpenCASCADE."));
}



