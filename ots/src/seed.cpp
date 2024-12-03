#include "ots.hpp"
#include "key-store.hpp"
#include "seed-internal.hpp"

namespace ots {
	bool Seed::languageSupported(const SeedLanguage& language) const {
		return language.supported(SeedType::Monero);
	}

	uint64_t Seed::birthday() const {
		if(m_birthday != 0)
			return m_birthday;
		return OTS::timestampFromHeight(m_height, m_network);
	}

	uint64_t Seed::height() const {
		if(m_height == 0 && m_birthday != 0)
			return OTS::heightFromTimestamp(m_birthday, m_network);
		return m_height;
	}

    Seed::Seed() : m_key(std::make_unique<KeyStore>()), m_network(Network::MAIN) {};
}
