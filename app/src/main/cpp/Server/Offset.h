#ifndef OFFSET_H
#define OFFSET_H

/* D -> 1.93.1 32 Bit */
typedef unsigned long DWORD;
typedef struct {

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xC87AE8 Offset: 0xC87AE8 VA: 0xB409AAE8
    //  private void LateUpdate() { }
    uintptr_t Update    =   0xC87AE8;

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xCA8258 Offset: 0xCA8258 VA: 0xB40BB258 Slot: 159
    //  public virtual Transform GetHeadTF() { }
    uintptr_t GetHeadTF     =  0xCA8258;


    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xCB9518 Offset: 0xCB9518 VA: 0xB40CC518 Slot: 65
    //  public bool IsCameraTrackableEntityAlive() { }
    uintptr_t IsCameraTrackableEntityAlive  =   0xCB9518;

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xC5B2E0 Offset: 0xC5B2E0 VA: 0xB406E2E0 Slot: 106
    //  public virtual bool IsLocalTeammate() { }
    uintptr_t get_isLocalTeam   =   0xC5B2E0;


    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xCAD8C4 Offset: 0xCAD8C4 VA: 0xB40C08C4
    //  public bool IsFiring() { }
    uintptr_t IsFiring      =   0xCAD8C4;

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xC4DD3C Offset: 0xC4DD3C VA: 0xB4060D3C
    //  public void SetAimRotation(Quaternion JGOGIAFGCFC) { }
    uintptr_t SetAimRotation    =   0xC4DD3C;

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  public Transform MainCameraTransform; // 0xA8
    uintptr_t MainCameraTransform = 0xA8;

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xC4BFC8 Offset: 0xC4BFC8 VA: 0xB405EFC8
    //  public bool get_IsDieing() { }
    uintptr_t get_IsDieing      =   0xC4BFC8;

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xC4EA04 Offset: 0xC4EA04 VA: 0xB4061A04
    //  public bool get_IsReallyDead() { }
    uintptr_t get_IsReallyDead      =   0xC4EA04;

    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6268
    //  RVA: 0xC5176C Offset: 0xC5176C VA: 0xB406476C Slot: 56
    //  public override bool IsVisible() { }
    uintptr_t IsVisible     =   0xC5176C;

    //  Namespace: COW
    //  public class UavMapObject // TypeDefIndex: 15400
    //  RVA: 0x1816280 Offset: 0x1816280 VA: 0xB4C29280
    //  private static Player GetLocalPlayer() { }
    uintptr_t GetLocalPlayer =  0x1816280;


    //  Namespace: COW
    //  internal class GameFacade // TypeDefIndex: 4858
    //  RVA: 0xED3344 Offset: 0xED3344 VA: 0xB42E6344
    //  public static NFJPHMKKEBF CurrentMatch() { }
    uintptr_t Current_Match     =   0xED3344     ;

    //  Namespace: UnityEngine
    //  [NativeClassAttribute] // RVA: 0x706BE8 Offset: 0x706BE8 VA: 0xB3B19BE8
    //  [NativeHeaderAttribute] // RVA: 0x706BE8 Offset: 0x706BE8 VA: 0xB3B19BE8
    //  [RequiredByNativeCodeAttribute] // RVA: 0x706BE8 Offset: 0x706BE8 VA: 0xB3B19BE8
    //  public class Component : Object // TypeDefIndex: 1558
    //  [FreeFunctionAttribute] // RVA: 0x710184 Offset: 0x710184 VA: 0xB3B23184
    //  RVA: 0x3EA23D0 Offset: 0x3EA23D0 VA: 0xB72B53D0
    uintptr_t Component_GetTransform    =   0x3EA23D0;

    //  Namespace : UnityEngine
    //  class Transform {
    //  RVA: 0x42EEC88 Offset: 0x42EEC88 VA: 0xB7701C88
    //  private void get_position_Injected(out Vector3 ret) { }
    uintptr_t Transform_INTERNAL_GetPosition = 0x42EEC88;

    //  Namespace: UnityEngine
    //  [NativeHeaderAttribute] // RVA: 0x70BDCC Offset: 0x70BDCC VA: 0xB3B1EDCC
    //  [RequiredByNativeCodeAttribute] // RVA: 0x70BDCC Offset: 0x70BDCC VA: 0xB3B1EDCC
    //  [NativeHeaderAttribute] // RVA: 0x70BDCC Offset: 0x70BDCC VA: 0xB3B1EDCC
    //  [NativeHeaderAttribute] // RVA: 0x70BDCC Offset: 0x70BDCC VA: 0xB3B1EDCC
    //  public class Transform : Component, IEnumerable // TypeDefIndex: 2060
    //  RVA: 0x42EF7E8 Offset: 0x42EF7E8 VA: 0xB77027E8
    //  public Vector3 get_forward() { }
    uintptr_t GetForward    =   0x42EF7E8;

    //  Namespace: COW.GamePlay
    //  internal abstract class AttackableEntity : COWReplicationEntity, OPILIBBOEAC // TypeDefIndex: 4945
    //  RVA: 0xEFC2DC Offset: 0xEFC2DC VA: 0xB430F2DC Slot: 35
    //  public bool get_IsDead() { }
    uintptr_t AttackableEntity_get_IsDead   = 0xEFC2DC;

    //  Namespace: COW.GamePlay
    //  internal class NFJPHMKKEBF // TypeDefIndex: 5796
    //  protected Dictionary<byte, Player> NIEBEGJADLC; // 0x4C
    uintptr_t Dictionary    =   0x4C;

    //  RVA: 0xCF9008 Offset: 0xCF9008 VA: 0xB410C008
    //  public bool get_IsSighting() { }
    uintptr_t get_IsSighting = 0xCF9008;

    //  [FreeFunctionAttribute] // RVA: 0x70FED0 Offset: 0x70FED0 VA: 0xB3B22ED0
    // RVA: 0x3EA0290 Offset: 0x3EA0290 VA: 0xB72B3290
    //  public static Camera get_main() { }
    uintptr_t Camera_main    = 0x3EA0290;

    //  RVA: 0xC95964 Offset: 0xC95964 VA: 0xB40A8964
    //  public int get_MaxHP() { }
    uintptr_t get_MaxHP      = 0xC95964;

    //  RVA: 0x3E9F91C Offset: 0x3E9F91C VA: 0xB72B291C
    //  public Vector3 WorldToScreenPoint(Vector3 position) { }
    uintptr_t WorldToScreenPoint = 0x3E9F91C;

    //  RVA: 0x42EED28 Offset: 0x42EED28 VA: 0xB7701D28
    //  private void set_position_Injected(ref Vector3 value) { }
    uintptr_t Transform_INTERNAL_SetPosition = 0x42EED28;

    //  RVA: 0xCD2010 Offset: 0xCD2010 VA: 0xB40E5010
    //  public float get_MaxJumpHeight() { }
    uintptr_t MaxJumpHeight = 0xCD2010;



    //  Namespace: COW.GamePlay
    //  internal class Player : AttackableEntity, MPICKNDAPEB, AEPAPLNNAHF, IReusableObjectOwner, IJOMOIINJGM // TypeDefIndex: 6368
    //  RVA: 0xC4DBD4 Offset: 0xC4DBD4 VA: 0xB4060BD4
    //  public bool get_InSwapWeaponCD() { }
    uintptr_t get_InSwapWeaponCD = 0xC4DBD4;

    //  RVA: 0x26A3D9C Offset: 0x26A3D9C VA: 0xB5AB6D9C
    //  public float GetScatterRate() { }
    uintptr_t GetScatterRate = 0x26A3D9C;



} OffsetStruct;
OffsetStruct Offset;

