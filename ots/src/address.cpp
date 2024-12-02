#include "ots.hpp"

namespace ots {

	Address::Address(const std::string& address) {
		m_address = address;
	}

	bool Address::isValid() const noexcept {
		return false; // TODO: implement
	}

	Network Address::network() const {
		if(!isValid())
			throw ots::exception::address::Invalid();
		NOT_IMPLEMENTED_YET();
	}

	std::pair<int, int> Address::index(const Wallet& wallet) const {
		// return wallet->addressIndex(this);
		NOT_IMPLEMENTED_YET();
	}

	Address::operator std::string() const {
		return m_address;
	}
}
