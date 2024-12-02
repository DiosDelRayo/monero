#include "ots.hpp"

namespace ots {
	std::string LegacySeed::phrase(const SeedLanguage& language) const {
		NOT_IMPLEMENTED_YET();
	}

	std::vector<int> LegacySeed::values() const {
		NOT_IMPLEMENTED_YET();
	}

	std::string LegacySeed::fingerprint() const {
		NOT_IMPLEMENTED_YET();
	}

	key_handle_t LegacySeed::storeKey(KeyJar& keyJar, const std::string& label) {
		NOT_IMPLEMENTED_YET();
	}

	bool LegacySeed::valid() const {
		NOT_IMPLEMENTED_YET();
	}

	uint64_t LegacySeed::birthday() const {
		NOT_IMPLEMENTED_YET();
	}

	uint64_t LegacySeed::height() const {
		NOT_IMPLEMENTED_YET();
	}

	LegacySeed LegacySeed::decode(
			const std::string& phrase,
			const SeedLanguage& language, 
			uint64_t height,
			uint64_t time, 
			Network network
			) {
		NOT_IMPLEMENTED_YET();
	}

	LegacySeed LegacySeed::decode(
			const std::vector<int>& values, 
			uint64_t height,
			uint64_t time,
			Network network
			) {
		NOT_IMPLEMENTED_YET();
	}
}
