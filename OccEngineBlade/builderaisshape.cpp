#include "builderaisshape.h"

builderAisShape::builderAisShape()
{
    // пока не знаю , добавим!
}

void builderAisShape::set_points(std::shared_ptr<std::deque<std::list<gp_Pnt>>> ptr)
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

bool builderAisShape::empty(){
    if(ptr_points_ == nullptr) return true;
    return false;
}

TopoDS_Face builderAisShape::primitiv_surface(std::list<gp_Pnt>& pnts){

    BRepBuilderAPI_MakeWire makerWire;

    for(auto it = pnts.begin(); it != pnts.end(); it++){
        gp_Pnt p1 = *it;
        it++;
        if (it ==  pnts.end()) break;
        gp_Pnt p2 = *it;
        makerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
        it--;
    }

    makerWire.Add(BRepBuilderAPI_MakeEdge(pnts.back(), pnts.front()).Edge());

    return BRepBuilderAPI_MakeFace(makerWire.Wire(), true).Face();
}

TopoDS_Solid builderAisShape::make_solid()
{
    TopoDS_Shell Shell_blade;

    TopoDS_Builder builder;

    builder.MakeSolid(TopoDS_blade_);
    builder.MakeShell(Shell_blade);

    // построение крышки лопатки
    builder.Add(Shell_blade, primitiv_surface(ptr_points_->front()));
    // построение дна лопатки
    builder.Add(Shell_blade, primitiv_surface(ptr_points_->back()));

    // таки пар deque.size() - 1 !!!

    for(int i = 0; i < ptr_points_->size() - 1; i++){
        std::list<gp_Pnt>& slice1 = ptr_points_->at(i);
        std::list<gp_Pnt>& slice2 = ptr_points_->at(i+1);

        auto it1 = slice1.begin();
        auto it2 = slice2.begin();

        for(int i = 0; i < slice1.size() - 1; i++){
            std::list<gp_Pnt> temp;

            for(int j = i; j > 0; j--){
                it1++;
                it2++;
            }

            temp.push_back(*it1); // it1
            temp.push_back(*(++it1)); // it1 + 1
            temp.push_back(*(++it2)); // it2 + 1
            temp.push_back(*(--it2)); // it2

            --it1; // <- it1 == it2 (по позиции)

            builder.Add(Shell_blade, primitiv_surface(temp));
            //temp.clear();
        }

        std::list<gp_Pnt> temp;

        temp.push_back(slice1.back());
        temp.push_back(slice1.front());
        temp.push_back(slice2.front());
        temp.push_back(slice2.back());

        builder.Add(Shell_blade, primitiv_surface(temp));
    }

    builder.Add(TopoDS_blade_, Shell_blade); // <- modificate Handle
    return TopoDS_blade_;
}

Handle(AIS_Shape) builderAisShape::make_ais_shape()
{
    AIS_blade_ = new AIS_Shape(TopoDS_blade_);
    return AIS_blade_;
}

