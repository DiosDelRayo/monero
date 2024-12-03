#include "ots.hpp"
#include "ots-internal.hpp"
#include "key-store.hpp"
#include "version.h"

namespace ots {

    crypto::secret_key keyFromHash(const std::vector<unsigned char>& data) {
		crypto::secret_key key;
		hash_to_scalar(data.data(), data.size(), key);
        return key;
    }

    crypto::secret_key randomKey() {
		crypto::secret_key key;
        crypto::random32_unbiased((unsigned char*)key.data);
        return key;
    }

    epee::wipeable_string phraseFromKey(const crypto::secret_key& key, const std::string& language) {
        epee::wipeable_string words;
        bool ok = crypto::ElectrumWords::bytes_to_words(key, words, language);
        if(!ok)
            throw ots::exception::RuntimeError("Unable to generate seed phrase from bytes");
        return words;
    }

    const std::string version() { return OTS_VERSION_STRING; };
    std::array<int, 3> versionComponents() {
        return {OTS_VERSION_MAJOR, OTS_VERSION_MINOR, OTS_VERSION_PATCH};
    };
} // namespace ots
