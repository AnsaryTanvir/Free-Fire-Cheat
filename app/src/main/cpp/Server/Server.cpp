#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <pthread.h>

#include "Substrate/CydiaSubstrate.h"
#include "KittyMemory/KittyMemory.h"
#include "KittyMemory/MemoryPatch.h"
#include "KittyMemory/KittyScanner.h"

#include "../Socket/SocketServer.h"

#include "../Unity/Unity.h"
#include "../Unity/Vector3.hpp"

#include "FeatureState.h"
#include "Offset.h"
#include "FunctionAndHook.h"
#include "../ClientServerCommon/ClientServerCommon.h"

#define LOG_TAG "Debug"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

using KittyMemory::ProcMap;

static void *UpdatedPlayer = NULL;
static void CreateDataList(Response& response);

/** --------------------------------------------------------------------------------------------- */
/** --------------- Started: Socket Server ------------- */
bool StartServer();
void *CreateServer(void *);
void DoTaskForRequest(Request& request, Response& response);

SocketServer server;

bool StartServer() {

    if (!server.Create()) {
        LOGD("Server: Failed to created server (-1) ");
        return false;
    }

    setsockopt(server.listenfd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const void *>(1), sizeof(int));
    if (!server.Bind()) {
        LOGD("Server: Failed to bind (-2) ");
        return false;
    }
    if (!server.Listen()) {
        LOGD("Server: Failed to listen request (-3) ");
        return false;
    }
    return true;
}

void *CreateServer(void *) {

    if (StartServer() ) {
        if ( server.Accept() ) {

            Request  request{};
            Response response{};

            while ( server.receive((void*)&request ) > 0) {

                /** Stopping the server on request **/
                if (request.FeatureNumber == FeatureMap.STOP_SERVER ){
                    response.Success = true;
                    server.send((void *) &response, sizeof(Response));
                    server.Close();
                    pthread_exit(NULL);
                }

                /** Else, handle request **/
                DoTaskForRequest(request, response);
                server.send((void*) &response, sizeof(response));
            }
        }else LOGD("Server: Failed to accept request");
    } else LOGD("Server: Failed to Initiate Server");

    return NULL;
}

void DoTaskForRequest(Request& request, Response& response){

    if ( request.FeatureNumber == FeatureMap.CHECK_SERVER ){
        response.Success = true;
        return;
    }

    if ( request.FeatureNumber == FeatureMap.AIMBOT ){
        FeatureState.AIMBOT = (bool) request.FeatureValue;
        LOGD("Payload: Aimbot %s", request.FeatureValue?"ON":"OFF" );
        response.Success = true;
        return;
    }


    if ( request.FeatureNumber == FeatureMap.AIM_FOV ){
        FeatureState.AIM_FOV   = (int) request.FeatureValue;
        LOGD("Payload: Aim Fov %d", request.FeatureValue );
        response.Success = true;
        return;
    }

    if ( request.FeatureNumber == FeatureMap.AIM_DISTANCE ){
        FeatureState.AIM_DISTANCE   = (int) request.FeatureValue;
        LOGD("Payload: Aim Distance %d", request.FeatureValue );
        response.Success = true;
        return;
    }

    if ( request.FeatureNumber == FeatureMap.ESP ){
        FeatureState.ESP    = (int) request.FeatureValue;
        if ( FeatureState.ESP ){
            CreateDataList(response);
            response.Success = true;
            return;
        }
        response.Success = false;
        return;
    }


    if ( request.FeatureNumber == FeatureMap.JUMP_HEIGHT ){
        FeatureState.JUMP_HEIGHT = (int) request.FeatureValue;
        LOGD("Payload: JUMP HEIGHT  %d", request.FeatureValue );
        response.Success = true;
        return;
    }

    if ( request.FeatureNumber == FeatureMap.NO_RECOIL ){
        FeatureState.NO_RECOIL = (int) request.FeatureValue;
        LOGD("Payload: NO RECOIL %s", request.FeatureValue?"ON":"OFF" );
        response.Success = true;
        return;
    }

    if ( request.FeatureNumber == FeatureMap.SPEED_TIME ){

        int speed = request.FeatureValue;
        LOGD("Payload: SPEED TIME  %d", speed);

        const char* CurrentTimerSpeed = GetTimerSpeedHex(speed);
        if (CurrentTimerSpeed == NULL )
            Patches.TimerSpeed = MemoryPatch::createWithHex("libunity.so", 0x38316C, TimerSpeedDefault );
        else
            Patches.TimerSpeed = MemoryPatch::createWithHex("libunity.so", 0x38316C, CurrentTimerSpeed );

        Patches.TimerSpeed.Modify();
        free((void *) CurrentTimerSpeed);
        response.Success = true;
        return;
    }


}

