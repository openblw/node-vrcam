{
  "targets": [{
    "target_name": "v4l2camera", 
    "sources": ["capture.c", "image_gpu.cpp", "vrcam.cc", "v4l2camera.cc"],
    "cflags": ["-Wall", "-Wextra", "-pedantic"],
    "cflags_c": ["-std=c11", "-Wno-unused-parameter"], 
    "cflags_cc": ["-std=c++11"],
    'include_dirs': [
                    "/opt/vc/include",
                    "/opt/vc/include/interface/vcos/pthreads"
                    ],
	'libraries': [
					"-L/home/pi/git/omxcv/",
					"-L/opt/vc/lib",
					"-L/opt/vc/src/hello_pi/libs/ilclient",
					"-lopencv_videostab",
					"-lopencv_ts",
					"-lopencv_superres",
					"-lopencv_stitching",
					"-lopencv_ocl",
					"-lopencv_gpu",
					"-lopencv_photo",
					"-lopencv_legacy",
					"-lopencv_contrib",
					"-lopencv_video",
					"-lopencv_objdetect",
					"-lopencv_ml",
					"-lopencv_calib3d",
					"-lopencv_features2d",
					"-lopencv_highgui",
					"-lopencv_imgproc",
					"-lopencv_flann",
					"-lopencv_core",
					"-lomxcv",
					"-lbcm_host",
					"-lilclient",
					"-lopenmaxil",
					"-lEGL",
					"-lGLESv2",
					"-lavformat",
					"-lavcodec",
					"-lavutil"]
  }]
}