typedef struct {


    //  Namespace: GCommon.Checker
    //  public static class MDDJBKJANJH // TypeDefIndex: 20306
    //  RVA: 0x2D78CF4 Offset: 0x2D78CF4 VA: 0xB618BCF4
    //  public static byte[] HBPBMIOJGFA() { }
    uintptr_t HBPBMIOJGFA   =   0x2D78CF4;

    //  Namespace: UnityEngine
    //  [NativeHeaderAttribute] // RVA: 0x705F88 Offset: 0x705F88 VA: 0xB3B18F88
    //  [StaticAccessorAttribute] // RVA: 0x705F88 Offset: 0x705F88 VA: 0xB3B18F88
    //  public class AndroidJNI // TypeDefIndex: 1510
    //  [ThreadSafeAttribute] // RVA: 0x70E7C8 Offset: 0x70E7C8 VA: 0xB3B217C8
    //  RVA: 0x3E8CD9C Offset: 0x3E8CD9C VA: 0xB729FD9C
    //  public static bool IsInstanceOf(IntPtr obj, IntPtr clazz) { }
    uintptr_t IsInstanceOf = 0x3E8CD9C;

    //  Namespace: ffano
    //  public class FNFOLKEMMBG // TypeDefIndex: 19358
    //  RVA: 0x2887D64 Offset: 0x2887D64 VA: 0xB5C9AD64
    //  public static void CCNEAFOPMIH(string DJKDKPMGKGH, string[] CLFFPBABFLP) { }
    uintptr_t CCNEAFOPMIH = 0x2887D64;

    //  Namespace: ffano
    //  public class FNFOLKEMMBG // TypeDefIndex: 19358
    //  RVA: 0x2887C20 Offset: 0x2887C20 VA: 0xB5C9AC20
    //  public static void AOCFOHFIAAM(string APKJPKBCCGD) { }
    uintptr_t AOCFOHFIAAM = 0x2887C20;

    //  Namespace: COW.GamePlay
    //  internal class KPDMJKOEHEE // TypeDefIndex: 6096
    //  RVA: 0xBE0AD0 Offset: 0xBE0AD0 VA: 0xB3FF3AD0
    //  private void LGINFBPMLAI(LGBENPIAFIN LHCHNFGKLHD) { }
    uintptr_t LGINFBPMLAI = 0xBE0AD0;

    //  Namespace: AnoSDKNamespace
    //  public static class IOPOOHPNCKH // TypeDefIndex: 19363
    //  RVA: 0x2BC0D68 Offset: 0x2BC0D68 VA: 0xB5FD3D68
    //  private static extern void LJGJMOPAEFB(int ELAMBPJFGBA) { }
    uintptr_t LJGJMOPAEFB = 0x2BC0D68;

    //  Namespace: AnoSDKNamespace
    //  public static class IOPOOHPNCKH // TypeDefIndex: 19363
    //  RVA: 0x2BC0D60 Offset: 0x2BC0D60 VA: 0xB5FD3D60
    //  public static void DPLMGOJKKCM(int EFDAAJBHMPD) { }
    //  public static void init(int gameId) { }
    uintptr_t init = 0x2BC0D60;

    //  Namespace: AnoSDKNamespace
    //  public static class IOPOOHPNCKH // TypeDefIndex: 19363
    //  RVA: 0x2BC0E64 Offset: 0x2BC0E64 VA: 0xB5FD3E64
    //  public static void LBABEMNOJAJ(int MAPEMGAINLD, string FACMPNNICKG) { }
    //  public static void SetUserInfo(int entryId, string openId) { }
    uintptr_t SetUserInfo = 0x2BC0E64;

    // Namespace: GCommon
    //  public static class PlatformUtility_Android // TypeDefIndex: 20274
    //  RVA: 0x32D0AA0 Offset: 0x32D0AA0 VA: 0xB66E3AA0
    //  public static bool IsPackageInstalled(string bundleIdentifier) { }
    uintptr_t IsPackageInstalled = 0x32D0AA0;


    //  Namespace: COW
    //  internal class UIModelLogin : UIBaseModel // TypeDefIndex: 16727
    //  RVA: 0x12A0B28 Offset: 0x12A0B28 VA: 0xB46B3B28
    //  private void DetectAndroidApplications(CSGetAndroidApplicationToDetectRes androidApplicationToDetectRes) { }
    uintptr_t DetectAndroidApplications = 0x12A0B28;


    //  Namespace: COW
    //  public static class EventLogger // TypeDefIndex: 4663
    //  RVA: 0x1A64D0C Offset: 0x1A64D0C VA: 0xB4E77D0C
    //  public static void LogAndroidApplicationDetection(List<int> installedIDs) { }
    uintptr_t LogAndroidApplicationDetection = 0x1A64D0C;

    //  RVA: 0x1A65138 Offset: 0x1A65138 VA: 0xB4E78138
    //  public static void InitCacheLogSend() { }
    uintptr_t InitCacheLogSend = 0x1A65138;

    //  RVA: 0x1A59DF0 Offset: 0x1A59DF0 VA: 0xB4E6CDF0
    //  private static void SendCachedLogs() { }
    uintptr_t SendCachedLogs = 0x1A59DF0;

    //  RVA: 0x1A65FFC Offset: 0x1A65FFC VA: 0xB4E78FFC
    //  private static void InitLeaveGameLog() { }
    uintptr_t InitLeaveGameLog = 0x1A65FFC;

    //  RVA: 0x1A669FC Offset: 0x1A669FC VA: 0xB4E799FC
    //  public static void LogIOSIDFA(string open_id, string idfa) { }
    uintptr_t LogIOSIDFA = 0x1A669FC;

    //  RVA: 0x1A6E11C Offset: 0x1A6E11C VA: 0xB4E8111C
    //  private static void InitLogLeaveWaitingIsland() { }
    uintptr_t InitLogLeaveWaitingIsland = 0x1A6E11C;

    //  RVA: 0x1A6E464 Offset: 0x1A6E464 VA: 0xB4E81464
    //  public static void SendLogLeaveWaitingIsland() { }
    uintptr_t SendLogLeaveWaitingIsland = 0x1A6E464;

    //  RVA: 0x1A6E700 Offset: 0x1A6E700 VA: 0xB4E81700
    //  public static void LogLeaveWaitingIslandPing() { }
    uintptr_t LogLeaveWaitingIslandPing = 0x1A6E700;

    //  RVA: 0x1A6ED84 Offset: 0x1A6ED84 VA: 0xB4E81D84
    //  public static void LogClientPushSetting(bool is_first_login = False) { }
    uintptr_t LogClientPushSetting = 0x1A6ED84;

    //  RVA: 0x1A6EF98 Offset: 0x1A6EF98 VA: 0xB4E81F98
    //  public static void LogClientSettingChange() { }
    uintptr_t LogClientSettingChange = 0x1A6EF98;


    //  RVA: 0x1A6E378 Offset: 0x1A6E378 VA: 0xB4E81378
    //  public static void LogLeaveWaitingIslandBattleStarted(bool battleStarted) { }
    uintptr_t LogLeaveWaitingIslandBattleStarte = 0x1A6E378;

    //  RVA: 0x198905C Offset: 0x198905C VA: 0xBFBB505C
    //  public static void CacheBackMall() { }
    uintptr_t CacheBackMall = 0x198905C;

    //  RVA: 0x1A6C450 Offset: 0x1A6C450 VA: 0xB4E7F450
    //  public static void LogClickGetAvatarBtn(uint avatarID, bool isbundlebtn) { }
    uintptr_t LogClickGetAvatarBtn = 0x1A6C450;

    //  RVA: 0x2EF32C8 Offset: 0x2EF32C8 VA: 0xC111F2C8
    //  private void OnApplicationPause(bool paused) { }
    uintptr_t OnApplicationPause = 0x2EF32C8;

    //  RVA: 0x1CCE85C Offset: 0x1CCE85C VA: 0xB50E185C
    //  public static void OnApplicationQuit() { }
    uintptr_t OnApplicationQuit = 0x1CCE85C;

    //  RVA: 0x1CCE564 Offset: 0x1CCE564 VA: 0xB50E1564
    //  public static void SendCacheEvent() { }
    uintptr_t SendCacheEven  = 0x1CCE564;

    //  RVA: 0x1A5DC2C Offset: 0x1A5DC2C VA: 0xB4E70C2C
    //  public static void LogGameMemory(EventLogger.EGameTimeType _type) { }
    uintptr_t LogGameMemory = 0x1A5DC2C;

    //  RVA: 0x197C010 Offset: 0x197C010 VA: 0xBFBA8010
    //  public static void StartObserver(int mode) { }

    //  RVA: 0x1A61788 Offset: 0x1A61788 VA: 0xB4E74788
    //  public static void LogScanIAPInventoryResult(EventLogger.ScanIAPInventoryResult[] results) { }
    uintptr_t LogScanIAPInventoryResult = 0x1A61788;

    //  RVA: 0x1A5B874 Offset: 0x1A5B874 VA: 0xB4E6E874
    //  public static void SendLogObserver() { }
    uintptr_t SendLogObserver = 0x1A5B874;

    //  RVA: 0x1A60388 Offset: 0x1A60388 VA: 0xB4E73388
    //  public static void SendNetworkEventLog(string eventType, object payload) { }
    uintptr_t SendNetworkEventLog = 0x1A60388;

    //  RVA: 0x1A5DF20 Offset: 0x1A5DF20 VA: 0xB4E70F20
    //  private static void SendGameMemoryLog() { }
    uintptr_t SendGameMemoryLog = 0x1A5DF20;

    //  RVA: 0x1A5E318 Offset: 0x1A5E318 VA: 0xB4E71318
    //  public static void StartLogGameLag() { }
    uintptr_t StartLogGameLag = 0x1A5E318;

    //  RVA: 0x1A5EC6C Offset: 0x1A5EC6C VA: 0xB4E71C6C
    //  public static void SendGameLagLog() { }
    uintptr_t SendGameLagLog = 0x1A5EC6C;

    //  RVA: 0x1A5B2D4 Offset: 0x1A5B2D4 VA: 0xB4E6E2D4
    //  public static void SendEventLog(string eventType, EventLogger.EventLoggerBase payload) { }
    uintptr_t SendEventLog = 0x1A5B2D4;

    //  RVA: 0x1A60804 Offset: 0x1A60804 VA: 0xB4E73804
    //  public static EventLogger.EventLoginInfo LoginInfo() { }
    uintptr_t LoginInfo = 0x1A60804;

    //  RVA: 0x1A62218 Offset: 0x1A62218 VA: 0xB4E75218
    //  public static void LogReportCheat(ulong cheater, uint reason, IHAAMHPPLMG cheaterPlayerID, uint[] subReason, bool inGame = True, uint reporteeType = 4) { }
    uintptr_t LogReportCheat = 0xB4E75218;

    // RVA: 0x1A63000 Offset: 0x1A63000 VA: 0xB4E76000
    //  public static void LogReportCheatInHistory(ulong cheater, uint reason, MatchStats stats, ulong matchID = 0, uint[] subReason, uint reporteeType = 4) { }
    uintptr_t LogReportCheatInHistory  = 0x1A63000;

    //  RVA: 0x1A67430 Offset: 0x1A67430 VA: 0xB4E7A430
    //  public static void SendLogLeaveGame() { }
    uintptr_t SendLogLeaveGame = 0x1A67430;

    //  [CompilerGeneratedAttribute] // RVA: 0x809070 Offset: 0x809070 VA: 0xB3C1C070
    //  RVA: 0x1A75900 Offset: 0x1A75900 VA: 0xB4E88900
    //  private static bool <SendCachedLogs>m__0(EventLogger.EventLogPageDetentionTimeItem item) { }
    uintptr_t EventLogPageDetentionTimeItem = 0x1A75900;

    //  [CompilerGeneratedAttribute] // RVA: 0x809080 Offset: 0x809080 VA: 0xB3C1C080
    //  RVA: 0x1A75930 Offset: 0x1A75930 VA: 0xB4E88930
    //  private static bool <SendCachedLogs>m__1(EventLogger.EventTypePopupWindowViewTime.SinglePopupWindowViewTime item) { }
    uintptr_t EventTypePopupWindowViewTime = 0x1A75930;

    //  RVA: 0x1A65518 Offset: 0x1A65518 VA: 0xB4E78518
    //  public static void LogEnterGame() { }
    uintptr_t LogEnterGame = 0x1A65518;


    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x772944 Offset: 0x772944 VA: 0xB3B85944
    //  public class BlacklistInfoRes // TypeDefIndex: 10093
    uintptr_t BlacklistInfoRes = 0x772944;

    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x76FAB4 Offset: 0x76FAB4 VA: 0xB3B82AB4
    //  public class BlacklistReq // TypeDefIndex: 9348
    uintptr_t BlacklistReq = 0x76FAB4;

    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x76FAC4 Offset: 0x76FAC4 VA: 0xB3B82AC4
    //  public class BlacklistRes // TypeDefIndex: 9349
    uintptr_t BlacklistRes = 0x76FAC4;

    //  Namespace:
    //  [ProtoContractAttribute] // RVA: 0x76E3E4 Offset: 0x76E3E4 VA: 0xB3B813E4
    //  public enum EAccount.BlacklistOpType // TypeDefIndex: 8983
    uintptr_t   BlacklistOpType = 0x76E3E4;

    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x76FAA4 Offset: 0x76FAA4 VA: 0xB3B82AA4
    //  public class BlacklistOpReq // TypeDefIndex: 9347
    uintptr_t BlacklistOpReq = 0x76FAA4;


    //  RVA: 0x2FF4918 Offset: 0x2FF4918 VA: 0xB6407918
    //  public List<FriendAccountInfo> get_BlackListAccountInfo() { }
    uintptr_t get_BlackListAccountInfo = 0x2FF4918;


    //  Namespace: COW
    //  public class UIModelRankingItem : UIBaseModel // TypeDefIndex: 16949
    //  RVA: 0x309B80C Offset: 0x309B80C VA: 0xB64AE80C
    //  public void ProcessRankingItem(GetRankingItemRankConfigRes res) { }
    uintptr_t ProcessRankingItem = 0x309B80C;

    //  RVA: 0x309B878 Offset: 0x309B878 VA: 0xB64AE878
    //  public RankingItemRank FindRankingItemDataByID(uint itemID) { }
    uintptr_t FindRankingItemDataByID = 0x309B878;

    //  RVA: 0x309B9C4 Offset: 0x309B9C4 VA: 0xB64AE9C4
    //  public bool CheckIsReachRankItemUseLevel(uint itemId) { }
    uintptr_t CheckIsReachRankItemUseLevel = 0x309B9C4;

    //  Namespace:
    //  [CompilerGeneratedAttribute] // RVA: 0x792898 Offset: 0x792898 VA: 0xB3BA5898
    //  private sealed class UIModelRankingItem.<FindRankingItemDataByID>c__AnonStorey0 // TypeDefIndex: 16950
    uintptr_t UIModelRankingItem = 0x792898;

    //  RVA: 0x309BB24 Offset: 0x309BB24 VA: 0xB64AEB24
    //  internal bool <>m__0(RankingItemRank data) { }
    uintptr_t RankingItemRank = 0x309BB24;


    //  [CompilerGeneratedAttribute] // RVA: 0x819F28 Offset: 0x819F28 VA: 0xB3C2CF28
    //  RVA: 0x314FAC0 Offset: 0x314FAC0 VA: 0xB6562AC0
    //  public uint get_ban_type() { }
    uintptr_t get_ban_type = 0x314FAC0;

    //  [CompilerGeneratedAttribute] // RVA: 0x819F38 Offset: 0x819F38 VA: 0xB3C2CF38
    //  RVA: 0x314FAC8 Offset: 0x314FAC8 VA: 0xB6562AC8
    //  public void set_ban_type(uint value) { }
    uintptr_t set_ban_type = 0x314FAC8;

    //  Namespace: tcp
    //  [ProtoContractAttribute] // RVA: 0x7794D4 Offset: 0x7794D4 VA: 0xB3B8C4D4
    //  public class AccountMatchInfo // TypeDefIndex: 11831
    //  [CompilerGeneratedAttribute] // RVA: 0x81AB88 Offset: 0x81AB88 VA: 0xB3C2DB88
    //  RVA: 0x31502D8 Offset: 0x31502D8 VA: 0xB65632D8
    //  public List<AccountMatchBanInfo> get_match_ban_info() { }
    uintptr_t get_match_ban_info = 0x31502D8;

    //  [CompilerGeneratedAttribute] // RVA: 0x81AB98 Offset: 0x81AB98 VA: 0xB3C2DB98
    //  RVA: 0x314FEE4 Offset: 0x314FEE4 VA: 0xB6562EE4
    //  private void set_match_ban_info(List<AccountMatchBanInfo> value) { }
    uintptr_t set_match_ban_info = 0x314FEE4;


    //  [CompilerGeneratedAttribute] // RVA: 0x81D528 Offset: 0x81D528 VA: 0xB3C30528
    //  RVA: 0x314FAE8 Offset: 0x314FAE8 VA: 0xB6562AE8
    //  public uint get_ban_expire_time() { }
    uintptr_t get_ban_expire_time = 0x81D528;

    //  [CompilerGeneratedAttribute] // RVA: 0x81D538 Offset: 0x81D538 VA: 0xB3C30538
    //  RVA: 0x314FAF0 Offset: 0x314FAF0 VA: 0xB6562AF0
    //  public void set_ban_expire_time(uint value) { }
    uintptr_t set_ban_expire_time = 0x314FAF0;


    //  RVA: 0xD5B5E4 Offset: 0xD5B5E4 VA: 0xB416E5E4
    //  private void HideEPRanking(object[] param) { }

    //  RVA: 0x1C534CC Offset: 0x1C534CC VA: 0xB50664CC
    //  private void SetMiniGameRanking() { }


    //  [CompilerGeneratedAttribute] // RVA: 0x814F88 Offset: 0x814F88 VA: 0xB3C27F88
    //  RVA: 0x39C74C4 Offset: 0x39C74C4 VA: 0xB6DDA4C4
    //  public uint get_ranking_points() { }

    //  RVA: 0xDDF064 Offset: 0xDDF064 VA: 0xB41F2064
    //  public void ClearEPRankingList() { }

    //  RVA: 0xDEBDB4 Offset: 0xDEBDB4 VA: 0xB41FEDB4
    //  public void UpdateEPRankingList(ulong userID, IHAAMHPPLMG pID, bool isAI, object syncInfo) { }

    //  RVA: 0xDEB8AC Offset: 0xDEB8AC VA: 0xB41FE8AC
    //  private void RefreshEPRankingSurroundEffect() { }

    //  [CompilerGeneratedAttribute] // RVA: 0x82F68C Offset: 0x82F68C VA: 0xB3C4268C
    //  RVA: 0xE002E8 Offset: 0xE002E8 VA: 0xB42132E8
    //  private static int <UpdateEPRankingList>m__1(EPPlayerInfo a, EPPlayerInfo b) { }

    //  RVA: 0x336B9A4 Offset: 0x336B9A4 VA: 0xB677E9A4
    //  public void MergeMatchingOverlays() { }

    //  RVA: 0x336BB98 Offset: 0x336BB98 VA: 0xB677EB98
    //  public static bool OverlayListsMatch(List<OverlayData> list1, List<OverlayData> list2) { }

    //  [CompilerGeneratedAttribute] // RVA: 0x8135E8 Offset: 0x8135E8 VA: 0xB3C265E8
    //  RVA: 0x3150C9C Offset: 0x3150C9C VA: 0xB6563C9C
    //  public uint get_rank() { }


    //  RVA: 0x2063794 Offset: 0x2063794 VA: 0xB5476794
    //  public LatestRankInfo get_RankInfo() { }


    //  RVA: 0x206380C Offset: 0x206380C VA: 0xB547680C
    //  public void SetLatestRankInfo(bool isRank, uint rankBefore, uint rankAfter, int scoreBefore, int scoreAfter) { }

    //  [CompilerGeneratedAttribute] // RVA: 0x8135E8 Offset: 0x8135E8 VA: 0xB3C265E8
    //  RVA: 0x3150C9C Offset: 0x3150C9C VA: 0xB6563C9C
    //  public uint get_rank() { }



    //  [CompilerGeneratedAttribute] // RVA: 0x814F88 Offset: 0x814F88 VA: 0xB3C27F88
    //  RVA: 0x39C74C4 Offset: 0x39C74C4 VA: 0xB6DDA4C4
    //  public uint get_ranking_points() { }

    //  [CompilerGeneratedAttribute] // RVA: 0x8135F8 Offset: 0x8135F8 VA: 0xB3C265F8
    //  RVA: 0x3150CA4 Offset: 0x3150CA4 VA: 0xB6563CA4
    //  public void set_rank(uint value) { }

    //  RVA: 0x1866D40 Offset: 0x1866D40 VA: 0xB4C79D40
    //  public static bool IsMatchGame() { }

    //  RVA: 0x311ECD4 Offset: 0x311ECD4 VA: 0xB6531CD4
    //  public bool get_IsCSRankingMatch() { }

    //  RVA: 0x311EBD0 Offset: 0x311EBD0 VA: 0xB6531BD0
    //  public bool get_IsRankingMatch() { }

    //  RVA: 0x2711028 Offset: 0x2711028 VA: 0xB5B24028
    //  public uint get_GameMode() { }

    //  RVA: 0x312E784 Offset: 0x312E784 VA: 0xB6541784
    //  public void SetAutoMatch(bool v) { }

    //  [CompilerGeneratedAttribute] // RVA: 0x807798 Offset: 0x807798 VA: 0xB3C1A798
    //  RVA: 0x107D9C0 Offset: 0x107D9C0 VA: 0xB44909C0
    //  public uint get_UnlockLevel() { }

    //  [CompilerGeneratedAttribute] // RVA: 0x808654 Offset: 0x808654 VA: 0xB3C1B654
    //  RVA: 0x1E6C61C Offset: 0x1E6C61C VA: 0xB527F61C
    //  public int get_LevelLimit() { }

    //  RVA: 0x2EA10C8 Offset: 0x2EA10C8 VA: 0xB62B40C8 Slot: 46
    //  public void OnDataChanged(UIBaseModel model, uint propID, object[] param) { }


    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x76ED44 Offset: 0x76ED44 VA: 0xB3B81D44
    //  public class MailSenderInfo // TypeDefIndex: 9133
    //   [ProtoMemberAttribute] // RVA: 0x7A736C Offset: 0x7A736C VA: 0xB3BBA36C
    //  public uint match_ban_expire_time; // 0x90
    uintptr_t match_ban_expire_time = 0x7A736C;

    //  [ProtoMemberAttribute] // RVA: 0x7A7568 Offset: 0x7A7568 VA: 0xB3BBA568
    //  public long match_create_time; // 0x20
    uintptr_t match_create_time = 0x7A7568;

    //  [ProtoMemberAttribute] // RVA: 0x7A757C Offset: 0x7A757C VA: 0xB3BBA57C
    //  public long report_time; // 0x28
    uintptr_t report_time = 0x7A757C;


    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x7758A4 Offset: 0x7758A4 VA: 0xB3B888A4
    //  public class HackMatchPoolCdtDesc // TypeDefIndex: 10851
    uintptr_t HackMatchPoolCdtDesc = 0x7758A4;

    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x775E14 Offset: 0x775E14 VA: 0xB3B88E14
    //  public class AntiHackProtectSettingDesc // TypeDefIndex: 10938
    uintptr_t AntiHackProtectSettingDesc = 0x775E14;

    //  [ProtoMemberAttribute] // RVA: 0x7CE42C Offset: 0x7CE42C VA: 0xB3BE142C
    //  public bool gs_test_hack; // 0x8
    uintptr_t gs_test_hack = 0x7CE42C;

    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x7708E4 Offset: 0x7708E4 VA: 0xB3B838E4
    //  public class MatchIncome // TypeDefIndex: 9575
    //  [ProtoMemberAttribute] // RVA: 0x7AD134 Offset: 0x7AD134 VA: 0xB3BC0134
    //  public bool is_anti_hack_protect; // 0xF4
    uintptr_t is_anti_hack_protect = 0x7AD134;


    //  Namespace: COW
    //  [AddComponentMenu] // RVA: 0x77F0EC Offset: 0x77F0EC VA: 0xB3B920EC
    //  public class UIHudLadderMatchResultController : UIPopupWindowController // TypeDefIndex: 12940
    //  RVA: 0x1EAAEC8 Offset: 0x1EAAEC8 VA: 0xB52BDEC8
    //  private void InitAntiHackProtect(MatchIncome income) { }
    uintptr_t InitAntiHackProtect = 0x1EAAEC8;

    //  Namespace:
    //  [ProtoContractAttribute] // RVA: 0x76FE44 Offset: 0x76FE44 VA: 0xB3B82E44
    //  public enum EHacker.HackerPoolCdt // TypeDefIndex: 9405
    uintptr_t HackerPoolCdt = 0x76FE44;


    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x772914 Offset: 0x772914 VA: 0xB3B85914
    //  public class LoginReq // TypeDefIndex: 10090


    //  Namespace: proto
    //  [ProtoContractAttribute] // RVA: 0x775784 Offset: 0x775784 VA: 0xB3B88784
    //  public class MatchmakingDesc // TypeDefIndex: 10833
    //  [ProtoMemberAttribute] // RVA: 0x7CA0F8 Offset: 0x7CA0F8 VA: 0xB3BDD0F8
    //  public uint[] hackers_pool_effect_mode; // 0x40
    uintptr_t hackers_pool_effect_mode = 0x7CA0F8;

    //  [CompilerGeneratedAttribute] // RVA: 0x812F68 Offset: 0x812F68 VA: 0xB3C25F68
    //  RVA: 0x3150714 Offset: 0x3150714 VA: 0xB6563714
    //  public uint get_unban_time() { }
    uintptr_t get_unban_time = 0x3150714;

    //  [CompilerGeneratedAttribute] // RVA: 0x812F78 Offset: 0x812F78 VA: 0xB3C25F78
    //  RVA: 0x315071C Offset: 0x315071C VA: 0xB656371C
    //  public void set_unban_time(uint value) { }
    uintptr_t set_unban_time  = 0x315071C;

    //  [CompilerGeneratedAttribute] // RVA: 0x817408 Offset: 0x817408 VA: 0xB3C2A408
    //  RVA: 0x39CA1D8 Offset: 0x39CA1D8 VA: 0xB6DDD1D8
    //  public uint get_hacker_cdt_id() { }
    uintptr_t get_hacker_cdt_id = 0x39CA1D8;

    //  [CompilerGeneratedAttribute] // RVA: 0x817418 Offset: 0x817418 VA: 0xB3C2A418
    //  RVA: 0x39CA1E0 Offset: 0x39CA1E0 VA: 0xB6DDD1E0
    //  public void set_hacker_cdt_id(uint value) { }
    uintptr_t set_hacker_cdt_id = 0x39CA1E0;



//    // RVA: 0xEC5764 Offset: 0xEC5764 VA: 0xB42D8764
//public static string get_DetectAndroidApplicationBundleIdentifier() { }
//// RVA: 0x12A0B28 Offset: 0x12A0B28 VA: 0xB46B3B28
//private void DetectAndroidApplications(CSGetAndroidApplicationToDetectRes androidApplicationToDetectRes) { }
//// Namespace: proto
//    [ProtoContractAttribute] // RVA: 0x777334 Offset: 0x777334 VA: 0xB3B8A334
//public class AndroidApplicationToDetectDesc // TypeDefIndex: 11276
//// Namespace: proto
//    [ProtoContractAttribute] // RVA: 0x7728C4 Offset: 0x7728C4 VA: 0xB3B858C4
//public class CSGetAndroidApplicationToDetectRes // TypeDefIndex: 10085
//
//// Fields
//    [ProtoMemberAttribute] // RVA: 0x7B8EA8 Offset: 0x7B8EA8 VA: 0xB3BCBEA8
//public List<AndroidApplicationToDetectDesc> android_apps_to_detect_res; // 0x8
//
//
//    [ProtoMemberAttribute] // RVA: 0x7AE328 Offset: 0x7AE328 VA: 0xB3BC1328
//public uint[] detected_behaviors; // 0xC4
//// RVA: 0x1A64D0C Offset: 0x1A64D0C VA: 0xB4E77D0C
//public static void LogAndroidApplicationDetection(List<int> installedIDs) { }
//
//
//    DebuggerBrowsableAttribute] // RVA: 0x7EF4DC Offset: 0x7EF4DC VA: 0xB3C024DC
//    [CompilerGeneratedAttribute] // RVA: 0x7EF4DC Offset: 0x7EF4DC VA: 0xB3C024DC
//private bool <is_hacker>k__BackingField; // 0x28
//
//    [ProtoMemberAttribute] // RVA: 0x846984 Offset: 0x846984 VA: 0xB3C59984
//public bool is_hacker { get; set; }
//
//    [ProtoMemberAttribute] // RVA: 0x846A0C Offset: 0x846A0C VA: 0xB3C59A0C
//public uint hacker_cdt_id { get; set; }
//
//    [CompilerGeneratedAttribute] // RVA: 0x817388 Offset: 0x817388 VA: 0xB3C2A388
//    // RVA: 0x39CA1A0 Offset: 0x39CA1A0 VA: 0xB6DDD1A0
//public bool get_is_hacker() { }
//
//
//    [CompilerGeneratedAttribute] // RVA: 0x817398 Offset: 0x817398 VA: 0xB3C2A398
//    // RVA: 0x39CA1A8 Offset: 0x39CA1A8 VA: 0xB6DDD1A8
//public void set_is_hacker(bool value) { }
//

//
//    [CompilerGeneratedAttribute] // RVA: 0x817418 Offset: 0x817418 VA: 0xB3C2A418
//    // RVA: 0x39CA1E0 Offset: 0x39CA1E0 VA: 0xB6DDD1E0
//public void set_hacker_cdt_id(uint value) { }
//
//    [CompilerGeneratedAttribute] // RVA: 0x819EE8 Offset: 0x819EE8 VA: 0xB3C2CEE8
//    // RVA: 0x314F970 Offset: 0x314F970 VA: 0xB6562970
//public uint get_hacker_tag() { }
//
//    [CompilerGeneratedAttribute] // RVA: 0x819EF8 Offset: 0x819EF8 VA: 0xB3C2CEF8
//    // RVA: 0x314F978 Offset: 0x314F978 VA: 0xB6562978
//public void set_hacker_tag(uint value) { }
//
//    [CompilerGeneratedAttribute] // RVA: 0x819F08 Offset: 0x819F08 VA: 0xB3C2CF08
//    // RVA: 0x314F980 Offset: 0x314F980 VA: 0xB6562980
//public long get_hackerpool_time() { }
//
//    [CompilerGeneratedAttribute] // RVA: 0x819F18 Offset: 0x819F18 VA: 0xB3C2CF18
//    // RVA: 0x314F988 Offset: 0x314F988 VA: 0xB6562988
//public void set_hackerpool_time(long value) { }
//





}BypassStruct;
BypassStruct Bypass;



