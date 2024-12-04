#include "ots.hpp"

namespace ots {

	Address::Address(const std::string& address) {
		if(!isValid(address))
			throw ots::exception::address::Invalid();
		m_address = address;
	}

	bool Address::isValid(const std::string& address) noexcept {
		return false; // TODO: implement
	}

	Network Address::network() const noexcept {
		return Network::MAIN; // TODO: implement
	}

    AddressType Address::type() const noexcept {
        return AddressType::Standard; // TODO: implement
    }

	Address::operator std::string() const noexcept {
		return m_address;
	}
}
