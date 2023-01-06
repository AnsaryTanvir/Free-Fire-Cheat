package gamingbd.pro;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.IBinder;
import android.util.Base64;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import static android.view.ViewGroup.LayoutParams.*;
import static gamingbd.pro.Native.*;

public class FloatingViewService extends Service{

    /* ESP */
    public WindowManager    EspWindow;
    public ESP              esp;

    /* Window is the root of everything that floats on screen */
    public WindowManager    Window;

    /* We have a Frame in the Window that will float */
    public FrameLayout      MainFrame;

    /*We have a Main Layout in the Frame */
    public RelativeLayout   MainLayout;

    /* Main Layout contains Collapsed View (ICON) & Expanded View (Title+Menu+Buttons) */
    public RelativeLayout   collapsedView;
    public LinearLayout     expandedView;

    /* Collapsed View contains only the floating icon */
    public ImageView        Icon;

    /* Expanded View contains Title + Menu + Buttons */
    public TextView         Title;
    public ScrollView       Menu;
    public RelativeLayout   Buttons;

    /* Menu Contains Features */
    public LinearLayout     Features;

    /* Buttons contain Inject Button & Close Button */
    public Button           InjectButton, CloseButton;

    /* LayoutParameters is used to change the position of the Window (Whole Floating Stuffs) */
    public WindowManager.LayoutParams LayoutParameters;

    /* Floating icon inside the Collapsed View. The icon image is stored in Base64 encoded format */
    public String iconString = IconNative();

    /** This is to stop adding widgets in menu multiple times**/
    public boolean WidgetsAddedInMenu = false;


    /*** This class (C/C++ Enumeration Alternative) must match with ClientServerCommon.h ****/
    public static class FeatureMappedWithInteger{
        public static final int AIMBOT          =  1;
        public static final int AIM_FOV         =  2;
        public static final int AIM_DISTANCE    =  3;
        public static final int ESP             =  4;
        public static final int JUMP_HEIGHT     =  5;
        public static final int NO_RECOIL       =  6;
        public static final int SPEED_TIME      =  7;
        public static final int DYNAMIC_SPEED   =  8;

    };


    /* This method is called when the service is created */
    @Override
    public void onCreate() {
        super.onCreate();

        esp = new ESP(this);
        EspWindow = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        DrawCanvas();

        StartFloat();
    }

    private void DrawCanvas() {
        WindowManager.LayoutParams EspLayoutParameters = new WindowManager.LayoutParams(WindowManager.LayoutParams.MATCH_PARENT, WindowManager.LayoutParams.MATCH_PARENT, getLayoutType(), WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE, PixelFormat.TRANSLUCENT);
        EspLayoutParameters.gravity = Gravity.TOP | Gravity.START;
        EspLayoutParameters.x       = 0;
        EspLayoutParameters.y       = 100;
        EspWindow.addView(esp, EspLayoutParameters);
    }

