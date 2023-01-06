package gamingbd.pro;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.os.Process;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class ESP extends View implements Runnable {

    int       FPS = 60;
    long      sleepTime = (long)1000/FPS;
    Paint     StrokePaint;
    Paint     TextPaint;
    Thread    EspDrawingThread;


    public ESP(Context context) {
        super(context, (AttributeSet) null, 0);

        InitializePaints();
        setFocusableInTouchMode(false);
        setBackgroundColor(0);

        EspDrawingThread = new Thread(this);
        EspDrawingThread.start();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if ( canvas != null && getVisibility() == VISIBLE ) {
            ClearCanvas(canvas);
            if ( Native.EspEnabled() ){
                Native.DrawOn(this, canvas);
            }
        }
    }

    @Override
    public void run() {
        Process.setThreadPriority(10);
        while ( EspDrawingThread.isAlive() && !EspDrawingThread.isInterrupted() ) {
            try {
                postInvalidate();
                Thread.sleep(sleepTime);
            } catch (InterruptedException e) {
                Log.d("Debug",e.getMessage());
            }
        }
    }

    public void InitializePaints() {

        StrokePaint = new Paint();
        StrokePaint.setStyle(Paint.Style.STROKE);
        StrokePaint.setAntiAlias(true);
        StrokePaint.setColor(Color.rgb(0, 0, 0));

        TextPaint = new Paint();
        TextPaint.setAntiAlias(true);
        TextPaint.setTextAlign(Paint.Align.CENTER);
    }

    public void ClearCanvas(Canvas canvas) {
        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
    }

    public void DrawLine(Canvas canvas, int alpha, int red, int green, int blue, float lineWidth, float fromX, float fromY, float toX, float toY) {
        StrokePaint.setAlpha(alpha);
        StrokePaint.setColor(Color.rgb(red, green, blue));
        StrokePaint.setStrokeWidth(lineWidth);
        canvas.drawLine(fromX, fromY, toX, toY, StrokePaint);
    }

    public void DrawText(Canvas canvas, int alpha, int red, int green, int blue, float stroke, String text, float positionX, float posY, float textSize) {
        TextPaint.setAlpha(alpha);
        TextPaint.setColor(Color.rgb(red, green, blue));
        TextPaint.setStrokeWidth(stroke);
        if ( getRight() > 1920 || getBottom() > 1920 )
            TextPaint.setTextSize(4.0f + textSize);
        else if ( getRight() == 1920 || getBottom() == 1920 )
            TextPaint.setTextSize(textSize + 2.0f);
        else
            TextPaint.setTextSize(textSize);
        canvas.drawText(text, positionX, posY, TextPaint);
    }

}