typedef struct{

    uintptr_t AnoSDKDelReportData           = 0x000334d5;
    uintptr_t AnoSDKDelReportData3          = 0x00033501;
    uintptr_t AnoSDKForExport               = 0x0003352d;
    uintptr_t AnoSDKFree                    = 0x000334f5;
    uintptr_t AnoSDKGetReportData           = 0x000334c1;
    uintptr_t AnoSDKGetReportData2          = 0x000334f9;
    uintptr_t AnoSDKGetReportData3          = 0x000334fd;
    uintptr_t AnoSDKInit                    = 0x000333fd;
    uintptr_t AnoSDKIoctl                   = 0x000334f1;
    uintptr_t AnoSDKIoctlOld                = 0x000334ed;
    uintptr_t AnoSDKOnPause                 = 0x00033495;
    uintptr_t AnoSDKOnRecvData              = 0x000334e9;
    uintptr_t AnoSDKOnRecvSignature         = 0x00033505;
    uintptr_t AnoSDKOnResume                = 0x000334ab;
    uintptr_t AnoSDKRegistInfoListener      = 0x00033509;
    uintptr_t AnoSDKSetUserInfo             = 0x00033415;
    uintptr_t AnoSDKSetUserInfoWithLicense  = 0x00033451;
    uintptr_t JNI_OnLoad                    = 0x002892f1;

}AnoSDKStruct;
AnoSDKStruct AnoSDK;


typedef struct {
    uintptr_t JNI_OnLoad = 0x00003d71;
    uintptr_t unwind_xx_info_query = 0x000a1a9d;
} AnortStruct;
AnortStruct Anort;

/*
 ADDRESS(0x198B904, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x198BB70, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x198BCDC, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1986884, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1986A70, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1986E94, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1987028, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x19872BC, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x19873D0, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1987560, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1987954, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1987D98, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1D76928, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x14FA9DC, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1989724, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x198993C, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1989A28, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1989B74, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1989CB4, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1989DF4, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x1989F34, _LogsFreeFire, LogsFreeFire); //[1.68]
ADDRESS(0x198A030, _LogsFreeFire, LogsFreeFire); //[1.68]
 */

#endif