    private int getLayoutType() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            return  WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            return  WindowManager.LayoutParams.TYPE_PHONE;
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            return  WindowManager.LayoutParams.TYPE_TOAST;
        } else {
            return  WindowManager.LayoutParams.TYPE_SYSTEM_ALERT;
        }
    }

    private void StartFloat() {

        /* Layout Scheme :

            Window [Window] {
                Main Frame [FrameLayout] {
                    Main Layout [RelativeLayout] {
                        Collapsed View [RelativeLayout]{
                            Icon [ImageView]
                        }
                        Expanded  View [LinearLayout]{
                            Title [TextView]
                            Menu  [ScrollView]{
                                Features [LinearLayout]{
                                    Switches [Widget]
                                    SeekBars [Widget]
                                }
                            }
                            Buttons [RelativeLayout]{
                                InjectButton [Button]
                                CloseButton  [Button]
                            }
                        }
                    }
                }
            }

         */


        /** Main Frame [FrameLayout] **/
        {
            /* Frame holds the entire floating view */
            MainFrame = new FrameLayout(this);
            MainFrame.setLayoutParams(new FrameLayout.LayoutParams(MATCH_PARENT, MATCH_PARENT));

            /** Main Layout [RelativeLayout] */
            {
                /* Creating the Main Layout inside the Frame */
                /* MainLayout contains the collapsed view (ICON) & the expanded view (MENU) */
                MainLayout = (new RelativeLayout(this));
                MainLayout.setLayoutParams(new FrameLayout.LayoutParams(WRAP_CONTENT, WRAP_CONTENT));

                /** Collapsed View [RelativeLayout] */
                {
                    /*---------------------- (Collapsed View) or (Floating Icon View) */
                    /* When we close/collapse the floating menu this collapsedView will be shown */
                    /* Initially the floating view should only show the icon [collapsed view] */
                    collapsedView = new RelativeLayout(this);
                    collapsedView.setLayoutParams(new RelativeLayout.LayoutParams(WRAP_CONTENT, WRAP_CONTENT));
                    collapsedView.setVisibility(View.VISIBLE);

                    /* Icon [ImageView] */
                    {
                        /* In the collapsed view there will be only an image as icon */
                        Icon = new ImageView(this);
                        Icon.setLayoutParams(new RelativeLayout.LayoutParams(WRAP_CONTENT, WRAP_CONTENT));
                        /* Icon size 50 dp */
                        int applyDimension = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, (float) 50, getResources().getDisplayMetrics());
                        Icon.getLayoutParams().height = applyDimension;
                        Icon.getLayoutParams().width  = applyDimension;
                        Icon.setScaleType(ImageView.ScaleType.FIT_XY);
                        byte[] decode = Base64.decode( iconString, 0);
                        Icon.setImageBitmap(BitmapFactory.decodeByteArray(decode, 0, decode.length));

                        Icon.setOnClickListener(new View.OnClickListener() {
                            public void onClick(View view) {
                                /* Hide icon & show expanded view */
                                collapsedView.setVisibility(View.GONE);
                                expandedView.setVisibility(View.VISIBLE);
                            }
                        });
                    }
                }

                /** Expanded  View [LinearLayout] */
                {
                    /* Initially the expanded view will be hidden */
                    expandedView = new LinearLayout(this);
                    expandedView.setVisibility(View.GONE);
                    expandedView.setOrientation(LinearLayout.VERTICAL);
                    /** Expanded View Width 400 dp **/
                    expandedView.setLayoutParams(new LinearLayout.LayoutParams(pixelToDp(400), WRAP_CONTENT));

                    {
                        /** Title [TextView] */
                        {
                            Title = new TextView(this);
                            Title.setText("gamingbd.pro");
                            Title.setTextColor(Color.WHITE);
                            Title.setTextSize(18);
                            Title.setGravity(Gravity.CENTER);
                            Title.setTypeface(null, Typeface.BOLD);
                            Title.setPadding(0, 15, 0, 15);
                            Title.setBackgroundColor(Color.parseColor("#3A833A"));
                        }

                        /** Menu [ScrollView] */
                        {
                            Menu = new ScrollView(this);
                            /** Menu height 200 dp **/
                            Menu.setLayoutParams(new LinearLayout.LayoutParams(MATCH_PARENT, pixelToDp(200)));
                            Menu.setPadding(pixelToDp(5), pixelToDp(5), pixelToDp(5), pixelToDp(5));
                            Menu.setBackgroundColor(Color.BLACK);
                            GradientDrawable gradientDrawable = new GradientDrawable();
                            gradientDrawable.setColor(Color.BLACK);
                            gradientDrawable.setCornerRadius(0);
                            /** Semi Transparent, Alpha Range: 0-255 **/
                            gradientDrawable.setAlpha(128);
                            Menu.setBackground(gradientDrawable);

                            /** Features [LinearLayout] */
                            {
                                /* The widgets on the FeatureNumber will be added in a separate code */
                                Features = new LinearLayout(this);
                                Features.setLayoutParams(new LinearLayout.LayoutParams(MATCH_PARENT, MATCH_PARENT));
                                Features.setPadding(0, 10,0,10);
                                Features.setOrientation(LinearLayout.VERTICAL);
                            }
                        }

                        /** Buttons [RelativeLayout]  */
                        {
                            Buttons = new RelativeLayout(this);
                            Buttons.setPadding(5, 15, 5, 15);
                            Buttons.setLayoutParams(new RelativeLayout.LayoutParams(WRAP_CONTENT, WRAP_CONTENT));
                            Buttons.setVerticalGravity(Gravity.CENTER);
                            Buttons.setBackgroundColor(Color.BLACK);

                            /** InjectButton [Button] **/
                            {
                                InjectButton = new Button(this);
                                InjectButton.setText("Inject");
                                InjectButton.setAllCaps(false);
                                InjectButton.setTextColor(Color.parseColor("#8C8D92"));
                                InjectButton.setTypeface(null, Typeface.BOLD);
                                InjectButton.setTextSize(14);
                                /* Button Height 40 dp */
                                InjectButton.setLayoutParams(new RelativeLayout.LayoutParams(WRAP_CONTENT, pixelToDp(40)));

                                GradientDrawable gradientDrawable = new GradientDrawable();
                                gradientDrawable.setColor(Color.parseColor("#3A833A"));
                                gradientDrawable.setCornerRadius(100);
                                InjectButton.setBackground(gradientDrawable);
                                InjectButton.setTextColor(Color.WHITE);

                                InjectButton.setOnClickListener(new View.OnClickListener() {
                                    @Override public void onClick(View view) {
                                        boolean injected = Utils.inject(getApplicationContext());
                                        if ( injected ){
                                            if ( !WidgetsAddedInMenu ){
                                                /* Add features in menu */
                                                WidgetsAddedInMenu = true;
                                                AddFeaturesInMenu();
                                                InjectButton.setVisibility(View.INVISIBLE);
                                            }
                                        }
                                    }
                                });
                            }

                            /** CloseButton  [Button] **/
                            {
                                CloseButton = new Button(this);
                                CloseButton.setText("Close");
                                CloseButton.setAllCaps(false);
                                CloseButton.setTextColor(Color.parseColor("#8C8D92"));
                                CloseButton.setTypeface(null, Typeface.BOLD);
                                CloseButton.setTextSize(14);

                                /* Button Height 40 dp */
                                RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(WRAP_CONTENT, pixelToDp(40));
                                layoutParams.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);
                                CloseButton.setLayoutParams(layoutParams);

                                GradientDrawable gradientDrawable = new GradientDrawable();
                                gradientDrawable.setColor(Color.parseColor("#D4403A"));
                                gradientDrawable.setCornerRadius(100);
                                CloseButton.setBackground(gradientDrawable);
                                CloseButton.setTextColor(Color.WHITE);

                                CloseButton.setOnClickListener(new View.OnClickListener() {
                                    @Override public void onClick(View view) {
                                        /** Hide expanded view & Show collapsed view (icon) **/
                                        collapsedView.setVisibility(View.VISIBLE);
                                        expandedView.setVisibility(View.GONE);
                                    }
                                });
                            }
                        }
                    }
                }
            }
        }

        /* Lets add components to the layout */

        /** Main Frame [FrameLayout] */
        {
            /* Adding Main Layout to the Frame */
            MainFrame.addView(MainLayout);

            /** Main Layout [RelativeLayout] */
            {
                /* Adding Collapsed View(ICON), Expanded View ( Title + Menu + Bottom Buttons ) to Main Layout */
                MainLayout.addView(collapsedView);
                MainLayout.addView(expandedView);

                /** Collapsed View [RelativeLayout] */
                {
                    /* Adding ICON in Collapsed View */
                    collapsedView.addView(Icon);
                }

                /** Expanded  View [LinearLayout] */
                {
                    /* Adding Title in Expanded View ( Title + Menu + Bottom Buttons ) */
                    expandedView.addView(Title);
                    expandedView.addView(Menu);
                    expandedView.addView(Buttons);

                    /** Menu [ScrollView] */
                    {
                        /* Adding Menu in Scroll View of Expanded View */
                        Menu.addView(Features);
                    }

                    /** Buttons [RelativeLayout]  */
                    {
                        /* Adding Inject/Close Button */
                        Buttons.addView(InjectButton);
                        Buttons.addView(CloseButton);
                    }

                }
            }
        }



        Window                   =   (WindowManager) getSystemService(WINDOW_SERVICE);
        LayoutParameters         =   new WindowManager.LayoutParams(WRAP_CONTENT, WRAP_CONTENT, Build.VERSION.SDK_INT >= Build.VERSION_CODES.O ? 2038 : 2002, 8, -3);
        LayoutParameters.gravity =   Gravity.TOP | Gravity.LEFT;
        LayoutParameters.x       =   0;
        LayoutParameters.y       =   100;
        Window.addView(MainFrame, LayoutParameters);
        MainFrame.setOnTouchListener(onTouchListener());
        Icon.setOnTouchListener(onTouchListener());
    }

    private void AddFeaturesInMenu() {

        addSwitch("Aimbot", new InterfaceBool() {
            public void OnWrite(Switch aSwitch, boolean isChecked) {
                /** Send the updated Switch status to the client for sending it to the server */
                UpdateFeatureNative( FeatureMappedWithInteger.AIMBOT, (isChecked? 1:0)  );
                /* Update Switch Text Color */
                if ( isChecked )    aSwitch.setTextColor(Color.WHITE);
                else                aSwitch.setTextColor(Color.GRAY);
            }
        });


        addSeekbar("Aim Fov: ", 0, 360, 360, new InterfaceInt() {
            public void OnWrite( TextView seekBarTopText, int seekBarValue) {

                /** Send the updated SeekBar value to the client for sending it to the server */
                UpdateFeatureNative(FeatureMappedWithInteger.AIM_FOV, seekBarValue);
                /* Update Seek Text */
                seekBarTopText.setText("Aim Fov: "+seekBarValue+" degree");
                if ( seekBarValue == 0 ){
                    seekBarTopText.setText("Aim Fov: Default");
                    seekBarTopText.setTextColor(Color.GRAY);
                    return;
                }
                seekBarTopText.setTextColor(Color.WHITE);
                return;
            }
        });

        addSeekbar("Aim Distance: ", 0, 180, 180, new InterfaceInt() {
            public void OnWrite( TextView seekBarTopText, int seekBarValue) {

                /** Send the updated SeekBar value to the client for sending it to the server */
                UpdateFeatureNative(FeatureMappedWithInteger.AIM_DISTANCE, seekBarValue);
                /* Update Seek Text */
                seekBarTopText.setText("Aim Distance: "+seekBarValue+" m");

                if ( seekBarValue == 0 ){
                    seekBarTopText.setText("Aim Distance: Default");
                    seekBarTopText.setTextColor(Color.GRAY);
                    return;
                }
                seekBarTopText.setTextColor(Color.WHITE);
                return;
            }
        });

        addSwitch("ESP", new InterfaceBool() {
            public void OnWrite(Switch aSwitch, boolean isChecked) {
                /** Send the updated Switch status to the client for sending it to the server */
                UpdateFeatureNative( FeatureMappedWithInteger.ESP, (isChecked? 1:0)  );
                /* Update Switch Text Color */
                if ( isChecked )    aSwitch.setTextColor(Color.WHITE);
                else                aSwitch.setTextColor(Color.GRAY);
            }
        });


        addSeekbar("Jump Height", 0, 4, 0, new InterfaceInt() {
            public void OnWrite( TextView seekBarTopText, int seekBarValue) {

                /** Send the updated SeekBar value to the client for sending it to the server */
                UpdateFeatureNative(FeatureMappedWithInteger.JUMP_HEIGHT, seekBarValue);
                /* Update Seek Text */
                seekBarTopText.setText("Jump Height: "+seekBarValue);
                if ( seekBarValue == 0 ){
                    seekBarTopText.setText("Jump Height: OFF");
                    seekBarTopText.setTextColor(Color.GRAY);
                    return;
                }
                seekBarTopText.setTextColor(Color.WHITE);
                return;
            }
        });

//        addSwitch("NO Recoil", new InterfaceBool() {
//            public void OnWrite(Switch aSwitch, boolean isChecked) {
//                /** Send the updated Switch status to the client for sending it to the server */
//                UpdateFeatureNative( FeatureMappedWithInteger.NO_RECOIL, (isChecked? 1:0)  );
//                /* Update Switch Text Color */
//                if ( isChecked )    aSwitch.setTextColor(Color.WHITE);
//                else                aSwitch.setTextColor(Color.GRAY);
//            }
//        });


        addSeekbar("Speed Time", 0, 100, 0, new InterfaceInt() {
            public void OnWrite( TextView seekBarTopText, int seekBarValue) {

                /** Send the updated SeekBar value to the client for sending it to the server */
                UpdateFeatureNative(FeatureMappedWithInteger.SPEED_TIME, seekBarValue);
                /* Update Seek Text */
                seekBarTopText.setText("Speed Time: "+seekBarValue+"x");
                if ( seekBarValue == 0 ){
                    seekBarTopText.setText("Speed Time: OFF");
                    seekBarTopText.setTextColor(Color.GRAY);
                    return;
                }
                seekBarTopText.setTextColor(Color.WHITE);
                return;
            }
        });

//        addSwitch("Dynamic Speed", new InterfaceBool() {
//            public void OnWrite(Switch aSwitch, boolean isChecked) {
//                /** Send the updated Switch status to the client for sending it to the server */
//                UpdateFeatureNative( FeatureMappedWithInteger.DYNAMIC_SPEED, (isChecked? 1:0)  );
//                /* Update Switch Text Color */
//                if ( isChecked )    aSwitch.setTextColor(Color.WHITE);
//                else                aSwitch.setTextColor(Color.GRAY);
//            }
//        });


    }

    /**------------------------------------------------------------------------------------------**/
    /**-------------------------Method to add Switch --------------------------------------------**/
    public void addSwitch(String switchName, InterfaceBool interfaceBool) {

        final Switch aSwitch = new Switch(this);
        aSwitch.setText(switchName);
        aSwitch.setTextSize(17);
        aSwitch.setTextColor(Color.GRAY);
        aSwitch.setTypeface(null, Typeface.BOLD);
        aSwitch.setPadding(30, 10, 25, 10);

        aSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                interfaceBool.OnWrite( aSwitch, isChecked);
            }
        });
        Features.addView(aSwitch);
    }
    public interface InterfaceBool {
        void OnWrite(Switch aSwitch, boolean isChecked);
    }
    /*-------------------------Method to add Switch ---------------------------------------------*/
    /*-------------------------------------------------------------------------------------------*/


    /**------------------------------------------------------------------------------------------**/
    /**-------------------------Method to add SeekBar -------------------------------------------**/
    private void addSeekbar(String seekBarName, int min, int max, int initialSeekValue,  InterfaceInt interInt) {

        TextView seekBarTopText = new TextView(this);
        seekBarTopText.setText(seekBarName + " : OFF");
        seekBarTopText.setTextSize(16);
        seekBarTopText.setTypeface(null, Typeface.BOLD);
        seekBarTopText.setTextColor(Color.GRAY);
        seekBarTopText.setPadding(25, 20, 25, 20);

        SeekBar seekBar = new SeekBar(this);
        seekBar.setMax(max);
        seekBar.setProgress(initialSeekValue);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onStartTrackingTouch( SeekBar seekBar) {}
            public void onStopTrackingTouch( SeekBar seekBar) {}
            public void onProgressChanged( SeekBar seekBar, int i, boolean z) {
                seekBar.setProgress(i);
                interInt.OnWrite( seekBarTopText, i);
            }
        });

        {
            if ( seekBarName.contains("Aim Fov:") || seekBarName.contains("Aim Distance:") ){
                seekBarTopText.setText(seekBarName + ""+initialSeekValue);
            }
        }


        /** Add TextView & SeekBar */
        Features.addView(seekBarTopText);
        Features.addView(seekBar);
    }

    private interface InterfaceInt {
        void OnWrite( TextView seekBarTopText, int seekBarValue);
    }
    /*-------------------------Method to add SeekBar --------------------------------------------*/
    /*--------------------------------------------------------------------------------------------*/


    /** Handle Touch Event */
    public View.OnTouchListener onTouchListener() {

        return new View.OnTouchListener() {

            final View collapsedView    = FloatingViewService.this.collapsedView;
            final View expandedView     = FloatingViewService.this.expandedView;

            float   initialTouchX;
            float   initialTouchY;
            int     initialX;
            int     initialY;

            public boolean onTouch(View view, MotionEvent motionEvent) {
                switch (motionEvent.getAction()) {

                    case MotionEvent.ACTION_DOWN:
                        initialX        = LayoutParameters.x;
                        initialY        = LayoutParameters.y;
                        initialTouchX   = motionEvent.getRawX();
                        initialTouchY   = motionEvent.getRawY();
                        return true;

                    case MotionEvent.ACTION_UP:

                        int rawX = (int) (motionEvent.getRawX() - initialTouchX);
                        int rawY = (int) (motionEvent.getRawY() - initialTouchY);

                        if ( rawX < 10 && rawY < 10 && isViewCollapsed() ){
                            try {
                                collapsedView.setVisibility(View.GONE);
                                expandedView.setVisibility(View.VISIBLE);
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                        }

                        /* Make Layout Less Transparent If Dragging Stops */
                        {
                            GradientDrawable gradientDrawable = new GradientDrawable();
                            gradientDrawable.setColor(Color.BLACK);
                            gradientDrawable.setAlpha(200);         // Alpha [0 -> 255] = More Dark
                            Menu.setBackground(gradientDrawable);
                        }

                        return true;


                    case MotionEvent.ACTION_MOVE:

                        LayoutParameters.x = initialX + ((int) (motionEvent.getRawX() - initialTouchX));
                        LayoutParameters.y = initialY + ((int) (motionEvent.getRawY() - initialTouchY));
                        Window.updateViewLayout(MainFrame, LayoutParameters);

                        /** Make Layout More Transparent While Dragging **/
                        {
                            GradientDrawable gradientDrawable   = new GradientDrawable();
                            gradientDrawable.setColor(Color.BLACK);
                            gradientDrawable.setAlpha(100);         // Alpha [0 -> 255] = More Dark
                            Menu.setBackground(gradientDrawable);
                        }
                        return true;


                    default:
                        return false;
                }
            }
        };
    }

    /* Check if view is collapsed or expanded */
    public boolean isViewCollapsed() {
        return MainFrame == null || collapsedView.getVisibility() == View.VISIBLE;
    }

    /* Convert dp to pixel */
    public int pixelToDp(int i) {
        return (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, (float) i, getResources().getDisplayMetrics());
    }

    /* Interface(s) */
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }


}



