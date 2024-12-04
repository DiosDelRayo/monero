#include "ots.h"
#include "ots.hpp"
#include <cstring>

namespace {
    void translate_exception(ots_error_t* error, const std::exception& e) {
        error->code = -1;
        strncpy(error->message, e.what(), sizeof(error->message) - 1);
        error->message[sizeof(error->message) - 1] = '\0';
    }

    template<typename T>
    void set_error_success(T* result) {
        result->error.code = 0;
        result->error.message[0] = '\0';
    }
} // namespace

extern "C" {
    ots_result_t ots_create_context() {
        ots_result_t result = {};
        try {
            result.ctx = new ots_ctx_st(new ots::OTS());
            set_error_success(&result);
        } catch (const std::exception& e) {
            translate_exception(&result.error, e);
        }
        return result;
    }

    void ots_free_context(ots_result_t* result) {
        if (result && result->ctx) {
            // delete result->ctx->impl;  // Delete the OTS instance
            delete result->ctx;        // Delete the context
            result->ctx = nullptr;
        }
    }

    char* ots_version() {
        std::string version_str = ots::OTS::version();
        return strdup(version_str.c_str());
    }

    int* ots_version_components() {
        auto [major, minor, patch] = ots::OTS::versionComponents();
        int* out = new int[3]{major, minor, patch};
        return out;
    }
} // extern "C"
