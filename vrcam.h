#ifndef VRCAM_H
#define VRCAM_H


#ifdef __cplusplus
extern "C" {
#endif

int ToJpegAsEquirectangular(int width, int height, int stride,
		const uint8_t *imagedata, const char *out_filename);

#ifdef __cplusplus
}
#endif

#endif
