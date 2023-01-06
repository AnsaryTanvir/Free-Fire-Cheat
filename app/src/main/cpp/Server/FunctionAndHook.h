#ifndef FUNCTIONANDHOOK_H
#define FUNCTIONANDHOOK_H

/**------------------------------------------------------------------------------------------------*/
/** Do not touch these things */
typedef unsigned long DWORD;
static  DWORD       libBase = 0;
static  const char* libName = "libil2cpp.so";

DWORD getLibraryBase(const char* libName) {

    FILE *fp;
    DWORD address = 0;

    char filename[32], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", getpid());
    fp = fopen(filename, "rt");

    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, libName)) {
                address = (uintptr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return address;
}
DWORD getRealOffset(DWORD address) {
    if ( libBase == 0 )
        libBase = getLibraryBase(libName);
    return (libBase + address);
}

/** Do not touch these things */
/**------------------------------------------------------------------------------------------------*/


struct {
    MemoryPatch FastSwapWeapon;
    MemoryPatch NoRecoil;
    MemoryPatch TimerSpeed;
}Patches;


const char* TimerSpeedDefault = "0B 2E 11 3E"   ;
const char* GetTimerSpeedHex(int speed){

    char* CurrentTimerSpeed = (char*) calloc(12, sizeof (char));
    if ( speed == 0 ) return NULL;

    if  ( speed <= (0xFF-0x10) ){

        char FirstByte[] ="00";
        speed < 0xF ? sprintf(FirstByte, "0%x", speed ) : sprintf(FirstByte, "%x", speed);

        char ThirdByte[] ="10";
        sprintf(ThirdByte, "%x", speed+0x10 );

        sprintf(CurrentTimerSpeed, "%s 10 %s 3E", FirstByte, ThirdByte );
        for (int i = 0; i < (int)strlen(CurrentTimerSpeed); i++ ) CurrentTimerSpeed[i] = toupper(CurrentTimerSpeed[i]);
        return CurrentTimerSpeed;
    }

    return NULL;
}

#endif
