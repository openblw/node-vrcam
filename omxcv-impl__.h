/**
 * @file omxcv-impl.cpp
 * @brief Actual implementation class
 */

#ifndef __OMXCV_IMPL_H
#define __OMXCV_IMPL_H

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <utility>
#include <fstream>

#include <opencv2/opencv.hpp>

//Sigh
extern "C" {

//Without the right struct packing the buffers will be screwed...
//nFlags won't be set correctly...
#pragma pack(4)
#include <bcm_host.h>
#include <ilclient.h>
//For OMX_IndexParamNalStreamFormatSelect
#include <OMX_Broadcom.h>
#pragma pack()
}

#define OMX_ENCODE_PORT_IN  200
#define OMX_ENCODE_PORT_OUT 201

#define OMX_JPEG_PORT_IN  340
#define OMX_JPEG_PORT_OUT 341

//The maximum size of a NALU. We'll just assume 512 KB.
#define MAX_NALU_SIZE (512*1024)

#define CHECKED(c, v) if ((c)) throw std::invalid_argument(v)

namespace omxcv {
    /**
     * Our implementation class of the encoder.
     */
    class OmxCvImpl {
        public:
            OmxCvImpl(const char *name, int width, int height, int bitrate, int fpsnum=-1, int fpsden=-1);
            virtual ~OmxCvImpl();

            bool process(const cv::Mat &mat);
        private:
            int m_width, m_height, m_stride, m_bitrate, m_fpsnum, m_fpsden;
            uint8_t *m_sps, *m_pps;
            uint16_t m_sps_length, m_pps_length;
            uint32_t m_nalu_filled, m_nalu_required;
            uint8_t *m_nalu_buffer;
            bool m_initted_header;

            std::string m_filename;
            std::ofstream m_ofstream;

            std::condition_variable m_input_signaller;
            std::deque<std::pair<OMX_BUFFERHEADERTYPE *, int64_t>> m_input_queue;
            std::thread m_input_worker;
            std::mutex  m_input_mutex;
            std::atomic<bool> m_stop;

            /** The OpenMAX IL client **/
            ILCLIENT_T *m_ilclient;
            COMPONENT_T *m_encoder_component;

            std::chrono::steady_clock::time_point m_frame_start;
            int m_frame_count;

            void input_worker();
            bool write_data(OMX_BUFFERHEADERTYPE *out, int64_t timestamp);
    };
    
    class OmxCvJpegImpl {
        public:
            OmxCvJpegImpl(int width, int height, int quality=90);
            virtual ~OmxCvJpegImpl();
            
            bool process(const char *filename, const cv::Mat &mat);
        private:
            int m_width, m_height, m_stride, m_quality;
            
            std::condition_variable m_input_signaller;
            std::deque<std::pair<OMX_BUFFERHEADERTYPE *, std::string>> m_input_queue;
            std::thread m_input_worker;
            std::mutex  m_input_mutex;
            std::atomic<bool> m_stop;
            
            ILCLIENT_T *m_ilclient;
            COMPONENT_T *m_encoder_component;
            
            void input_worker();
    };
}

#endif // __OMXCV_IMPL_H
