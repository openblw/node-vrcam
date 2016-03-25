/**
 * @file config.h
 * @brief Compile-time configuration options.
 */

#ifndef __OMXCV_CONFIG_H
#define __OMXCV_CONFIG_H

/* Short git hash */
#define OMXCV_VERSION "${OMXCV_VERSION}"
/* Date of git hash */
#define OMXCV_DATE "${OMXCV_DATE}"

/* Enable Pi 2 (armv7/NEON) stuff */
#cmakedefine ENABLE_NEON

#endif /* __OMXCV_CONFIG_H */