/** --------------- Finished: Socket Server -------------- */
/** --------------------------------------------------------------------------------------------- */


/** --------------------------------------------------------------------------------------------- */
/* --------------- Function(s) Definition --------- */

/* This is an static method, no need to pass any object */
static void *Current_Match() {
    void* (*_Current_Match)(void*) = (void *(*)(void *))getRealOffset(Offset.Current_Match);
    return _Current_Match(NULL);
}

static void *Component_GetTransform(void *player) {
    void *(*_Component_GetTransform)(void*) = (void *(*)(void *))getRealOffset(Offset.Component_GetTransform);
    return _Component_GetTransform(player);
}

static bool get_isLocalTeam(void *player) {
    bool (*_get_isLocalTeam)(void *) = (bool (*)(void *))getRealOffset(Offset.get_isLocalTeam);
    return _get_isLocalTeam(player);
}

static bool get_isAlive(void *player) {
    bool (*_get_isAlive)(void *players) = (bool (*)(void *))getRealOffset(Offset.IsCameraTrackableEntityAlive);
    return _get_isAlive(player);
}

static bool AttackableEntity_get_IsDead(void *player) {
    bool (*_AttackableEntity_GetIsDead)(void*) = (bool (*)(void *))getRealOffset(Offset.AttackableEntity_get_IsDead);
    return _AttackableEntity_GetIsDead(player);
}

static bool get_IsDieing(void *player) {
    bool (*_get_IsDieing)(void*) = (bool (*)(void *))getRealOffset(Offset.get_IsDieing);
    return _get_IsDieing(player);
}

static bool get_IsReallyDead(void *player) {
    bool (*_get_IsReallyDead)(void *) = (bool (*)(void *))getRealOffset(Offset.get_IsReallyDead);
    return _get_IsReallyDead(player);
}

static Vector3 Transform_INTERNAL_GetPosition(void *player) {
    Vector3 out = Vector3::Zero();
    void (*_Transform_INTERNAL_GetPosition)(void*, Vector3* ) = (void (*)(void*, Vector3 *))getRealOffset(Offset.Transform_INTERNAL_GetPosition);
    _Transform_INTERNAL_GetPosition(player,&out);
    return out;
}

static Vector3 GetForward(void *trans) {
    Vector3 (*_GetForward)(void*) = (Vector3(*)(void *))getRealOffset(Offset.GetForward);
    return _GetForward(trans);
}

static bool get_IsFiring(void *player) {
    bool (*_get_IsFiring)(void *) = (bool (*)(void *))getRealOffset(Offset.IsFiring);
    return _get_IsFiring(player);
}

static void SetAimRotation(void *player, Quaternion look ) {
    void (*_SetAimRotation)(void*, Quaternion ) = (void (*)(void *, Quaternion))getRealOffset(Offset.SetAimRotation);
    _SetAimRotation(player, look);
}

static void *GetHeadTF(void *player) {
    void *(*_GetHeadTF)(void *) = (void *(*)(void *))getRealOffset(Offset.GetHeadTF);
    return _GetHeadTF(player);
}

