#ifndef FEATURESTATE_H
#define FEATURESTATE_H

typedef struct{

    /*** This variables will hold the state/value of hooks / patches ****/
    bool AIMBOT         = false;
    bool AIMBOT_FIRE    = true;
    bool AIMBOT_SCOPE   = true;
    int  AIM_FOV        = 360;
    int  AIM_DISTANCE   = 180;
    bool ESP            = false;
    int  JUMP_HEIGHT    = false;
    int  NO_RECOIL      = false;
    int  DYNAMIC_SPEED  = false;

}FeatureStateStruct;
FeatureStateStruct FeatureState;

#endif
