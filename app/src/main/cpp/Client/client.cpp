#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../Socket/SocketClient.h"
#include "../ClientServerCommon/ClientServerCommon.h"
#include "Icon.h"
#include "ESP/ESP.h"
#include "../Utils/Obfuscate.h"

#define LOG_TAG "Debug"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)


bool EspEnabled = false;

/* -------------- Init Socket ------------- */
int     startClient();
bool    isServerOK();
bool    makeRequest(Request& request, Response& response);

SocketClient client;

int  startClient(){

    client = SocketClient();
    if( !client.Create() ){
        LOGD("%s", (char *)OBFUSCATE("Client: Failed to create client (-1)") );
        return -1;
    }
    if( !client.Connect() ){
        LOGD("%s", (char *)OBFUSCATE("Client: Failed to connect to server (-2) ") );
        return -2;
    }
    if( !isServerOK() ){
        LOGD("%s", (char *)OBFUSCATE("Client: Failed to connect to server (-3) ") );
        return -3;
    }
    return 0;
}

bool isServerOK() {
    Request  request{ FeatureMap.CHECK_SERVER, NULL };
    Response response{};
    if ( makeRequest(request,response) ){
        return true;
    };
    return false;
}

bool makeRequest(Request& request, Response& response){

    int code = client.send((void*) &request, sizeof(Request));
    if( code > 0 ) {
        size_t length = client.receive((void*) &response);
        if( length > 0 ){
            return true;
        }else LOGD("%s", (char*) OBFUSCATE("Client: Failed to get response form server") );
    }else LOGD("%s", (char*) OBFUSCATE("Client: Failed to send request to server"));

    return false;
}

/* -------------- End Socket -------------- */

__attribute__((constructor))
int main(){
    LOGD("%s", (char*) OBFUSCATE("Client: I am loaded in the address space"));
}

extern "C"
JNIEXPORT jint JNICALL
Java_gamingbd_pro_Native_StartClientNative(JNIEnv *env, jclass clazz, jobject context) {
    return startClient();
}

extern "C"
JNIEXPORT void JNICALL
Java_gamingbd_pro_Native_UpdateFeatureNative(JNIEnv *env, jclass clazz, jint feature, jint value) {

    Request  request {feature,value};
    Response response{};
    if ( !makeRequest(request,response) ){
        LOGD("%s", (char*) OBFUSCATE("Client: Response: Fail"));
        return;
    }

    if ( request.FeatureNumber == FeatureMap.ESP ){
        EspEnabled = (bool) request.FeatureValue ;
        if ( EspEnabled ) LOGD("%s", (char*) OBFUSCATE("Client: ESP ON") );
        else LOGD("%s", (char*) OBFUSCATE( "Client: ESP OFF") );

    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_gamingbd_pro_Native_IconNative(JNIEnv *env, jclass clazz) {
    return GetIcon(env);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_gamingbd_pro_Native_SuperUserPermissionGranted(JNIEnv *env, jclass clazz) {
    if ( system("su") == 0 )
        return true;
    return false;
}

Response GetEspData(){

    Request request{FeatureMap.ESP, true};
    if( client.send((void*) &request, sizeof(request)) > 0 ){
        Response response{};
        size_t length = client.receive((void*) &response);
        if(length > 0){
            return response;
        }
    }
    Response response{false, 0};
    return response;
}

bool isValidPlayer(PlayerData playerData) {
    return ( playerData.HeadLocation != Vector3::Zero() );
}

static long MapRange(long currentValue, long inputMin, long inputMax, long outputMin, long outputMax){
    return (currentValue - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
}

void DrawESP(ESP esp, int screenWidth, int screenHeight) {

    Response response = GetEspData();
    if( response.Success ) {
        if( response.PlayerCount > 0) {
            for( int i = 0; i < response.PlayerCount; i++) {

                PlayerData player = response.Players[i];
                if( !isValidPlayer(player) ) continue;

                Vector3 Head        = player.HeadLocation;
                Vector3 Start       = Vector3(((float)screenWidth / 2),0);
                Vector3 End         = Vector3(((float)screenWidth - ((float)screenWidth - Head.X)),((float)screenHeight - Head.Y - 8.0f));
                Color   lineColor   = player.IsDieing ? Color::Red() : Color::White();
                esp.DrawLine( lineColor , 1.0f, Start, End);

                char distanceText[128];
                sprintf(distanceText, "[ %.2fm ]", player.Distance);
                long  distanceTextSize = MapRange( 180 - (long)player.Distance, 0, 180, 10, 25);
                Color textColor   = player.IsDieing ? Color::Red() : Color::Green();
                End.Y += 30.0f;
                esp.DrawText( textColor , 1.0f , distanceText, End, distanceTextSize);
            }
        }
    }
}

/**
 * This function will be called 60 times in every second to draw on canvas
 */
ESP espOverlay;
extern "C"
JNIEXPORT void JNICALL
Java_gamingbd_pro_Native_DrawOn(JNIEnv *env, jclass clazz, jobject esp, jobject canvas) {
    espOverlay = ESP(env, esp, canvas);
    if ( espOverlay.isValid() ){
        DrawESP(espOverlay, espOverlay.getWidth(), espOverlay.getHeight());
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_gamingbd_pro_Native_EspEnabled(JNIEnv *env, jclass clazz) {
    return EspEnabled;
}