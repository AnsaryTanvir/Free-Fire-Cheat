package gamingbd.pro;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Process;
import android.provider.Settings;
import android.util.Log;
import android.widget.Toast;

import eu.chainfire.libsuperuser.Shell;
import static gamingbd.pro.Native.*;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("Client");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        /**
         * Get Super User Permission
         */
        GetSuperUserPermission(this);
        Log.d("Debug", Build.CPU_ABI);

        /**
         * Disable SeLinux to use ptrace system call/
         */
        Utils.disableSeLinux(getApplicationContext());

        /**
         * Start Floating Service & Kill Current Activity/
         */
        StartFloating(this);
        finish();

    }

    public static void StartFloating(Context context) {
        if ( Build.VERSION.SDK_INT <  23 || Settings.canDrawOverlays(context)) {
            context.startService(new Intent(context, FloatingViewService.class));
        } else {
            context.startActivity(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION", Uri.parse("package:" + context.getPackageName())));
            Process.killProcess(Process.myPid());
        }
    }

    public static boolean GetSuperUserPermission(Context context){
        try {
            Shell.Pool.SU.run("su");
            if ( SuperUserPermissionGranted() )
                return true;
        } catch (Shell.ShellDiedException e) {
            e.printStackTrace();
        }
        return false;
    }

}