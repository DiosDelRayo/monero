#pragma once

#include "ots.hpp"
#include "crypto/crypto.h"
#include "mnemonics/electrum-words.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_core/cryptonote_core.h"

// TODO: resolve dependencies to compile everything static inside

namespace ots {
    crypto::secret_key keyFromHash(const std::vector<unsigned char>& data);
    crypto::secret_key randomKey();
    epee::wipeable_string seedPhraseFromKey(const crypto::secret_key& key, const std::string& language);

    class KeyJar {
        public:
            key_handle_t store(
                    const crypto::secret_key& key, 
                    const std::string& label = {}, 
                    Seed* seed = nullptr
                    );
            const crypto::secret_key get(const std::string& label) const;
            const crypto::secret_key get(const Seed& seed) const;
            const crypto::secret_key get(key_handle_t handle) const;
            bool has(const std::string& label) const;
            bool has(const Seed& seed) const;
            bool remove(key_handle_t handle);
            const Seed& getSeed(key_handle_t handle) const;
            const std::string& getLabel(key_handle_t handle) const;
            Network getNetwork(key_handle_t handle) const;
            Wallet getWallet(key_handle_t handle) const;
            static const KeyJar& instance();
    };
}
