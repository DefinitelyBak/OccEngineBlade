#include "builderaisshape.h"

builderAisShape::builderAisShape()
{
    // пока не знаю , добавим!
}

void builderAisShape::set_points(std::shared_ptr<std::map<std::string, std::deque<std::list<gp_Pnt>>>> ptr)
{
    ptr_points_ = ptr;
}

 TopoDS_Solid builderAisShape::get_TopoDS_solid() const
{
    return TopoDS_blade_;
}

 Handle(AIS_Shape) builderAisShape::get_AIS_shape() const
{
    return AIS_blade_;
 }

bool builderAisShape::empty()
{
    return ptr_points_->empty();
}

bool builderAisShape::is_done()
{
    return status_;
}

TopoDS_Solid builderAisShape::make_solid()
{
    TopoDS_Builder builder;

    builder.MakeSolid(TopoDS_blade_);
    builder.Add(TopoDS_blade_, make_shell(ptr_points_->at("up").front()));
    builder.Add(TopoDS_blade_, make_shell(ptr_points_->at("dw").front()));
    builder.Add(TopoDS_blade_, make_shell_Bezier(ptr_points_->at("cx")));
    builder.Add(TopoDS_blade_, make_shell_Bezier(ptr_points_->at("cv")));
    builder.Add(TopoDS_blade_, make_shell_edge(ptr_points_->at("le")));
    builder.Add(TopoDS_blade_, make_shell_edge(ptr_points_->at("re")));

    return TopoDS_blade_;
}

TopoDS_Face builderAisShape::primitiv_surface(std::list<gp_Pnt>& pnts){
    BRepBuilderAPI_MakePolygon poly_maker;

    for(auto it = pnts.begin(); it != pnts.end(); it++) poly_maker.Add(*it);

    BRepBuilderAPI_MakeFace face_maker(poly_maker.Wire(), false);

    if (face_maker.IsDone()){
        status_ = true;
        return face_maker.Face();
    }

    return TopoDS_Face();
}

TopoDS_Face builderAisShape::primitiv_surface_Bezier(std::list<gp_Pnt>& pnts){
    auto it = pnts.begin();
    NCollection_Array1<gp_Pnt> A(1,2);
    A(1) = *it;
    it++;
    A(2) = *it;

    NCollection_Array1<gp_Pnt> B(1,2);
    B(1) = *it;
    it++;
    B(2) = *it;

    NCollection_Array1<gp_Pnt> C(1,2);
    C(1) = *it;
    it++;
    C(2) = *it;

    NCollection_Array1<gp_Pnt> D(1,2);

    D(1) = pnts.back();
    D(2) = pnts.front();

    Handle(Geom_BezierCurve) Ac1 = new Geom_BezierCurve(A);
    Handle(Geom_BezierCurve) Bc1 = new Geom_BezierCurve(B);
    Handle(Geom_BezierCurve) Cc1 = new Geom_BezierCurve(C);
    Handle(Geom_BezierCurve) Dc1 = new Geom_BezierCurve(D);

    GeomFill_BezierCurves bcFill;

    bcFill.Init(Ac1, Bc1, Cc1, Dc1, GeomFill_StretchStyle);
    BRepBuilderAPI_MakeFace face_maker(bcFill.Surface(), 1e-6);

    if (face_maker.IsDone()){
        status_ = true;
        return face_maker.Face();
    }

    return TopoDS_Face();

}
TopoDS_Shell builderAisShape::make_shell(std::list<gp_Pnt>& points_){

    TopoDS_Shell Shell_blade;
    TopoDS_Builder builder;

    builder.MakeShell(Shell_blade);
    builder.Add(Shell_blade, primitiv_surface(points_));

    if(!status_ || Shell_blade.IsNull()){
        status_ = false;
        return TopoDS_Shell();
    }

    return Shell_blade;
}

TopoDS_Shell builderAisShape::make_shell_Bezier(std::deque<std::list<gp_Pnt>>& points_)
{

    TopoDS_Shell shell_blade;
    TopoDS_Builder builder;

    builder.MakeShell(shell_blade);

    for(int i = 0; i < points_.size() - 1; i++){
        std::list<gp_Pnt>& slice1 = points_.at(i);
        std::list<gp_Pnt>& slice2 = points_.at(i + 1);

        auto it1 = slice1.begin();
        auto it2 = slice2.begin();

        bool status = true;
        for(int i = 0; i < slice1.size(); i++){
            std::list<gp_Pnt> temp;

            for(int j = i; j > 0; j--)
                if (it1++ == slice1.end() || it2++ == slice1.end()){
                    status = false;
                    break;
                }


            if(status) break;

            temp.push_back(*it1); // it1
            it1++; temp.push_back(*it1); // it1 + 1
            it2++; temp.push_back(*it2); // it2 + 1
            it2--; temp.push_back(*it2); // it2

            --it1; // <- it1 == it2 (по позиции)

            builder.Add(shell_blade, primitiv_surface_Bezier(temp));
            temp.clear();
        }

        std::list<gp_Pnt> temp;

        temp.push_back(slice1.back());
        temp.push_back(slice1.front());
        temp.push_back(slice2.front());
        temp.push_back(slice2.back());

        builder.Add(shell_blade, primitiv_surface_Bezier(temp));
    }

    if(!status_ || shell_blade.IsNull()){
        status_ = false;
        return TopoDS_Shell();
    }

    return shell_blade;
}

TopoDS_Shape builderAisShape::make_shell_edge(std::deque<std::list<gp_Pnt>>& points_){

    BRepOffsetAPI_Sewing sew(0.9);

    for (int i = 0; i < points_.size() - 1; i++){
        auto it1 = points_[i].begin();
        auto it2 = points_[i + 1].begin();

        while( (++it1) != points_[i].end()){
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

            sew.Add(primitiv_surface_Bezier(list));
        }
    }
    sew.Perform();

    TopoDS_Shape result = sew.SewedShape();

    if(!status_ || result.IsNull()){
        status_ = false;
        return TopoDS_Shape();
    }

    return result;
}

Handle(AIS_Shape) builderAisShape::make_ais_shape()
{
    AIS_blade_ = new AIS_Shape(TopoDS_blade_);
    return AIS_blade_;
}

bool builderAisShape::export_step(){
    STEPControl_Writer writer;

    writer.Transfer(TopoDS_blade_, STEPControl_ManifoldSolidBrep );

    return writer.Write("Output.STEP");
}
