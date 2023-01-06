package gamingbd.pro;

import android.content.Context;
import android.graphics.Canvas;

public class Native {

    public static native boolean    SuperUserPermissionGranted();
    public static native int        StartClientNative(Context context);
    public static native void       UpdateFeatureNative(int Feature, int Value );
    public static native String     IconNative();
    public static native boolean    EspEnabled();

    /* ESP */
    public static native void       DrawOn(ESP esp, Canvas canvas);


}
