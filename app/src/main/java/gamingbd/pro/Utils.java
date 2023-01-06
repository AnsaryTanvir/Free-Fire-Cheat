package gamingbd.pro;

import android.content.Context;
import android.os.Build;
import android.util.Log;
import android.widget.Toast;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import eu.chainfire.libsuperuser.Shell;
import static gamingbd.pro.Native.*;

public class Utils {


    public static String targetPackage = "com.dts.freefireth"   ; // Target package name
    public static String injector      = "injector.so"          ; // Name of the injector executable, defined in CMakeLists.txt
    public static String payload       = "libServer.so"         ; // Name of the payload, defined in CMakeLists.txt



    /**
     * This method is used to temporarily disable SeLinux globally.
     *
     * SeLinux or Security-Enhanced Linux is a Linux Security Module aimed to provide
     * Mandatory Access Control (MAC).
     * With SELinux enabled, root access can't do everything anymore because it imposes some
     * restriction such as restricting calls to ptrace (a system call).
     *
     * @param context This is the context.
     * @exception IOException
     * @exception eu.chainfire.libsuperuser.Shell.ShellDiedException
     **/

    public static void disableSeLinux(Context context){
        try {
            Runtime.getRuntime().exec("su");
            Shell.Pool.SU.run("setenforce 0");
        } catch (IOException | Shell.ShellDiedException e) {
            e.printStackTrace();
        }
    }


    /**
     * This method is used to get the process id of a running application.
     *
     * @param pkg The package name of target application whose process id is to get.
     * @return int process id or -1 if process doesn't exists
     * @exception eu.chainfire.libsuperuser.Shell.ShellDiedException
     */

    public static int GetProcessID(String pkg) {

        try {

            ArrayList arrayList             = new ArrayList();
            Shell.PoolWrapper poolWrapper   = Shell.Pool.SU;
            poolWrapper.run("(toolbox ps; toolbox ps -A; toybox ps; toybox ps -A) | grep \" " + pkg + "$\"", arrayList, null, false);
            Iterator iterator               = arrayList.iterator();

            while (iterator.hasNext()) {

                String Trim = ((String) iterator.next()).trim();
                while (Trim.contains("  "))
                    Trim = Trim.replace("  ", " ");

                String[] Split = Trim.split(" ");
                if (Split.length >= 2)
                    return Integer.parseInt(Split[1]);
            }
            return -1;

        } catch (Shell.ShellDiedException e) {
            e.printStackTrace();
            return -1;
        }
    }

    /** By using ZipFile class, we can open the apk as a ZipFile and extract individual files */
    //  The output destination is /data/data/package-name/cache which is readily accessible
    public static void CopyAPKContentToCache(Context context, String fileAbsolutePathInApk, String outputFileName ){

        try{

            String      apkPath         = context.getPackageCodePath( );
            ZipFile     zipFile         = new ZipFile(apkPath);
            ZipEntry    zipEntry        = zipFile.getEntry(fileAbsolutePathInApk);
            InputStream inputStream     = zipFile.getInputStream(zipEntry);

            String newFileName          = "/data/data/" + context.getPackageName() + "/cache/" + outputFileName;
            OutputStream outputStream   = new FileOutputStream(newFileName);

            byte[] buffer   = new byte[1024];
            int length      = inputStream.read(buffer);
            while ( length > 0) {
                outputStream.write(buffer, 0, length);
                length      = inputStream.read(buffer);
            }

            outputStream.flush();
            inputStream.close();
            outputStream.close();

        }catch (Exception e){
            e.printStackTrace();
        }
    }


    public static boolean inject(Context context){

        /* Get the process id (PID) of target */
        int pid = Utils.GetProcessID(targetPackage);
        /* If the process doesn't have a PID i.e (PID < 0) that means it's not running */
        if ( pid < 0 ){
            Toast.makeText(context,targetPackage+" is not running", Toast.LENGTH_SHORT).show();
            return false;
        }

        /* Copy injector & payload into /data/data/package-name/cache */
        Utils.CopyAPKContentToCache(context, "lib/armeabi-v7a/"+ injector  , injector );
        Utils.CopyAPKContentToCache(context, "lib/armeabi-v7a/"+ payload   , payload  );

        /* Due to Android Linker Namespace Restriction, we need to execute injector & link payload
           from a whitelisted partition such as /data with appropriate permission */
        try {
            Shell.Pool.SU.run("cp "+    "/data/data/"+context.getPackageName()+"/cache/"+injector+  " /data/local" );
            Shell.Pool.SU.run("rm "+    "/data/data/"+context.getPackageName()+"/cache/"+injector  );
            Shell.Pool.SU.run("chmod "+  "777 "+  "/data/local/"+injector );

            Shell.Pool.SU.run("cp "+   "/data/data/"+context.getPackageName()+"/cache/"+payload+  " /data/local");
            Shell.Pool.SU.run("rm "+   "/data/data/"+context.getPackageName()+"/cache/"+payload );
            Shell.Pool.SU.run("chmod "+  "777 "+  "/data/local/"+payload );

        } catch (Shell.ShellDiedException e) {
            e.printStackTrace();
            return false;
        }


        /* Note: Injector must be executed with root permission
           Template: ./data/local/injector.so -p [Target Process PID] -so [Payload Path] [Password]
           Example:  ./injector.so -p 9468 -so /data/local/libpayload.so injector
           */
        try {

            List<String> STDOUT = new ArrayList<>();
            String injectCommand = String.format("./data/local/%s -p %d -so %s",injector, pid, "/data/local/"+payload );
            Shell.Pool.SU.run( injectCommand, STDOUT, null, false);

            /* Log the output of the performed command i.e injection */
            for ( String line: STDOUT) Log.d("Debug Injector", ""+ line);

            /* Reading the last line of STDOUT */
            if ( STDOUT.get( STDOUT.size() - 1 ).equals("[+] Finish Inject") ){
                if ( StartClientNative(context) ==  0){
                    return true;
                }
            }

            return false;

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }

    }

}