static Vector3 GetHeadPosition(void* player) {
    return Transform_INTERNAL_GetPosition(Component_GetTransform(GetHeadTF(player)));
}

static void *GetLocalPlayer(void* match) {
    void *(*_GetLocalPlayer)(void *) = (void *(*)(void *))getRealOffset(Offset.GetLocalPlayer);
    return _GetLocalPlayer(match);
}

static Vector3 CameraMain(void* player){
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + Offset.MainCameraTransform));
}

static bool get_IsSighting(void *player) {
    bool (*_get_IsSighting)(void *players) = (bool (*)(void *))getRealOffset(Offset.get_IsSighting);
    return _get_IsSighting(player);
}

static void *Camera_main() {
    void *(*_Camera_main)(void *) = (void *(*)(void *))getRealOffset(Offset.Camera_main);
    return _Camera_main(nullptr);
}

static int get_MaxHP(void* enemy) {
    int (*_get_MaxHP)(void* player) = (int(*)(void *))getRealOffset(Offset.get_MaxHP);
    return _get_MaxHP(enemy);
}

static Vector3 WorldToScreenPoint(void *WorldCam, Vector3 WorldPos) {
    Vector3 (*_WorldToScreenScene)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getRealOffset( Offset.WorldToScreenPoint);
    return _WorldToScreenScene(WorldCam,WorldPos);
}

void   CreateDataList(Response& response) {

    response.PlayerCount = 0;

    if ( UpdatedPlayer != NULL ) {

        void *CurrentMatch = Current_Match();
        void* LocalPlayer  = GetLocalPlayer(CurrentMatch);

        if ( CurrentMatch != NULL && LocalPlayer !=  NULL ) {

            monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)((long)CurrentMatch + Offset.Dictionary);
            void *Camera = Camera_main();

            if ( players != NULL && Camera != NULL ) {
                //for(int i = 0; i < players->getNumValues(); i++ )
                for(int i = 0; i < players->getNumValues(); i++ ) {

                    void*       closestEnemy = players->getValues()[i];
                    PlayerData* playerData   = &response.Players[response.PlayerCount];
                   if ( closestEnemy != LocalPlayer && closestEnemy != NULL && !get_isLocalTeam(closestEnemy) ){

                        Vector3 HeadLocation = WorldToScreenPoint(Camera, GetHeadPosition(closestEnemy));
                        if ( HeadLocation.Z < -0 ) continue;

                        playerData->Distance      = Vector3::Distance(GetHeadPosition(LocalPlayer), GetHeadPosition(closestEnemy) );
                        playerData->HeadLocation  = HeadLocation;
                        playerData->IsDieing      = get_IsDieing(closestEnemy);
                        response.PlayerCount++;
                        if ( response.PlayerCount == MaxPlayerCount ) continue;
                    }
                }
            }
        }
    }
}

void   *GetClosestEnemy(void *match) {

    if( !match ) return NULL;

    float maxAngle          = FeatureState.AIM_FOV;
    float shortestDistance  = 9999.0f;

    void* closestEnemy      = NULL;
    void* LocalPlayer       = GetLocalPlayer(match);

    if( LocalPlayer != NULL ) {

        monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)( (long)match + Offset.Dictionary);
        for ( int i = 0; i < players->getNumValues(); i++ ) {

            void* Player = players->getValues()[i];
            if (  Player != NULL && !get_isLocalTeam(Player) && !get_IsDieing(Player) && get_MaxHP(Player) ) {

                Vector3 PlayerPos       = GetHeadPosition(Player);
                Vector3 LocalPlayerPos  = GetHeadPosition(LocalPlayer);
                Vector3 targetDir       = Vector3::Normalized(PlayerPos - LocalPlayerPos);


                float angle  = Vector3::Angle( targetDir, GetForward(Component_GetTransform(Camera_main())) ) * 100.0;
                if (  angle <= maxAngle) {
                    if( angle < shortestDistance ) {
                        /* Update shortest Distance */
                        shortestDistance    = angle;
                        closestEnemy        = Player;
                    }
                }
            }
        }
    }
    return closestEnemy;
}

