
#include <PI_Vector.h>

PI_Vector::PI_Vector(uint8_t info[5])
{
    uint8_t index = info[0];
    uint8_t this_x0 = info[1];
    uint8_t this_y0 = info[2];
    uint8_t this_x1 = info[3];
    uint8_t this_y1 = info[3];
}

PI_Vector::PI_Vector()
{
    uint8_t index = 0;
    uint8_t this_x0 = 0;
    uint8_t this_y0 = 0;
    uint8_t this_x1 = 0;
    uint8_t this_y1 = 0;
}