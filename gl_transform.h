/**
 * @file image_gpu.h
 * @brief GPU functions for image processing.
 */

#ifndef _GLRENDERER_H
#define _GLRENDERER_H

#include <opencv2/opencv.hpp>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

namespace openblw {
class GLProgram {
public:
	GLProgram(const char *vertex_file, const char *fragment_file);
	virtual ~GLProgram();

	GLuint GetId();
	operator GLuint() {
		return m_program_id;
	}
	;
private:
	GLuint m_vertex_id, m_fragment_id, m_program_id;

	GLuint LoadShader(GLenum shader_type, const char *source_file);
	char* ReadFile(const char *file);
};

class GLTexture {
public:
	GLTexture(GLsizei width, GLsizei height, GLint type);
	virtual ~GLTexture();

	GLsizei GetWidth();
	GLsizei GetHeight();

	void SetData(void *data);
	GLuint GetTextureId();
	operator GLuint() {
		return m_texture_id;
	}
	;
private:
	GLsizei m_width, m_height;
	GLint m_type;
	GLuint m_texture_id;
};

/**
 * Class to perform colour thresholding using OpenGL.
 */
class GLTransform {
public:
	GLTransform(int width, int height, int tex_width, int tex_height);
	virtual ~GLTransform();

	void Transform(const cv::Mat &in, cv::Mat &out);
private:
	void GetRenderedData(void *buffer);

	int m_width, m_height;
	GLProgram *m_program;
	GLTexture *m_texture;
	GLTexture *m_texture_dst;

	EGLDisplay m_display;
	EGLSurface m_surface;
	GLuint m_quad_buffer;
	GLuint m_framebuffer_id;
};

}

#endif
