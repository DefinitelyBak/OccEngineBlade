
#ifndef BUILDERAISSHAPE_H
#define BUILDERAISSHAPE_H

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

#include <TopoDS_Builder.hxx>

#include <BRepBuilderAPI_MakeSolid.hxx>


#include <AIS_Shape.hxx>


// данный класс должен получать множество точек из jsonReader и
// формировать AIS_Shape для viever

// класс принимает
class builderAisShape
{
public:
    builderAisShape();

    void set_points(std::shared_ptr<std::deque<std::list<gp_Pnt>>> ptr);

    TopoDS_Solid get_TopoDS_solid() const;
    Handle(AIS_Shape) get_AIS_shape() const;

    bool empty();
    TopoDS_Solid make_solid();
    Handle(AIS_Shape) make_ais_shape();
private:
    TopoDS_Face primitiv_surface(std::list<gp_Pnt>& pnts);

public:

private:
    std::shared_ptr<std::deque<std::list<gp_Pnt>>> ptr_points_;

    TopoDS_Solid TopoDS_blade_;
    Handle(AIS_Shape) AIS_blade_;
};

#endif // BUILDERAISSHAPE_H
