#include "M01_PI_Auto.h"

M01_PI_Auto::M01_PI_Auto(S06_PI_Grabber *grabber, S05_PI_Lift *lift, S04_PI_Drivetrain *drivetrain, S09_PI_Aim *aiming, C04_PI_Pixy *pixy)
{
    //grabbing:
    this->grabber = grabber;
    grabState = GrabState::grab_idle;

    //lift:
    liftResetDone = false;
    _lift = lift;
    on = false;

    _drivetrain = drivetrain;
    _rotationDone = true;

    _pixy = pixy;
    _aiming = aiming;
    autoAimDone = true;

    ultrasoundDriveDone = true;

    timeOutTmr = new frc::Timer();
    timeOutTmr->Start();
}

void M01_PI_Auto::functions()
{
    //reset the lift at he beggining of the game:
    /*if (!liftResetDone)
    {
        if(_lift->reset()){
            liftResetDone = true;
        }
    }
    */

    //all the methods called periodically should return true when they are done or not doing anything
    //and false when they are doing something.

    if (grabHatch() && placeHatch() && rotateDegrees() && autoAim() && ultrasoundDrive())
    {
        //if all functions are done:
        on = false;
    }
    else
    {
        //if at least one function is on:
        on = true;
    }
}

void M01_PI_Auto::reset()
{
    grabHatchReset();
    placeHatchReset();
    _rotationDone = true;
    on = false;
}

void M01_PI_Auto::grabHatchEnable()
{
    //only work when supposed to.
    if (grabState == GrabState::grab_idle && placeState == PlaceState::place_idle)
    {
        grabState = GrabState::grab_extend; //progress to the next state;

        //start the watchdog timer:
        timeOutTmr->Reset();
    }
}

void M01_PI_Auto::placeHatchEnable()
{
    //only work when it is supposed to
    if (placeState == PlaceState::place_idle && grabState == GrabState::grab_idle)
    {
        placeState = PlaceState::place_extend; //progress to the next state;

        //start the watchdog timer:
        timeOutTmr->Reset();
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
        //extending the arm:
        grabber->extendGripper();
        //check if fully extended.
        if (grabber->getArm() == 1 || timeOutTmr->Get() > GRABBER_TIMEOUT)
        {
            grabState = GrabState::grab_grab;
            //setup the grab ratio for next step:
            grabRatio = START_GRAB_RATIO;

            timeOutTmr->Reset();
        }
        return false;
        break;
    case GrabState::grab_grab:
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
            timeOutTmr->Reset();
        }
        return false;
        break;
    case GrabState::grab_secured:
        //step 5 - ??????
        grabState = GrabState::grab_retract;
        timeOutTmr->Reset();
        return false;
        break;
    case GrabState::grab_retract:
        //step 6 - profit
        grabber->retractGripper();

        if (grabber->getArm() == -1 || timeOutTmr->Get() > GRABBER_TIMEOUT)
        {
            //done retracting. go next
            grabState = GrabState::grab_done;
            timeOutTmr->Reset();
        }
        return false;
        break;
    case GrabState::grab_done:
        grabState = GrabState::grab_idle;
        break;
    default:
        grabState = GrabState::grab_idle;
        *error = true; //shit hit the fan
    }

    return true;
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
        if (grabber->getArm() == 1 ||timeOutTmr->Get() > GRABBER_TIMEOUT)
        {
            placeState = PlaceState::place_place;
            timeOutTmr->Reset();
        }
        return false;
        break;
    case PlaceState::place_place:
        //notify that auto is happening:
        on = true;
        //place the thing:
        grabber->grip(0);
        //check if grab done:
        if (grabber->getGripper() == -1 || timeOutTmr->Get() > GRABBER_TIMEOUT)
        {
            //done:
            placeState = PlaceState::place_cleared;
            timeOutTmr->Reset();
        }
        return false;
        break;
    case PlaceState::place_cleared:
        //notify that auto is happening:
        on = true;
        //step 5 - ??????
        placeState = PlaceState::place_retract;
        timeOutTmr->Reset();
        return false;
        break;
    case PlaceState::place_retract:
        //notify that auto is happening:
        on = true;
        //step 6 - profit
        grabber->retractGripper();

        if (grabber->getArm() == -1 || timeOutTmr->Get() > GRABBER_TIMEOUT)
        {
            //done retracting. go next
            placeState = PlaceState::place_done;
            timeOutTmr->Reset();
        }
        return false;
        break;
    case PlaceState::place_done:
        //notify that auto is happening:
        on = false;
        placeState = PlaceState::place_idle;
        break;
    default:
        //notify that auto is happening:
        on = false;
        placeState = PlaceState::place_idle;
        *error = true; //shit hit the fan
    }

    return true;
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

bool M01_PI_Auto::placeHatchOnLevelRoutine(int lvl)
{

    
}

void M01_PI_Auto::rotateDegreesEnable(double angle)
{
    _rotationDone = false;
    _rotationAngle = angle;
}

bool M01_PI_Auto::rotateDegrees()
{
    if (!_rotationDone)
    {
        if (_drivetrain->Rotate(_rotationAngle))
        {
            std::cout << "Rotation done \n";
            _rotationDone = true;

            return true;
        }

        return false;
    }
    return true;
}

void M01_PI_Auto::autoAimStart()
{
    if (_pixy->AimReady())
        autoAimDone = false;
    else
        std::cout << "Pixy can't detect a usable line \n";
}

bool M01_PI_Auto::autoAim()
{
    if (!autoAimDone)
    {
        /*
        if (_aiming->Aim(_pixy->LatestVector().Angle(), _pixy->LatestVector().NearestX(), _pixy->LatestVector().NearestY()))
        {
            //done
            autoAimDone = true;
            return true;
        }
        return false;
        */
       unit8_t info[2] = _pixy->GetBlocks();
       uint8_t x = info[0];
       uint8_t surface = info[1];
       if (_aiming->SimpleAim(x,5,surface,100,10))
        {
            //done
            autoAimDone = true;
            return true;
        }
        return false;
    }
    return true;
}

bool M01_PI_Auto::ultrasoundDrive()
{
    if (!ultrasoundDriveDone)
    {
        if (_drivetrain->driveToUltrasoundDistance(targetUltrasoundDist))
        {
            ultrasoundDriveDone = true;
            return true;
        }

        return false;
    }
    return true;
}

void M01_PI_Auto::ultrasoundDriveRocket()
{
    targetUltrasoundDist = distToRocket;
    ultrasoundDriveDone = false;
}
void M01_PI_Auto::ultrasoundDriveCargo()
{
    targetUltrasoundDist = distToCargo;
    ultrasoundDriveDone = false;
}