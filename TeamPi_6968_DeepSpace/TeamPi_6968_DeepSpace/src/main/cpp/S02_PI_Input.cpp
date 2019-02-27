#include "S02_PI_Input.h"

S02_PI_Input::S02_PI_Input()
{
    this->driver = new PI_Driver();
    this->navigator =  new PI_Navigator(navigatorControllerID);
}
