#include "ots.hpp"

namespace ots {

	Address Wallet::address(int account, int index) const {
		// return std::make_pair(0, 0);
		NOT_IMPLEMENTED_YET();
	}

	std::vector<Address> Wallet::accounts(int max, int offset) const {
		/*
		std::vector<Address> accounts;
		return accounts;
		*/
		NOT_IMPLEMENTED_YET();
	}

	std::vector<Address> Wallet::subAddresses(int account, int max, int offset) const {
		NOT_IMPLEMENTED_YET();
	}

	bool Wallet::hasAddress(const std::string& address) const {
		NOT_IMPLEMENTED_YET();
	}

	bool Wallet::hasAddress(const Address& address) const {
		NOT_IMPLEMENTED_YET();
	}

	std::pair<int, int> Wallet::addressIndex(const std::string& address) const {
		NOT_IMPLEMENTED_YET();
	}

	std::pair<int, int> Wallet::addressIndex(const Address& address) const {
		NOT_IMPLEMENTED_YET();
	}


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

	std::vector<TxWarning> Wallet::checkTransaction(const TxDescription& description) const {
		NOT_IMPLEMENTED_YET();
	}


	std::string Wallet::signTransaction(const std::string& unsignedTransaction) const {
		NOT_IMPLEMENTED_YET();
	}


	std::string Wallet::signData(const std::string& data) const {
		NOT_IMPLEMENTED_YET();
	}

	bool Wallet::verifyData(
		const std::string& data, 
		const std::string& address, 
		const std::string& signature
		) const {
		NOT_IMPLEMENTED_YET();
	}
}
