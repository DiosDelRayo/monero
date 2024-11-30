#ifndef OTS_H
#define OTS_H

#include "version.h"

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
	ots_result_t ots_create_context(ots_version_t version);

	// Core functionality with versioning
	typedef struct {
	    uint8_t* spend_key;
	    ots_error_t error;
	} ots_keys_result_t;

	ots_keys_result_t seed_to_keys(ots_result_t* ctx, const char* seed_phrase);

	// Memory management
	void ots_free_keys_result(ots_keys_result_t* result);
	void ots_free_context(ots_result_t* result);

#ifdef __cplusplus
    }
#endif

#endif // OTS_H
