
#ifndef BUILDERAISSHAPE_H
#define BUILDERAISSHAPE_H



#include <QDebug>

#include <memory>
#include <deque>
#include <list>

// Ниже include-ы относящиеся к поверхности
#include <Standard_Address.hxx>
#include <Standard_Std.hxx>
#include <Standard_Stream.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Macro.hxx>

#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>

#include <Geom_Plane.hxx>

#include <TopoDS_Wire.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Face.hxx>

#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

#include <TopoDS_Builder.hxx>

#include <BRepBuilderAPI_MakeSolid.hxx>

#include <BRepOffsetAPI_Sewing.hxx>


#include <AIS_Shape.hxx>


#include <gp_Pnt.hxx>
#include <NCollection_Array1.hxx>

#include <Geom_BezierSurface.hxx>
#include <Geom_BezierCurve.hxx>
#include <GeomFill_BezierCurves.hxx>

#include <STEPControl_Writer.hxx>


// данный класс должен получать множество точек из jsonReader и
// формировать AIS_Shape для viever

// класс принимает
class builderAisShape
{
public:
    builderAisShape();

    void set_points(std::map<std::string, std::deque<std::list<gp_Pnt>>>& ptr);


    TopoDS_Solid      get_TopoDS_solid() const;
    Handle(AIS_Shape) get_AIS_shape() const;


    bool empty();
    TopoDS_Solid      make_solid();
    Handle(AIS_Shape) make_ais_shape();


    bool export_step();
    //TopoDS_Face  primitiv_surface(std::list<gp_Pnt>& pnts);
    //TopoDS_Face  primitiv_surface_Bezier(std::list<gp_Pnt>& pnts);

private:
    TopoDS_Shell make_shell_Bezier(std::deque<std::list<gp_Pnt>>& points_);
    TopoDS_Shell make_shell(std::list<gp_Pnt>& points_);
    TopoDS_Face  primitiv_surface(std::list<gp_Pnt>& pnts);
    TopoDS_Face  primitiv_surface_Bezier(std::list<gp_Pnt>& pnts);

public:
    TopoDS_Shape make_shell_edge(std::deque<std::list<gp_Pnt>>& points_);
private:
    std::map<std::string, std::deque<std::list<gp_Pnt>>> points_;

    TopoDS_Solid TopoDS_blade_;
    Handle(AIS_Shape) AIS_blade_;
};

#endif // BUILDERAISSHAPE_H
