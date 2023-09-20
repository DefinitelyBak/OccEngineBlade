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

    //std::deque<std::list<gp_Pnt>> ptr = reader.parse_data()->at("le");

    //TopoDS_Shell A;
    //TopoDS_Face A2 = builder.primitiv_surface_Bezier(temp2);

    //TopoDS_Shell shell;
    //TopoDS_Builder BUILD;
    //UILD.MakeShell(A);

    //auto it1 = ptr[0].begin();
    //auto it2 = ptr[1].begin();



/*
    BRepOffsetAPI_Sewing sew(0.9);
    //sew.Add(f1);sew.Perform();TopoDS_Shape sewedShape = sew.SewedShape();

    while( (++it1) != ptr[0].end()){
        it1--;

        std::list<gp_Pnt> list;

        list.push_back(*it1);
        it1++;
        list.push_back(*it1);
        it2++;
        list.push_back(*it2);
        it2--;
        list.push_back(*it2);

        it2++;

        sew.Add(builder.primitiv_surface_Bezier(list));
    }

    it1 = ptr[1].begin();
    it2 = ptr[2].begin();
    while( (++it1) != ptr[1].end()){
        it1--;

        std::list<gp_Pnt> list;

        list.push_back(*it1);
        it1++;
        list.push_back(*it1);
        it2++;
        list.push_back(*it2);
        it2--;
        list.push_back(*it2);

        it2++;

        sew.Add(builder.primitiv_surface_Bezier(list));
    }

    sew.Perform();
*/

    //Handle(AIS_Shape) AIS = new AIS_Shape(builder.make_shell_edge(ptr));
   // myOccView->getContext()->Display(AIS, false);

    builder.set_points(*reader.parse_data());
    builder.make_solid();
    builder.make_ais_shape();
    myOccView->getContext()->Display(builder.get_AIS_shape(), true);

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



