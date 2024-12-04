#include "ots.hpp"
#include "ots-internal.hpp"
#include "key-store.hpp"
#include "version.h"

namespace ots {

    OTS::OTS() {};

    const std::string OTS::version() noexcept {
        return OTS_VERSION_STRING;
    };

    std::array<int, 3> OTS::versionComponents() noexcept {
        return {OTS_VERSION_MAJOR, OTS_VERSION_MINOR, OTS_VERSION_PATCH};
    };

    uint64_t OTS::heightFromTimestamp(uint64_t timestamp, Network network) {
        NOT_IMPLEMENTED_YET();
    }

    uint64_t OTS::timestampFromHeight(uint64_t height, Network network) {
        NOT_IMPLEMENTED_YET();
    }

    std::array<unsigned char, 32> OTS::random() {
        NOT_IMPLEMENTED_YET();
        /* TODO: solve first dependencies
        std::array<unsigned char, 32> key;
        crypto::random32_unbiased(key.data());
        return key;
        */
    }

    crypto::secret_key keyFromHash(const std::vector<unsigned char>& data) {
        NOT_IMPLEMENTED_YET();
        /* TODO: solve first dependencies
		crypto::secret_key key;
		hash_to_scalar(data.data(), data.size(), key);
        return key;
        */
    }

    crypto::secret_key randomKey() {
        NOT_IMPLEMENTED_YET();
        /* TODO: solve first dependencies
		crypto::secret_key key;
        crypto::random32_unbiased((unsigned char*)key.data);
        return key;
        */
    }

    epee::wipeable_string phraseFromKey(const crypto::secret_key& key, const std::string& language) {
        NOT_IMPLEMENTED_YET();
        /* TODO: solve first dependencies
        epee::wipeable_string words;
        bool ok = crypto::ElectrumWords::bytes_to_words(key, words, language);
        if(!ok)
            throw ots::exception::RuntimeError("Unable to generate seed phrase from bytes");
        return words;
        */
    }
} // namespace ots
