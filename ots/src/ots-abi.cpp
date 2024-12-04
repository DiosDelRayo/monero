#include "ots.h"
#include "ots.hpp"
#include <cstring>
#include <memory>

struct ots_ctx_st {
    std::unique_ptr<ots::OTS> impl;

    explicit ots_ctx_st(ots::OTS* ptr) : impl(ptr) {}
};

namespace {
    // Exception translation utility
    void translate_exception(ots_error_t* error, const std::exception& e) {
        error->code = -1;
        std::strncpy(error->message, e.what(), sizeof(error->message) - 1);
        error->message[sizeof(error->message) - 1] = '\0';
    }

    // Success error state setting
    void set_error_success(ots_result_t* result) {
        if (result) {
            result->error.code = 0;
            result->error.message[0] = '\0';
        }
    }
}

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
            // unique_ptr will automatically delete the OTS instance
            delete result->ctx;
            result->ctx = nullptr;
        }
    }

    char* ots_version() {
        std::string version_str = ots::OTS::version();
        return strdup(version_str.c_str());
    }

    void ots_free_version_string(char* version_str) {
        free(version_str);
    }

    int* ots_version_components() {
        auto [major, minor, patch] = ots::OTS::versionComponents();
        int* out = new int[3]{major, minor, patch};
        return out;
    }

    void ots_free_version_components(int* components) {
        delete[] components;
    }
}
