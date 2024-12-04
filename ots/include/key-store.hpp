#pragma once

/**
 * @file key-store.hpp
 * @brief decoupling of crypto/crypto.h of the monero source
 * @internal
 */

#include "crypto/crypto.h"

namespace ots {
    /**
     * @class KeyStore
     * @brief essentialy wraps crypto::secret_key
     * @internal
     * Used to keep monero source out of the ots.hpp throuh forward declaration of KeyStore
     */
    class KeyStore {
        public:
            explicit KeyStore();
            explicit KeyStore(const std::array<unsigned char, 32>& key);
            explicit KeyStore(crypto::secret_key key);
            operator crypto::secret_key&() { return m_key; }
        protected:
            crypto::secret_key m_key;
    };
}
