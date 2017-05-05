package me.yezhou.fftw;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final String TAG = "yezhou";
    private Button btnFftwInit;
    private Button btnFftwDft1d;
    private Button btnFftwDftR2c1d;
    private Button btnFftwfDftR2c1d;
    private Button btnFftwfDftR2c1dThread;
    private Button btnFftwfDftR2c1dThreadMeasure;
    private Button btnFftwDft2d;
    private Button btnFftwDftR2c2d;
    private Button btnFftwfDftR2c2d;
    private Button btnFftwfDftR2c2dThread;
    private Button btnFftwfDftR2c2dThreadMeasure;
    private TextView tvRuntimeResult;

    private static final int LOOP_SIZE = 12;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnFftwInit = (Button) findViewById(R.id.btn_fftw_init);
        btnFftwDft1d = (Button) findViewById(R.id.btn_fftw_dft_1d);
        btnFftwDftR2c1d = (Button) findViewById(R.id.btn_fftw_dft_r2c_1d);
        btnFftwfDftR2c1d = (Button) findViewById(R.id.btn_fftwf_dft_r2c_1d);
        btnFftwfDftR2c1dThread = (Button) findViewById(R.id.btn_fftwf_dft_r2c_1d_thread);
        btnFftwfDftR2c1dThreadMeasure = (Button) findViewById(R.id.btn_fftwf_dft_r2c_1d_thread_measure);
        btnFftwDft2d = (Button) findViewById(R.id.btn_fftw_dft_2d);
        btnFftwDftR2c2d = (Button) findViewById(R.id.btn_fftw_dft_r2c_2d);
        btnFftwfDftR2c2d = (Button) findViewById(R.id.btn_fftwf_dft_r2c_2d);
        btnFftwfDftR2c2dThread = (Button) findViewById(R.id.btn_fftwf_dft_r2c_2d_thread);
        btnFftwfDftR2c2dThreadMeasure = (Button) findViewById(R.id.btn_fftwf_dft_r2c_2d_thread_measure);
        tvRuntimeResult = (TextView) findViewById(R.id.tv_runtime_result);

        btnFftwInit.setOnClickListener(this);
        btnFftwDft1d.setOnClickListener(this);
        btnFftwDftR2c1d.setOnClickListener(this);
        btnFftwfDftR2c1d.setOnClickListener(this);
        btnFftwfDftR2c1dThread.setOnClickListener(this);
        btnFftwfDftR2c1dThreadMeasure.setOnClickListener(this);
        btnFftwDft2d.setOnClickListener(this);
        btnFftwDftR2c2d.setOnClickListener(this);
        btnFftwfDftR2c2d.setOnClickListener(this);
        btnFftwfDftR2c2dThread.setOnClickListener(this);
        btnFftwfDftR2c2dThreadMeasure.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        if (view.equals(btnFftwInit)) {
            mHandler.obtainMessage(MSG_ID_DFT_INIT).sendToTarget();
        } else if (view.equals(btnFftwDft1d)) {
            mHandler.obtainMessage(MSG_ID_DFT_1D).sendToTarget();
        } else if (view.equals(btnFftwDftR2c1d)) {
            mHandler.obtainMessage(MSG_ID_DFT_R2C_1D).sendToTarget();
        } else if(view.equals(btnFftwfDftR2c1d)) {
            mHandler.obtainMessage(MSG_ID_F_DFT_R2C_1D).sendToTarget();
        } else if(view.equals(btnFftwfDftR2c1dThread)) {
            mHandler.obtainMessage(MSG_ID_F_DFT_R2C_1D_THREAD).sendToTarget();
        } else if(view.equals(btnFftwfDftR2c1dThreadMeasure)) {
            mHandler.obtainMessage(MSG_ID_F_DFT_R2C_1D_THREAD_MEASURE).sendToTarget();
        } else if (view.equals(btnFftwDft2d)) {
            mHandler.obtainMessage(MSG_ID_DFT_2D).sendToTarget();
        } else if(view.equals(btnFftwDftR2c2d)) {
            mHandler.obtainMessage(MSG_ID_DFT_R2C_2D).sendToTarget();
        } else if(view.equals(btnFftwfDftR2c2d)) {
            mHandler.obtainMessage(MSG_ID_F_DFT_R2C_2D).sendToTarget();
        } else if(view.equals(btnFftwfDftR2c2dThread)) {
            mHandler.obtainMessage(MSG_ID_F_DFT_R2C_2D_THREAD).sendToTarget();
        } else if(view.equals(btnFftwfDftR2c2dThreadMeasure)) {
            mHandler.obtainMessage(MSG_ID_F_DFT_R2C_2D_THREAD_MEASURE).sendToTarget();
        }
    }

    private static final int MSG_ID_UDPATE_RESULT = 0;
    private static final int MSG_ID_DFT_INIT = 1;
    private static final int MSG_ID_DFT_1D = 11;
    private static final int MSG_ID_DFT_R2C_1D = 12;
    private static final int MSG_ID_F_DFT_R2C_1D = 13;
    private static final int MSG_ID_F_DFT_R2C_1D_THREAD = 14;
    private static final int MSG_ID_F_DFT_R2C_1D_THREAD_MEASURE = 15;
    private static final int MSG_ID_DFT_2D = 21;
    private static final int MSG_ID_DFT_R2C_2D = 22;
    private static final int MSG_ID_F_DFT_R2C_2D = 23;
    private static final int MSG_ID_F_DFT_R2C_2D_THREAD = 24;
    private static final int MSG_ID_F_DFT_R2C_2D_THREAD_MEASURE = 25;

    private Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch(msg.what){
                case MSG_ID_UDPATE_RESULT:
                    double result = (double) msg.obj;
                    tvRuntimeResult.append("运行时长: " + result + " ms\n");
                    break;
                case MSG_ID_DFT_INIT:
                case MSG_ID_DFT_1D:
                case MSG_ID_DFT_R2C_1D:
                case MSG_ID_F_DFT_R2C_1D:
                case MSG_ID_F_DFT_R2C_1D_THREAD:
                case MSG_ID_F_DFT_R2C_1D_THREAD_MEASURE:
                case MSG_ID_DFT_2D:
                case MSG_ID_DFT_R2C_2D:
                case MSG_ID_F_DFT_R2C_2D:
                case MSG_ID_F_DFT_R2C_2D_THREAD:
                case MSG_ID_F_DFT_R2C_2D_THREAD_MEASURE:
                    tvRuntimeResult.setText("");
                    new FftwThread(this,msg.what).start();
                    break;
            }
        };
    };

    class FftwThread extends Thread {
        private Handler handler;
        private int what;

        public FftwThread(Handler mHandler, int what) {
            this.handler = mHandler;
            this.what = what;
        }

        @Override
        public void run() {
            double result = 0.0;
            for (int i=0; i < LOOP_SIZE; i++) {
                switch(what){
                    case MSG_ID_DFT_INIT:
                        FFTW.fftwInit();
                        break;
                    case MSG_ID_DFT_1D:
                        result = FFTW.fftwDft1d();
                        break;
                    case MSG_ID_DFT_R2C_1D:
                        result = FFTW.fftwDftR2c1d();
                        break;
                    case MSG_ID_F_DFT_R2C_1D:
                        result = FFTW.fftwfDftR2c1d();
                        break;
                    case MSG_ID_F_DFT_R2C_1D_THREAD:
                        result = FFTW.fftwfDftR2c1dThread();
                        break;
                    case MSG_ID_F_DFT_R2C_1D_THREAD_MEASURE:
                        result = FFTW.fftwfDftR2c1dThreadMeasure();
                        break;
                    case MSG_ID_DFT_2D:
                        result = FFTW.fftwDft2d();
                        break;
                    case MSG_ID_DFT_R2C_2D:
                        result = FFTW.fftwDftR2c2d();
                        break;
                    case MSG_ID_F_DFT_R2C_2D:
                        result = FFTW.fftwfDftR2c2d();
                        break;
                    case MSG_ID_F_DFT_R2C_2D_THREAD:
                        result = FFTW.fftwfDftR2c2dThread();
                        break;
                    case MSG_ID_F_DFT_R2C_2D_THREAD_MEASURE:
                        result = FFTW.fftwfDftR2c2dThreadMeasure();
                        break;
                }
                handler.obtainMessage(MSG_ID_UDPATE_RESULT, result).sendToTarget();
            }
        }
    }
}
