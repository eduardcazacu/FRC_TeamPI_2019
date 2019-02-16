#include "M01_PI_Auto.h"

M01_PI_Auto::M01_PI_Auto(S06_PI_Grabber *grabber)
{
    //grabbing:
    this->grabber = grabber;
    grabState = GrabState::grab_idle;
}

void M01_PI_Auto::functions()
{
    grabHatch();
    placeHatch();
}

void M01_PI_Auto::reset()
{
    grabHatchReset();
    placeHatchReset();
    on=false;
}

void M01_PI_Auto::grabHatchEnable()
{
    //only work when supposed to.
    if (grabState == GrabState::grab_idle && placeState == PlaceState::place_idle)
    {
        grabState = GrabState::grab_extend; //progress to the next state;
    }
}

void M01_PI_Auto::placeHatchEnable()
{
    //only work when it is supposed to
    if (placeState == PlaceState::place_idle && grabState == GrabState::grab_idle)
    {
        placeState = PlaceState::place_extend; //progress to the next state;
    }
}

void M01_PI_Auto::grabHatchReset()
{
    //TODO: handle all the resetting stuff:

    grabState = GrabState::grab_idle;
}

void M01_PI_Auto::placeHatchReset()
{
    //TODO: handle all the restting stuff.
    placeState = PlaceState::place_idle;
}

bool M01_PI_Auto::grabHatch(bool *error)
{
    //all good:
    *error = false;
    switch (grabState)
    {
    case GrabState::grab_idle:
        //wait here for grab state to be changed by grabHatchEnable
        break;

    case GrabState::grab_extend:
        //notify that auto is happening:
        on = true;
        //extending the arm:
        grabber->extendGripper();
        //check if fully extended.
        if (grabber->getArm() == 1)
        {
            grabState = GrabState::grab_grab;
            //setup the grab ratio for next step:
            grabRatio = START_GRAB_RATIO;
        }

        break;
    case GrabState::grab_grab:
        //notify that auto is happening:
        on = true;
        //grab the thing:
        //gradually increase the grab rate until the sensor has detected the hatch, or reached the maximum
        grabber->grip(grabRatio);
        //increment:
        grabRatio += GRAB_RATIO_INCREMENT;
        //check if grab done:
        if (grabber->hatchSecured() || grabRatio >= GRAB_RATIO_LIMIT)
        {
            //done:
            grabState = GrabState::grab_secured;
        }
        break;
    case GrabState::grab_secured:
        //notify that auto is happening:
        on = true;
        //step 5 - ??????
        grabState = GrabState::grab_retract;
        break;
    case GrabState::grab_retract:
        //notify that auto is happening:
        on = true;
        //step 6 - profit
        grabber->retractGripper();

        if (grabber->getArm() == -1)
        {
            //done retracting. go next
            grabState = GrabState::grab_done;
        }
        break;
    case GrabState::grab_done:
        grabState = GrabState::grab_idle;
        on = false;
        return true;
        break;
    default:
        grabState = GrabState::grab_idle;
        *error = true; //shit hit the fan
                       //notify that auto is happening:
        on = false;
    }

    return false;
}
bool M01_PI_Auto::grabHatch()
{
    bool *error = new bool; //temp var for error.

    if (grabHatch(error))
    {
        //done, clear memory
        delete (error);
        return true;
    }
    return false;
}

bool M01_PI_Auto::placeHatch(bool *error)
{
    //all good:
    *error = false;
    switch (placeState)
    {
    case PlaceState::place_idle:
        //wait here until activated.
        break;

    case PlaceState::place_extend:
        //notify that auto is happening:
        on = true;
        //extending the arm:
        grabber->extendGripper();
        //check if fully extended.
        if (grabber->getArm() == 1)
        {
            placeState = PlaceState::place_place;
        }

        break;
    case PlaceState::place_place:
        //notify that auto is happening:
        on = true;
        //place the thing:
        grabber->grip(0);
        //check if grab done:
        if (grabber->getGripper() == -1)
        {
            //done:
            placeState = PlaceState::place_cleared;
        }
        break;
    case PlaceState::place_cleared:
        //notify that auto is happening:
        on = true;
        //step 5 - ??????
        placeState = PlaceState::place_retract;
        break;
    case PlaceState::place_retract:
        //notify that auto is happening:
        on = true;
        //step 6 - profit
        grabber->retractGripper();

        if (grabber->getArm() == -1)
        {
            //done retracting. go next
            placeState = PlaceState::place_done;
        }
        break;
    case PlaceState::place_done:
        //notify that auto is happening:
        on = false;
        placeState = PlaceState::place_idle;
        return true;
        break;
    default:
        //notify that auto is happening:
        on = false;
        placeState = PlaceState::place_idle;
        *error = true; //shit hit the fan
    }

    return false;
}
bool M01_PI_Auto::placeHatch()
{
    bool *error = new bool; //temp var for error.

    if (placeHatch(error))
    {
        //done, clear memory
        delete (error);
        return true;
    }
    return false;
}