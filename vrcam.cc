/**
 * @file omxcv-test.cpp
 * @brief Simple testing application for omxcv.
 */
#include "vrcam.h"
#include "omxcv.h"
#include "gl_transform.h"
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#define CAMERA_DEV   "/dev/video0"
#define CAMERA_WIDTH  1920
#define CAMERA_HEIGHT 720
#define MMAP_COUNT    2
#define PICTURE_NUM   10

#define TIMEDIFF(start) (duration_cast<microseconds>(steady_clock::now() - start).count())

using omxcv::OmxCv;
using omxcv::OmxCvJpeg;
using std::this_thread::sleep_for;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::duration_cast;

using namespace openblw;

//pre procedure difinition

//structure difinition

//global variables

OmxCvJpeg encoder = OmxCvJpeg(EQUIRECTANGULAR_WIDTH,
EQUIRECTANGULAR_HEIGHT);
GLTransform transformer(EQUIRECTANGULAR_WIDTH, EQUIRECTANGULAR_HEIGHT,
CAMERA_WIDTH, CAMERA_HEIGHT);
OmxCv *recorder = NULL;

int StartRecord(const char *filename, int bitrate_kbps) {
	recorder = new OmxCv(filename, EQUIRECTANGULAR_WIDTH,
			EQUIRECTANGULAR_HEIGHT, bitrate_kbps);
	return 0;
}

int StopRecord() {
	if (recorder == NULL)
		return -1;
	delete recorder;
	recorder = NULL;
	return 0;
}

int SetRotation(float x_deg, float y_deg, float z_deg) {
	transformer.SetRotation(x_deg, y_deg, z_deg);
}

int Transform(int width, int height, int stride,
		const unsigned char *imagedata) {
	cv::Mat raw_image(height, width, CV_8UC(stride / width));
	cv::Mat vr_image(EQUIRECTANGULAR_HEIGHT, EQUIRECTANGULAR_WIDTH, CV_8UC(3));

	memcpy(raw_image.data, imagedata, stride * height);

	transformer.Transform(raw_image, vr_image);

	memcpy(imagedata, raw_image.data, 3 * EQUIRECTANGULAR_WIDTH * EQUIRECTANGULAR_HEIGHT);
}

int AddFrame(int width, int height, int stride,
		const unsigned char *imagedata) {
	if (recorder == NULL)
		return -1;

	cv::Mat vr_image(height, width, CV_8UC(stride / width));

	memcpy(vr_image.data, imagedata, stride * height);

	recorder->Encode(vr_image);
}

int SaveJpegAsEquirectangular(int width, int height, int stride,
		const unsigned char *imagedata, const char *out_filename) {

	cv::Mat vr_image(height, width, CV_8UC(stride / width));

	memcpy(vr_image.data, imagedata, stride * height);

	if (out_filename != NULL) {

		if (encoder.Encode(out_filename, vr_image)) {
		} else {
			perror("error on jpeg encode");
			return -1;
		}
	}

	return 0;
}
