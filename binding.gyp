{
  "targets": [{
    "target_name": "v4l2camera", 
    "sources": ["capture.c", "vrcam.cc", "v4l2camera.cc"],
    "cflags": ["-Wall", "-Wextra", "-pedantic"],
    "cflags_c": ["-std=c11", "-Wno-unused-parameter"], 
    "cflags_cc": ["-std=c++11"],
    'include_dirs': [],
	'libraries': ["-L/home/pi/git/omxcv/", "-L/opt/vc/lib", "-L/opt/vc/src/hello_pi/libs/ilclient",
	              "-Wl,-Bstatic", "-lopencv_core", "-lopencv_legacy", "-lopencv_highgui", "-lopencv_contrib", "-lopencv_imgproc",
	              "-Wl,-Bstatic", "-lomxcv",
	              "-Wl,-Bdynamic", "-lbcm_host", "-lilclient", "-lopenmaxil"]
  }]
}

