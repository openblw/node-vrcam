/**
 * @file omxcv-test.cpp
 * @brief Simple testing application for omxcv.
 */
#include "vrcam.h"
#include "omxcv.h"
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

//pre procedure difinition

//structure difinition

//global variables

int polar_x[2] = { 640 / 2, 640 + 640 / 2 };
int polar_y[2] = { 640 / 2, 640 / 2 };
int polar_r[2] = { 660 / 2, 660 / 2 };
int convert2equirectangular(cv::Mat &src, cv::Mat &dst) {
//	int i, j;
//	for (i = 0; i < dst.rows / 2; i++) {
//		uint8_t *dst_line_head = dst.data + dst.step * i;
//		double phi_rate = 2 * (double) i / dst.rows;
//		int r = phi_rate * polar_r[0];
//		for (j = 0; j < dst.cols; j++) {
//			double theta = -M_PI * (2 * (double) j / dst.cols - 1);
//			int x = r * cos(theta) + polar_x[0];
//			int y = r * sin(theta) + polar_y[0];
//			if (x < 0 || x >= src.cols / 2 || y < 0 || y >= src.rows) {
//				dst_line_head[3 * j + 0] = 0;
//				dst_line_head[3 * j + 1] = 0;
//				dst_line_head[3 * j + 2] = 0;
//			} else {
//				uint8_t *src_line_head = src.data + src.step * y;
//				dst_line_head[3 * j + 0] = src_line_head[3 * x + 0];
//				dst_line_head[3 * j + 1] = src_line_head[3 * x + 1];
//				dst_line_head[3 * j + 2] = src_line_head[3 * x + 2];
//			}
//		}
//	}
//	for (i = 0; i < dst.rows / 2; i++) {
//		uint8_t *dst_line_head = dst.data + dst.step * (dst.rows - 1 - i);
//		double phi_rate = 2 * (double) i / dst.rows;
//		int r = phi_rate * polar_r[0];
//		for (j = 0; j < dst.cols; j++) {
//			double theta = M_PI * (2 * (double) j / dst.cols - 1) + M_PI / 2;
//			int x = r * cos(theta) + polar_x[1];
//			int y = r * sin(theta) + polar_y[1];
//			if (x < src.cols / 2 || x >= src.cols || y < 0 || y >= src.rows) {
//				dst_line_head[3 * j + 0] = 0;
//				dst_line_head[3 * j + 1] = 0;
//				dst_line_head[3 * j + 2] = 0;
//			} else {
//				uint8_t *src_line_head = src.data + src.step * y;
//				dst_line_head[3 * j + 0] = src_line_head[3 * x + 0];
//				dst_line_head[3 * j + 1] = src_line_head[3 * x + 1];
//				dst_line_head[3 * j + 2] = src_line_head[3 * x + 2];
//			}
//		}
//	}
	return 0;
}

int SaveJpegAsEquirectangular(int width, int height, int stride,
		const unsigned char *imagedata, const char *out_filename) {

	cv::Mat raw_image(height, width, CV_8UC(stride / width));
	cv::Mat vr_image(EQUIRECTANGULAR_HEIGHT, EQUIRECTANGULAR_WIDTH, CV_8UC(3));

	memcpy(raw_image.data, imagedata, stride * height);

	if (out_filename != NULL) {

		convert2equirectangular(raw_image, vr_image);

		OmxCvJpeg encoder = OmxCvJpeg(EQUIRECTANGULAR_WIDTH,
		EQUIRECTANGULAR_HEIGHT);

		if (encoder.Encode(out_filename, vr_image)) {
		} else {
			perror("error on jpeg encode");
			return -1;
		}
	}

	return 0;
}
