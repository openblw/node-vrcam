#ifndef VRCAM_H
#define VRCAM_H


#ifdef __cplusplus
extern "C" {
#endif

int StartRecord();
int StopRecord();
int AddFrame(int width, int height, int stride,
		const unsigned char *imagedata);
int SaveJpegAsEquirectangular(int width, int height, int stride,
		const unsigned char *imagedata, const char *out_filename);
int SetRotation(float x_deg, float y_deg, float z_deg);

#ifdef __cplusplus
}
#endif

#endif
