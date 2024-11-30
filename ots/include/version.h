#ifndef OTS_VERSION_H
#define OTS_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

// Version management
typedef enum {
    OTS_V1 = 1,
    OTS_LATEST = OTS_V1
} ots_version_t;

#ifdef __cplusplus
}
#endif

#endif // OTS_VERSION_H
