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
#define CAMERA_WIDTH  1280
#define CAMERA_HEIGHT 480
#define EQUIRECTANGULAR_WIDTH  1024
#define EQUIRECTANGULAR_HEIGHT 512
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
GLTransform transformer(EQUIRECTANGULAR_WIDTH, EQUIRECTANGULAR_HEIGHT, CAMERA_WIDTH, CAMERA_HEIGHT);


int SaveJpegAsEquirectangular(int width, int height, int stride,
		const unsigned char *imagedata, const char *out_filename) {

	cv::Mat raw_image(height, width, CV_8UC(stride / width));
	cv::Mat vr_image(EQUIRECTANGULAR_HEIGHT, EQUIRECTANGULAR_WIDTH, CV_8UC(3));

	memcpy(raw_image.data, imagedata, stride * height);

	if (out_filename != NULL) {

		transformer.Transform(raw_image, vr_image);

		if (encoder.Encode(out_filename, vr_image)) {
		} else {
			perror("error on jpeg encode");
			return -1;
		}
	}

	return 0;
}
