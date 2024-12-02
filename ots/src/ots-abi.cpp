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
    ots_result_t ots_create_context(ots_version_t version) {
        ots_result_t result = {};
        try {
            result.ctx = new ots_ctx_st(new ots::OTS(version));
            set_error_success(&result);
        } catch (const std::exception& e) {
            translate_exception(&result.error, e);
        }
        return result;
    }

    ots_keys_result_t seed_to_keys(ots_result_t* ctx, const char* seed_phrase) {
        ots_keys_result_t result = {};
        if (!ctx || !ctx->ctx || !seed_phrase) {
            result.error.code = -1;
            strncpy(result.error.message, "Invalid parameters", sizeof(result.error.message));
            return result;
        }

        try {
            auto spend_key = ctx->ctx->impl->secretSpendKeyFromSeed(seed_phrase);

            // Allocate and copy keys
            result.spend_key = new uint8_t[32];
            std::memcpy(result.spend_key, spend_key.data, 32);
            set_error_success(&result);
        } catch (const std::exception& e) {
            translate_exception(&result.error, e);
        }
        return result;
    }

    void ots_free_keys_result(ots_keys_result_t* result) {
        if (result) {
            delete[] result->spend_key;
            result->spend_key = nullptr;
        }
    }

    void ots_free_context(ots_result_t* result) {
        if (result && result->ctx) {
            delete result->ctx->impl;  // Delete the OTS instance
            delete result->ctx;        // Delete the context
            result->ctx = nullptr;
        }
    }
} // extern "C"