/*                          Function(s) Definition ---------------------------------------------  */
/** --------------------------------------------------------------------------------------------- */



/** --------------------------------------------------------------------------------------------- */
/*  ------------- Function Hooking                                                             */

float (*oldMaxJumpHeight)(void* player);
float MaxJumpHeight(void* player) {
    if ( FeatureState.JUMP_HEIGHT ){
        return oldMaxJumpHeight(player) + (float) FeatureState.JUMP_HEIGHT/4.0f;
    }
    return oldMaxJumpHeight(player);
}

void (*oldLateUpdate)(void* player);
void LateUpdate(void* player){

    if ( player != NULL && FeatureState.AIMBOT  ) {

        void* CurrentMatch  = Current_Match();
        void* ClosestEnemy  = GetClosestEnemy(CurrentMatch);
        void* LocalPlayer   = GetLocalPlayer(CurrentMatch);

        if ( CurrentMatch != NULL && ClosestEnemy != NULL && LocalPlayer != NULL ) {

            Vector3     PlayerLocation  = CameraMain(LocalPlayer);
            Vector3     EnemyLocation   = GetHeadPosition(ClosestEnemy);
            Quaternion  PlayerLook      = GetRotationToLocation(EnemyLocation, 0.1f, PlayerLocation);

            bool    IsScopeOn   = get_IsSighting(LocalPlayer);
            bool    IsFiring    = get_IsFiring(LocalPlayer);

            bool    alive       = get_isAlive(player);
            bool    sameTeam    = get_isLocalTeam(player);
            bool    isDead      = AttackableEntity_get_IsDead(player);
            bool    dieing      = get_IsDieing(player);
            bool    reallyDead  = get_IsReallyDead(player);
            float   distance    = Vector3::Distance(PlayerLocation, EnemyLocation);

            if ( alive && !sameTeam && !isDead && !dieing && !reallyDead ){
                if (  (FeatureState.AIMBOT_FIRE && IsFiring) || (FeatureState.AIMBOT_SCOPE && IsScopeOn) ) {
                    if ( distance < FeatureState.AIM_DISTANCE ){
                        SetAimRotation( LocalPlayer, PlayerLook );
                    }
                }
            }
        }

    }

    UpdatedPlayer = player;
    oldLateUpdate(player);
}

//void(*LogsFreeFire)(void* _this);
//void _LogsFreeFire(void* _this){
//    if (LogsFreeFire != NULL)   return;
//    return LogsFreeFire(_this);
//}
//
//void(*Antiblacklist)(void* _this);
//void _Antiblacklist(void* _this){
//    if (Antiblacklist != NULL)  return;
//    return Antiblacklist(_this);
//}
//
//void(*CSRank)(void* _this);
//void _CSRank(void* _this){
//    if (CSRank != NULL) return;
//    return CSRank(_this);
//}


