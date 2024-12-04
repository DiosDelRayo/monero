#ifndef OTS_H
#define OTS_H

#ifdef __cplusplus
#include <memory>

namespace ots {
    class OTS;
}

extern "C" {
#endif

    // Opaque pointer for the context
    typedef struct ots_ctx_st ots_ctx_st;

    // Error handling structure
    typedef struct {
        int32_t code;
        char message[256];
        char location[64];
    } ots_error_t;

    // Context with error
    typedef struct {
        ots_ctx_st* ctx;
        ots_error_t error;
    } ots_result_t;

    // Create context for OTS
    ots_result_t ots_create_context();

    // Destroy context
    void ots_free_context(ots_result_t* result);

    // Get version as string
    char* ots_version();

    // Free version string
    void ots_free_version_string(char* version_str);

    // Get version components
    int* ots_version_components();

    // Free version components
    void ots_free_version_components(int* components);

#ifdef __cplusplus
}
#endif

#endif // OTS_H
