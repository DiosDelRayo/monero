#ifndef OTS_H
#define OTS_H

#ifdef __cplusplus
#include <memory>

namespace ots {
    class OTS;
}

extern "C" {
    // Bridge structure that holds the C++ implementation
    struct ots_ctx_st {
	ots::OTS* impl;  // Changed from unique_ptr to raw pointer since we manage lifetime through C API
	explicit ots_ctx_st(ots::OTS* ptr) : impl(ptr) {}
    };
#else
    struct ots_ctx_st;
#endif

	// Error handling structure
	typedef struct {
	    int32_t code;
	    char message[256];
	    char location[64];
	} ots_error_t;

	// Context with error
	typedef struct {
	    struct ots_ctx_st* ctx;
	    ots_error_t error;
	} ots_result_t;

	// Create context with specific version
	ots_result_t ots_create_context();
    // destroy context
    void ots_free_context(ots_result_t* result);

    char* ots_version();
    int* ots_version_components();

#ifdef __cplusplus
    }
#endif

#endif // OTS_H
