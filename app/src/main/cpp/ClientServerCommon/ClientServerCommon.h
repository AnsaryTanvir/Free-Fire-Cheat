#ifndef CLIENTSERVERCOMMON_H
#define CLIENTSERVERCOMMON_H

#include "../Unity/Vector3.hpp"

#define MaxPlayerCount 54

typedef struct {
    /** Associated With Client/Server Core Part **/
    const int CHECK_SERVER    = -1;
    const int STOP_SERVER     = -2;

    /*** This must match with FloatingViewService.java ****/
    const int  AIMBOT           =  1;
    const int  AIM_FOV          =  2;
    const int  AIM_DISTANCE     =  3;
    const int  ESP              =  4;
    const int  JUMP_HEIGHT      =  5;
    const int  NO_RECOIL        =  6;
    const int  SPEED_TIME       =  7;
    const int  DYNAMIC_SPEED    =  8;

}FeatureMapStruct;
FeatureMapStruct FeatureMap;

struct Request {
    int FeatureNumber;
    int FeatureValue ;
};

struct PlayerData {
    float   Distance;
    bool    IsDieing;
    Vector3 HeadLocation;
};

struct Response {
    bool        Success;
    int         PlayerCount;
    PlayerData  Players[MaxPlayerCount];
};


#endif
