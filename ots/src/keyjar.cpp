#include "keyjar.hpp"
#include <random>

key_handle_t KeyJar::generateHandle() {
    // Generate cryptographically secure handle
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<key_handle_t> dis(1, UINT64_MAX);
    
    key_handle_t handle;
    do {
        handle = dis(gen);
    } while (handle == 0 || keys_.find(handle) != keys_.end());
    
    return handle;
}

key_handle_t KeyJar::storeKey(const crypto::secret_key& key, const std::string& label) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    key_handle_t handle = generateHandle();
    keys_.emplace(handle, SecureKeyEntry(key, label));
    
    cleanupUnusedKeys();  // Opportunistic cleanup
    return handle;
}

const crypto::secret_key* KeyJar::getKey(key_handle_t handle) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = keys_.find(handle);
    if (it == keys_.end()) {
        return nullptr;
    }
    
    it->second.access_count++;
    return it->second.key.get();
}

bool KeyJar::removeKey(key_handle_t handle) {
    std::lock_guard<std::mutex> lock(mutex_);
    return keys_.erase(handle) > 0;
}

void KeyJar::cleanupUnusedKeys() {
    // Optional: Implement policy for removing old/unused keys
    // For example, remove keys not accessed in X time or after Y operations
}