void* hackThread(void* ){

    sleep(1);
    while ( libBase == 0 ) libBase = getLibraryBase(libName);
    LOGD("Base of libil2cpp.so : %p ", (void*) libBase );

    /** Hooking Goes Here **/
    {
        MSHookFunction( (void *) getRealOffset(Offset.Update                ),(void *) LateUpdate          , (void **) &oldLateUpdate         );
        MSHookFunction( (void *) getRealOffset(Offset.MaxJumpHeight         ),(void *) MaxJumpHeight       , (void **) &oldMaxJumpHeight      );
    }

    {
        //        scan for bytes with mask x and ?
        //        uintptr_t found_at = KittyScanner::find_from_lib("libil2cpp.so", "\x30\x48\x2D\xE9\x08\xB0\x8D\xE2\x02\x8B\x2D\xED\x00\x40\xA0\xE1", "xxxxxxxxxxxxxxxx");
        //        LOGD("scanner found bytes at: %p", (void*)found_at);

        /** Fast Weapon Switch **/
        //MemoryPatch::createWithHex("libil2cpp.so", Offset.get_InSwapWeaponCD, "00 00 A0 E3 1E FF 2F E1", 4).Modify();
        /** No Recoil **/
        //MemoryPatch::createWithHex("libil2cpp.so", Offset.GetScatterRate    , "00 00 A0 E3 1E FF 2F E1", 4).Modify();

    }

    /* Anti BlackList */
    {

//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.HBPBMIOJGFA                       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.CCNEAFOPMIH                       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.AOCFOHFIAAM                       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LGINFBPMLAI                       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LJGJMOPAEFB                       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.init                              , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SetUserInfo                       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.IsPackageInstalled                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.IsInstanceOf                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.DetectAndroidApplications         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendCachedLogs                    , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendLogLeaveGame                  , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogAndroidApplicationDetection    , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.InitCacheLogSend                  , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogEnterGame                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.InitLeaveGameLog                  , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogIOSIDFA                        , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.CacheBackMall                     , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogClickGetAvatarBtn              , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.OnApplicationPause                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.OnApplicationQuit                 , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogLeaveWaitingIslandBattleStarte , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.InitLogLeaveWaitingIsland         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendCacheEven                     , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//
//
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendLogLeaveWaitingIsland         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogLeaveWaitingIslandPing         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogClientPushSetting              , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogClientSettingChange            , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.BlacklistInfoRes                  , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.BlacklistReq                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.BlacklistRes                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.BlacklistOpType                   , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.BlacklistOpReq                    , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendEventLog                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendGameLagLog                    , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendGameMemoryLog                 , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogGameMemory                     , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendNetworkEventLog               , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.SendLogObserver                   , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogScanIAPInventoryResult         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.LogReportCheatInHistory           , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.set_ban_type                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.get_ban_type                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.set_match_ban_info                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.get_match_ban_info                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.set_ban_expire_time               , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.get_ban_expire_time               , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//        /* Added Later */
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.get_BlackListAccountInfo          , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.StartLogGameLag                   , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.EventLogPageDetentionTimeItem     , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.EventTypePopupWindowViewTime      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.ProcessRankingItem                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.FindRankingItemDataByID           , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.CheckIsReachRankItemUseLevel      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.UIModelRankingItem                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.RankingItemRank                   , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        /** MSHookFunction((void *) getRealOffset(Bypass.LogReportCheat),(void *) _LogsFreeFire,(void **)&LogsFreeFire ); */
//        /** MemoryPatch::createWithHex("libil2cpp.so", Bypass.LoginInfo   , "00 00 A0 E3 1E FF 2F E1", 4).Modify(); */
//
//
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKDelReportData                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKDelReportData3               , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKForExport                    , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKFree                         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKGetReportData                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKGetReportData2               , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKGetReportData3               , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKInit                         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKIoctl                        , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKIoctlOld                     , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKOnPause                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKOnRecvData                   , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKOnRecvSignature              , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKOnResume                     , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKRegistInfoListener           , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKSetUserInfo                  , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.AnoSDKSetUserInfoWithLicense       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanogs.so", AnoSDK.JNI_OnLoad                         , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//        MemoryPatch::createWithHex("libanort.so", Anort.JNI_OnLoad                          , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libanort.so", Anort.unwind_xx_info_query                , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//
//        /** Added Later **/
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.match_ban_expire_time             , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.match_create_time                 , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.report_time                       , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.HackMatchPoolCdtDesc              , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.AntiHackProtectSettingDesc        , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.gs_test_hack                      , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.HackerPoolCdt                     , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.hackers_pool_effect_mode          , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.get_unban_time                    , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.set_unban_time                    , "000 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.get_hacker_cdt_id                 , "00 00 A0 E3 1E FF 2F E1", 4).Modify();
//        MemoryPatch::createWithHex("libil2cpp.so", Bypass.set_hacker_cdt_id                 , "00 00 A0 E3 1E FF 2F E1", 4).Modify();

    }

    /** Bypass **/
    {
//        MSHookFunction((void *) getRealOffset(Bypass.HBPBMIOJGFA),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.CCNEAFOPMIH),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.AOCFOHFIAAM),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LGINFBPMLAI),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LJGJMOPAEFB),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.init),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.SetUserInfo),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.IsPackageInstalled),(void *) _LogsFreeFire,(void **)&LogsFreeFire );

    }

    /** Logs **/
    {
//        MSHookFunction((void *) getRealOffset(Bypass.IsInstanceOf),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.DetectAndroidApplications),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.SendCachedLogs),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.SendLogLeaveGame),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogReportCheat),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogAndroidApplicationDetection),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.InitCacheLogSend),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogEnterGame),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.InitLeaveGameLog),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogIOSIDFA),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.CacheBackMall),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogClickGetAvatarBtn),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.OnApplicationPause),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.OnApplicationQuit),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogLeaveWaitingIslandBattleStarte),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.InitLogLeaveWaitingIsland),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.SendLogLeaveWaitingIsland),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogLeaveWaitingIslandPing),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogClientPushSetting),(void *) _LogsFreeFire,(void **)&LogsFreeFire );
//        MSHookFunction((void *) getRealOffset(Bypass.LogClientSettingChange),(void *) _LogsFreeFire,(void **)&LogsFreeFire );

    }

    /** Anti BlackList **/
    {

//        MSHookFunction((void *) getRealOffset(Bypass.BlacklistInfoRes), (void *) _Antiblacklist, (void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.BlacklistReq), (void *) _Antiblacklist, (void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.BlacklistRes), (void *) _Antiblacklist, (void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.BlacklistOpType),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.BlacklistOpReq),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.BlacklistOpReq),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.SendEventLog),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.SendGameLagLog),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.SendGameMemoryLog),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.LogGameMemory),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.SendNetworkEventLog),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.SendLogObserver),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.LogScanIAPInventoryResult),(void *) _Antiblacklist,(void **)&Antiblacklist );
//        MSHookFunction((void *) getRealOffset(Bypass.LogReportCheatInHistory),(void *) _Antiblacklist,(void **)&Antiblacklist );

    }


    return  NULL;
}

