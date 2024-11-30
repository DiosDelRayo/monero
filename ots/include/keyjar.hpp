#pragma once
#include "crypto/crypto.h"
#include <memory>
#include <unordered_map>
#include <mutex>
#include <string>

// Forward declarations
//namespace crypto {
//    struct secret_key;
//}

// Opaque handle type for FFI
typedef uint64_t key_handle_t;

class KeyJar {
private:
    struct SecureKeyEntry {
        std::unique_ptr<crypto::secret_key> key;
        std::string label;  // Optional identifier/metadata
        uint64_t access_count{0};
        
        explicit SecureKeyEntry(const crypto::secret_key& k, std::string l = std::string()) 
            : key(std::make_unique<crypto::secret_key>(k)), label(std::move(l)) {}
    };

    std::unordered_map<key_handle_t, SecureKeyEntry> keys_;
    std::mutex mutex_;
    key_handle_t next_handle_{1};  // 0 is reserved for invalid handle

    // Private utility methods
    key_handle_t generateHandle();
    void cleanupUnusedKeys();

public:
    // Internal C++ API
    key_handle_t storeKey(const crypto::secret_key& key, const std::string& label = std::string());
    const crypto::secret_key* getKey(key_handle_t handle);
    bool removeKey(key_handle_t handle);
    
    // Singleton access
    static KeyJar& instance() {
        static KeyJar instance;
        return instance;
    }

private:
    KeyJar() = default;
    ~KeyJar() = default;
    KeyJar(const KeyJar&) = delete;
    KeyJar& operator=(const KeyJar&) = delete;
};

// C FFI interface
extern "C" {
    typedef struct {
        int32_t code;
        char message[256];
    } keyjar_error_t;

    typedef struct {
        key_handle_t handle;
        keyjar_error_t error;
    } keyjar_result_t;

    // Store a key in the jar and get a handle
    keyjar_result_t keyjar_store_key(const uint8_t* key_data, size_t key_size, const char* label);
    
    // Remove a key from the jar
    keyjar_error_t keyjar_remove_key(key_handle_t handle);
    
    // Check if a handle is valid
    bool keyjar_is_valid_handle(key_handle_t handle);
    
    // Perform operations using the key without exposing it
    keyjar_error_t keyjar_sign_message(key_handle_t key_handle, 
                                     const uint8_t* message, size_t message_size,
                                     uint8_t* signature_out, size_t* signature_size);
    
    keyjar_error_t keyjar_derive_shared_secret(key_handle_t private_key_handle,
                                             const uint8_t* public_key, size_t public_key_size,
                                             uint8_t* shared_secret_out, size_t* shared_secret_size);
}
