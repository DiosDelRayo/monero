#include "ots.hpp"
#include "key-store.hpp"

namespace ots {

	Address Wallet::address(uint32_t account, uint32_t index) const noexcept {
		NOT_IMPLEMENTED_YET();
	}

	std::vector<Address> Wallet::accounts(uint32_t max, uint32_t offset) const noexcept {
		/*
		std::vector<Address> accounts;
		return accounts;
		*/
		NOT_IMPLEMENTED_YET();
	}

	std::vector<Address> Wallet::subAddresses(uint32_t account, uint32_t max, uint32_t offset) const noexcept {
		NOT_IMPLEMENTED_YET();
	}

	bool Wallet::hasAddress(const std::string& address) const noexcept {
        try {
            return hasAddress(Address(address));
        } catch(ots::exception::address::Invalid e) {
            return false;
        }
	}

	bool Wallet::hasAddress(const Address& address) const noexcept {
		NOT_IMPLEMENTED_YET();
	}

	std::pair<uint32_t, uint32_t> Wallet::addressIndex(const std::string& address) const {
		NOT_IMPLEMENTED_YET();
	}

	std::pair<uint32_t, uint32_t> Wallet::addressIndex(const Address& address) const {
		NOT_IMPLEMENTED_YET();
	}

    std::string Wallet::secretViewKey() const noexcept {
		NOT_IMPLEMENTED_YET();
    };

    std::string Wallet::publicViewKey() const noexcept {
		NOT_IMPLEMENTED_YET();
    };

    std::string Wallet::secretSpendKey() const noexcept {
		NOT_IMPLEMENTED_YET();
    };

    std::string Wallet::publicSpendKey() const noexcept {
		NOT_IMPLEMENTED_YET();
    };

	uint64_t Wallet::importOutputs(const std::string& outputs) {
		NOT_IMPLEMENTED_YET();
	}

	std::string Wallet::exportKeyImages() const {
		NOT_IMPLEMENTED_YET();
	}


	// Transaction-related methods
	TxDescription Wallet::describeTransaction(const std::string& unsignedTransaction) const {
		NOT_IMPLEMENTED_YET();
	}


	std::vector<TxWarning> Wallet::checkTransaction(const std::string& unsignedTransaction) const {
		NOT_IMPLEMENTED_YET();
	}

	std::vector<TxWarning> Wallet::checkTransaction(const TxDescription& description) const noexcept {
		NOT_IMPLEMENTED_YET();
	}


	std::string Wallet::signTransaction(const std::string& unsignedTransaction) const {
		NOT_IMPLEMENTED_YET();
	}


	std::string Wallet::signData(const std::string& data) const noexcept {
		NOT_IMPLEMENTED_YET();
	}

	bool Wallet::verifyData(
		const std::string& data, 
		const std::string& address, 
		const std::string& signature
		) const {
		NOT_IMPLEMENTED_YET();
	}

    Wallet::Wallet(const std::array<unsigned char, 32>& key, uint64_t height) noexcept :
        m_key(std::make_unique<KeyStore>(KeyStore(key))),
        m_height(height) {}

    Wallet::Wallet(const KeyStore& key, uint64_t height) noexcept :
        m_key(std::make_unique<KeyStore>(key)),
        m_height(height) {}
}