/*                          Function Hooking ---------------------------------------------  */
/** --------------------------------------------------------------------------------------------- */


__attribute__((constructor))
int main(){
    LOGD("Payload: I am loaded in the address space");

    pthread_t ptid;
    pthread_create(&ptid, NULL, CreateServer, NULL);

    pthread_t ptid2;
    pthread_create(&ptid2, NULL, hackThread, NULL);


}







/*

if ( request.FeatureNumber == FeatureMap.DYNAMIC_SPEED ){
    FeatureState.DYNAMIC_SPEED = (int) request.FeatureValue;
    LOGD("Payload: Dynamic Speed %s", request.FeatureValue?"ON":"OFF" );
    response.Success = true;
    return;
}


pthread_t ptid3;
pthread_create(&ptid3, NULL, DynamicSpeed, NULL);


void SpeedON(){
    Patches.TimerSpeed = MemoryPatch::createWithHex("libunity.so", 0x38316C, "1E 10 2E 3E" );
    Patches.TimerSpeed.Modify();
}
void SpeedOFF(){
    Patches.TimerSpeed = MemoryPatch::createWithHex("libunity.so", 0x38316C, TimerSpeedDefault );
    Patches.TimerSpeed.Modify();
}

void* DynamicSpeed(void*){

    while(1){
        if ( FeatureState.DYNAMIC_SPEED ){
            SpeedON();
            usleep(500000);
            SpeedOFF();
            usleep(500000);
        }
    }

    return NULL;
}


 */



















