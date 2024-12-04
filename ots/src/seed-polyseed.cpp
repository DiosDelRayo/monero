#include "ots.hpp"
#include "key-store.hpp"

namespace ots {
	std::string Polyseed::phrase(const SeedLanguage& language) const {
		NOT_IMPLEMENTED_YET();
	}

	std::vector<int> Polyseed::values() const {
		NOT_IMPLEMENTED_YET();
	}

	std::string Polyseed::fingerprint() const {
		NOT_IMPLEMENTED_YET();
	}

	bool Polyseed::encrypted() const {
		NOT_IMPLEMENTED_YET();
	}

	bool Polyseed::encrypt(const std::string& password) {
		NOT_IMPLEMENTED_YET();
	}

	bool Polyseed::decrypt(const std::string& password) {
		NOT_IMPLEMENTED_YET();
	}

	Polyseed create(
			uint64_t time,
			const SeedLanguage& language, 
			Network network = Network::MAIN
			) {
		NOT_IMPLEMENTED_YET();
	}

	Polyseed decode(const std::string& phrase, Network network) {
		NOT_IMPLEMENTED_YET();
	}

	Polyseed decode(
			const std::string& phrase, 
			const SeedLanguage& language, 
			Network network
			) {
		NOT_IMPLEMENTED_YET();
	}

	Polyseed decode(const std::vector<int>& values, Network network) {
		NOT_IMPLEMENTED_YET();
	}
}
