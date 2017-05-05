#include <jni.h>
#include <android/log.h>
#include <sys/time.h>
#include "fftw3.h"
#include "me_yezhou_fftw_FFTW.h"

#define LOG_TAG	"yezhou"
#undef LOG
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)

#define SIZE 160 //SIZE x SIZE , default: 160 x 160
#define N 4096

int init_in_fftw_complex(fftw_complex* in) {
	int i,j,index;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			index = j + i * SIZE;
			in[index][0] = index + 1;
			in[index][1] = 0;
		}
	}
	return 0;
}

int init_in_fftw_complex_1d(fftw_complex* in) {
	int i;
	for (i = 0; i < N; i++) {
		in[i][0] = N + 1;
		in[i][1] = 0;
	}
	return 0;
}

int init_in_fftwf_float(float* in) {
	int i,j,index;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			index = j + i * SIZE;
			in[index] = (float)(index + 1);
		}
	}
	return 0;
}

int init_in_fftwf_float_1d(float* in) {
	int i;
	for (i = 0; i < N; i++) {
		in[i] = (float)(i + 1);
	}
	return 0;
}

static double now_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000. + tv.tv_usec/1000.;
}

JNIEXPORT jstring JNICALL Java_me_yezhou_fftw_FFTW_fftwInit(JNIEnv * env, jclass jcls) {
	LOGD("btn_fftw_init()");

	return (*env)->NewStringUTF(env, "btn_fftw_init");
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwDft1d(JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

	init_in_fftw_complex_1d(in);

    //fftw_plan fftw_plan_dft_1d(int n0, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftw_dft_1d() costs time %f ms", t_span);

	//return (*env)->NewStringUTF(env, "fftw_dft_1d");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwDft2d(JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE * SIZE);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE * SIZE);

	init_in_fftw_complex(in);

	p = fftw_plan_dft_2d(SIZE, SIZE, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftw_dft_2d() costs time %f ms", t_span);

	//return (*env)->NewStringUTF(env, "fftw_dft_2d");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwDftR2c1d(
		JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	fftw_complex *in, *out;
	fftw_plan p;
	int NTmp = floor(N/2 +1);
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NTmp);

	init_in_fftw_complex_1d(in);

    //fftw_plan fftw_plan_dft_r2c_1d(int n0, double *in, fftw_complex *out, unsigned flags);
	p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
	fftw_execute(p);

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftw_dft_r2c_1d() costs time %f ms", t_span);

	//return (*env)->NewStringUTF(env, "fftw_dft_r2c_1d");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwDftR2c2d(
		JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	fftw_complex *in, *out;
	fftw_plan p;
	int NTmp = floor(SIZE/2 +1);
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE * SIZE);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE * NTmp);

	init_in_fftw_complex(in);

	p = fftw_plan_dft_r2c_2d(SIZE, SIZE, in, out, FFTW_ESTIMATE);
	fftw_execute(p);

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftw_dft_r2c_2d() costs time %f ms", t_span);

	//return (*env)->NewStringUTF(env, "fftw_dft_r2c_2d");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwfDftR2c1d(
		JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	float *in;
	fftwf_complex *out;
	fftwf_plan p;
	int NTmp = floor(N / 2 + 1);
	in = (float*) fftw_malloc(sizeof(float) * N);
	out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * NTmp);

	init_in_fftwf_float_1d(in);

	p = fftwf_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
	fftwf_execute(p);

	fftwf_destroy_plan(p);
	fftwf_free(in);
	fftwf_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftwf_dft_r2c_1d() costs time %f ms", t_span);

	//return (*env)->NewStringUTF(env, "fftwf_dft_r2c_1d");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwfDftR2c2d(
		JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	float *in;
	fftwf_complex *out;
	fftwf_plan p;
	int NTmp = floor(SIZE / 2 + 1);
	in = (float*) fftw_malloc(sizeof(float) * SIZE * SIZE);
	out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * SIZE * NTmp);

	init_in_fftwf_float(in);

	p = fftwf_plan_dft_r2c_2d(SIZE, SIZE, in, out, FFTW_ESTIMATE);
	fftwf_execute(p);

	fftwf_destroy_plan(p);
	fftwf_free(in);
	fftwf_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftwf_dft_r2c_2d() costs time %f ms", t_span);

	//return (*env)->NewStringUTF(env, "fftwf_dft_r2c_2d");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwfDftR2c1dThread(
		JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	int thread_ok = 0;
	int n_threads = 4;
	float *in;
	fftwf_complex *out;
	fftwf_plan p;
	int NTmp = floor(N / 2 + 1);
	in = (float*) fftw_malloc(sizeof(float) * N);
	out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * NTmp);

	init_in_fftwf_float_1d(in);

	thread_ok = fftwf_init_threads();
	if (thread_ok)
		fftwf_plan_with_nthreads(n_threads);
	p = fftwf_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
	fftwf_execute(p);

	fftwf_destroy_plan(p);
	if (thread_ok)
		fftwf_cleanup_threads();
	fftwf_free(in);
	fftwf_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftwf_dft_r2c_1d_thread() costs time %f ms. thread_ok = %d", t_span, thread_ok);

	//return (*env)->NewStringUTF(env, "fftwf_dft_r2c_1d_thread");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwfDftR2c2dThread(
		JNIEnv * env, jclass jcls) {
	double t_start, t_end, t_span;
	t_start = now_ms();

	int thread_ok = 0;
	int n_threads = 4;
	float *in;
	fftwf_complex *out;
	fftwf_plan p;
	int NTmp = floor(SIZE / 2 + 1);
	in = (float*) fftw_malloc(sizeof(float) * SIZE * SIZE);
	out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * SIZE * NTmp);

	init_in_fftwf_float(in);

	thread_ok = fftwf_init_threads();
	if(thread_ok)
		fftwf_plan_with_nthreads(n_threads);
	p = fftwf_plan_dft_r2c_2d(SIZE, SIZE, in, out, FFTW_ESTIMATE);
	fftwf_execute(p);

	fftwf_destroy_plan(p);
	if(thread_ok)
		fftwf_cleanup_threads();
	fftwf_free(in);
	fftwf_free(out);

	t_end = now_ms();
	t_span = t_end - t_start;
	LOGD("fftwf_dft_r2c_2d_thread() costs time %f ms. thread_ok = %d", t_span, thread_ok);

	//return (*env)->NewStringUTF(env, "fftwf_dft_r2c_2d_thread");
	return t_span;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwfDftR2c1dThreadMeasure(
		JNIEnv * env, jclass jcls) {
	LOGD("fftwf_dft_r2c_1d_thread_measure()");

	//return (*env)->NewStringUTF(env, "fftwf_dft_r2c_1d_thread_measure");
	return 0.0;
}

JNIEXPORT jdouble JNICALL Java_me_yezhou_fftw_FFTW_fftwfDftR2c2dThreadMeasure(
		JNIEnv * env, jclass jcls) {
	LOGD("fftwf_dft_r2c_2d_thread_measure()");

	//return (*env)->NewStringUTF(env, "fftwf_dft_r2c_2d_thread_measure");
	return 0.0;
}