//
//void AimBot(void *player, void *enemy) {
//
////    bool    visible         = IsVisible(enemy);
//    bool    sameTeam        = get_isLocalTeam(enemy);
//    int     position        = GetPhysXPose(enemy);
//    void*   Main_Camera     = *(void**)((uintptr_t)player + Offset.MainCameraTransform) ;
//
//    if (  !sameTeam && position != 8 && Main_Camera != NULL  ){
//
//        Vector3 PlayerLocation  = Transform_INTERNAL_GetPosition(Main_Camera);
//        Vector3 EnemyLocation   = Transform_INTERNAL_GetPosition(GetHeadTF(enemy));
//
//        float distance          = Vector3::Distance(PlayerLocation, EnemyLocation);
//        Quaternion PlayerLook   = GetRotationToLocation(EnemyLocation, 0.1f, PlayerLocation);
//
//        Vector3 forward         = GetForward(Main_Camera);
//        Vector3 normalized      = Vector3::Normalized(EnemyLocation - PlayerLocation);
//        float   PlayerDot       = Vector3::Dot(forward, normalized);
//
//        int     givenFOV        = FeatureState.AIM_FOV;  //Absolute Max 360 degrees
//        float   CalculatedFOV   = 1.0f - ( 0.0027f * (float)givenFOV );
//        float   MaxDistance     = FeatureState.AIM_DISTANCE; //Absolute Max 180 meters
//
//        if( (PlayerDot > CalculatedFOV ) && (distance < MaxDistance) ){
//            if ( get_IsFiring(player) ){
//                SetAimRotation( player, PlayerLook );
//            }
//        }
//
//    }
//
//}


//void (*oldLateUpdate)(void* player);
//void LateUpdate(void* player){
//
//
//    if ( player != NULL && FeatureState.AIMBOT_FIRE ) {
//
//        void *local_player = Current_Local_Player();
//        if ( local_player == NULL )
//            local_player = GetLocalPlayerOrObServer();
//
//        if ( local_player != NULL ){
//
//            void *current_match = Current_Match();
//            if ( current_match != NULL ) {
//
//                void *fakeCamPlayer = get_MyFollowCamera(local_player);
//                void *fakeCamEnemy  = get_MyFollowCamera(player);
//
//                if ( fakeCamPlayer != NULL && fakeCamEnemy != NULL ){
//
//                    void *fakeCamPlayerTF = Component_GetTransform(fakeCamPlayer);
//                    void *fakeCamEnemyTF  = Component_GetTransform(player);
//
//                    if ( fakeCamPlayerTF != NULL && fakeCamEnemyTF != NULL ){
//
//                        Vector3 fakeCamPlayerPos    = Transform_INTERNAL_GetPosition(fakeCamPlayerTF);
//                        Vector3 fakeCamEnemyPos     = Transform_INTERNAL_GetPosition(fakeCamEnemyTF);
//                        float   distance            = Vector3::Distance(fakeCamPlayerPos, fakeCamEnemyPos);
//
//                        if ( player != local_player){
//
//                            if ( distance > 1.6f ) {
//
//                                bool    alive       = get_isAlive(player);
//                                bool    sameTeam    = get_isLocalTeam(player);
//                                int     position    = GetPhysXPose(player);
//                                bool    isDead      = AttackableEntity_get_IsDead(player);
//                                bool    dieing      = get_IsDieing(player);
//                                bool    reallyDead  = get_IsReallyDead(player);
//
//                                if ( alive && !sameTeam && position != 8 && !isDead && !dieing && !reallyDead ){
//                                    AimBot(local_player, player);
//                                    LOGD("Payload: Distance %0.2f ", distance);
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//
//    }
//
//    oldLateUpdate(player);
//}

