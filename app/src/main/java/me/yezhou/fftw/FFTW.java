package me.yezhou.fftw;

/**
 * Created by yezhou on 2017/5/4.
 */
public class FFTW {

    public static native String fftwInit();
    public static native double fftwDft1d();
    public static native double fftwDftR2c1d();
    public static native double fftwfDftR2c1d();
    public static native double fftwfDftR2c1dThread();
    public static native double fftwfDftR2c1dThreadMeasure();
    public static native double fftwDft2d();
    public static native double fftwDftR2c2d();
    public static native double fftwfDftR2c2d();
    public static native double fftwfDftR2c2dThread();
    public static native double fftwfDftR2c2dThreadMeasure();

    static{
        System.loadLibrary("FFTW");
    }

}
