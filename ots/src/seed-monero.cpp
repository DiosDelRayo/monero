#include "ots.hpp"

namespace ots {
	std::string MoneroSeed::phrase(const SeedLanguage& language) const {
		NOT_IMPLEMENTED_YET();
	}

	std::vector<int> MoneroSeed::values() const {
		NOT_IMPLEMENTED_YET();
	}

	std::string MoneroSeed::fingerprint() const {
		NOT_IMPLEMENTED_YET();
	}

	key_handle_t MoneroSeed::storeKey(KeyJar& keyJar, const std::string& label) {
		NOT_IMPLEMENTED_YET();
	}

	bool MoneroSeed::valid() const {
		NOT_IMPLEMENTED_YET();
	}

	bool MoneroSeed::encrypted() const {
		NOT_IMPLEMENTED_YET();
	}

	bool MoneroSeed::encrypt(const std::string& password) {
		NOT_IMPLEMENTED_YET();
	}

	bool MoneroSeed::decrypt(const std::string& password) {
		NOT_IMPLEMENTED_YET();
	}

	MoneroSeed MoneroSeed::decode(
			const std::string& phrase,
			const SeedLanguage& language, 
			uint64_t height,
			uint64_t time,
			bool encrypted,
			Network network
			) {
		NOT_IMPLEMENTED_YET();
	}

	MoneroSeed MoneroSeed::decode(
			const std::vector<int>& values, 
			uint64_t height,
			uint64_t time,
			bool encrypted,
			Network network
			) {
		NOT_IMPLEMENTED_YET();
	}

	MoneroSeed MoneroSeed::create(
			uint64_t height,
			uint64_t time,
			Network network
			) {
		NOT_IMPLEMENTED_YET();
	}
}
