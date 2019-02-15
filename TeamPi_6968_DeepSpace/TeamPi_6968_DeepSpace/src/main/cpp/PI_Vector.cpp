
#include "PI_Vector.h"

PI_Vector::PI_Vector(uint8_t info[5])
{
    index = info[0];
    x0 = info[1];
    y0 = info[2];
    x1 = info[3];
    y1 = info[4];
}

/*PI_Vector::PI_Vector(uint8_t _index, uint8_t _x0, uint8_t _y0, uint8_t _x1, uint8_t _y1)
{
    index = _index;
    x0 = _x0;
    y0 = _y0;
    x1 = _x1;
    y1 = _y1;
}*/

double PI_Vector::IntersectY(PI_Vector vector2){
    if (Dir() == vector2.Dir())
    {
        //The lines are parralel
        return -1;
    }

    return (IntersectX(vector2)*Dir()+Height());
}

double PI_Vector::IntersectX(PI_Vector vector2)
{
    if (Dir() == vector2.Dir())
    {
        //The lines are parralel
        return -1;
    }

    return ((vector2.Height() - Height()) / (Dir() - vector2.Dir()));
}

double PI_Vector::Dir()
{
    double dy = y1 - y0;
    double dx = x1 - x0;
    return (dy / dx);
}

double PI_Vector::Height()
{
    return ((-Dir() * x0) / y0);
}

double PI_Vector::CenterX(){
    return ((x1-x0)/2);
}

double PI_Vector::CenterY(){
    return ((y1-y0)/2);
}

double PI_Vector::Angle(){
    return atan(Dir()); //only works between -PI/2 and PI/2
    //return atan2(y1-y0,x1-x0);
}

double PI_Vector::Length(){
    return sqrt(pow(x1-x0,2)+pow(y1-y0,2));
}

double PI_Vector::NearestY(){
    if(y0>y1)
    return y0;
    return y1;
}

void PI_Vector::Print(){

    std::cout<<"\n";
    std::cout<<"Vector:\n";
    std::cout<<"index: "<<(int)index<<"\n";
    std::cout<<"x0: "<<(int)x0<<"\n";
    std::cout<<"y0: "<<(int)y0<<"\n";
    std::cout<<"x1: "<<(int)x1<<"\n";
    std::cout<<"y1: "<<(int)y1<<"\n";
}