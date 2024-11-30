#include "ots.hpp"

#include "crypto/crypto.h"
#include "mnemonics/electrum-words.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_core/cryptonote_core.h"


namespace epee {  class wipeable_string; }
namespace ots {


    class OTS::Impl {
	public:
	    explicit Impl(int version) {}
	    // Core implementations
	    std::string generateSeed() const {
		return generateSeedFromHashV1(crypto::secret_key(), false);
	    }

	    std::string generateSeedFromHash(const std::vector<unsigned char>& data) const {
		crypto::secret_key key;
		hash_to_scalar(data.data(), data.size(), key);
		return generateSeedFromHashV1(key, true);
	    }

	    crypto::secret_key secretSpendKeyFromSeed(const std::string& seed_phrase) const {
		    return secretSpendKeyFromSeedV1(seed_phrase);
		}
	private:
	    std::string generateSeedFromHashV1(const crypto::secret_key& recovery_key, bool recover) const {
		crypto::secret_key key;
		if(recover)
		    key = recovery_key;
		else
		    crypto::random32_unbiased((unsigned char*)key.data);
		epee::wipeable_string words;
		bool ok = crypto::ElectrumWords::bytes_to_words(key, words, "English");
		return ok?words.data():std::string();
	    }

	    crypto::secret_key secretSpendKeyFromSeedV1(const std::string& seed_phrase) const {
		crypto::secret_key spend_key;
		// bool ok = crypto::ElectrumWords::words_to_bytes(key, words, "English");
		// Implement key derivation
		return spend_key;
	    }

	    int version;
    };


    OTS::OTS(int version) : pimpl(std::make_unique<Impl>(version)), version(version) {}
    OTS::~OTS() = default;  // Define destructor where Impl is complete
    OTS::OTS(OTS&&) noexcept = default;
    OTS& OTS::operator=(OTS&&) noexcept = default;

    std::string OTS::generateSeed() const {
	return pimpl->generateSeed();
    }

    std::string OTS::generateSeedFromHash(const std::vector<unsigned char>& data) const {
	return pimpl->generateSeedFromHash(data);
    }

    // crypto::secret_key OTS::secretSpendKeyFromSeed(const std::string& seed_phrase) const {
    ec_scalar OTS::secretSpendKeyFromSeed(const std::string& seed_phrase) const {
	return pimpl->secretSpendKeyFromSeed(seed_phrase);
    }

} // namespace ots
