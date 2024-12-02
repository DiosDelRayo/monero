#pragma once

#include "ots-exceptions.hpp"
#include "version.h"
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <utility>

namespace crypto {
    struct secret_key;
}

namespace ots {

	enum class Network {
		MAIN,
		TEST,
		STAGE
	};

	enum class SeedType {
		Monero,
		Polyseed,
		All // used to not filter the language list by type
	};

	// Forward declarations
	class Seed;
	class Wallet;
	class KeyJar;
	class TxDescription;
	class TxWarning;

	// Type aliases
	using key_handle_t = size_t;
	using seed_handle_t = size_t;

	// Seed Language class
	class SeedLanguage {
		public:
			[[nodiscard]] std::string name() const;
			[[nodiscard]] std::string englishName() const;
			[[nodiscard]] std::string code() const;
			[[nodiscard]] bool supported(SeedType type = SeedType::Monero) const;
			[[nodiscard]] bool isDefault(SeedType type = SeedType::Monero) const;
			bool operator==(const SeedLanguage& other) const;

			static const SeedLanguage fromName(const std::string& name);
			static const SeedLanguage fromEnglishName(const std::string& name);
			static const SeedLanguage fromCode(const std::string& code);

			static const std::vector<SeedLanguage>& list();
			static const std::vector<SeedLanguage> listFor(SeedType type);
			static const SeedLanguage& defaultLanguage(SeedType type = SeedType::Monero);

		private:
			static std::vector<SeedLanguage> s_list;
			static std::map<SeedType, SeedLanguage> s_default;
			std::string m_code;
			std::string m_name;
			std::string m_englishName;
			std::map<SeedType, bool> m_supported;
	};

	class Seed {
		public:
			virtual ~Seed() = default;
			virtual std::string phrase(const SeedLanguage& language) const = 0;
			virtual inline std::vector<int> values() const { return m_values; };
			virtual std::string fingerprint() const = 0;
			virtual key_handle_t storeKey(KeyJar& keyJar, const std::string& label = {}) = 0;
			virtual bool valid() const = 0;
			virtual uint64_t birthday() const;
			virtual uint64_t height() const;
			virtual inline bool encrypted() const { return false; };
			virtual inline Network network() const { return m_network; };
			virtual bool languageSupported(const SeedLanguage& language) const;

		protected:
			uint64_t m_birthday = 0;
			uint64_t m_height = 0;
			std::vector<int> m_values;
			Network m_network;
	};

	class EncryptableSeed : public Seed {
		public:
			virtual bool encrypt(const std::string& password) = 0;
			virtual bool decrypt(const std::string& password) = 0;
	};

	class LegacySeed : public Seed {
		public:
			std::string phrase(const SeedLanguage& language) const override;
			std::vector<int> values() const override;
			std::string fingerprint() const override;
			key_handle_t storeKey(KeyJar& keyJar, const std::string& label = {}) override;
			bool valid() const override;
			inline bool encrypted() const override { return false; };
			bool languageSupported(const SeedLanguage& language) const override;
			static LegacySeed decode(
					const std::string& phrase,
					const SeedLanguage& language, 
					uint64_t height = 0,
					uint64_t time = 0, 
					Network network = Network::MAIN
					);
			static LegacySeed decode(
					const std::vector<int>& values, 
					uint64_t height = 0,
					uint64_t time = 0, 
					Network network = Network::MAIN
					);
	};

	class MoneroSeed : public EncryptableSeed {
		public:
			std::string phrase(const SeedLanguage& language) const override;
			std::vector<int> values() const override;
			std::string fingerprint() const override;
			key_handle_t storeKey(KeyJar& keyJar, const std::string& label = {}) override;
			bool valid() const override;
			bool encrypted() const override;
			bool encrypt(const std::string& password) override;
			bool decrypt(const std::string& password) override;
			static MoneroSeed decode(
					const std::string& phrase,
					const SeedLanguage& language, 
					uint64_t height = 0,
					uint64_t time = 0, 
					bool encrypted = false, 
					Network network = Network::MAIN
					);
			static MoneroSeed decode(
					const std::vector<int>& values, 
					uint64_t height = 0,
					uint64_t time = 0, 
					bool encrypted = false, 
					Network network = Network::MAIN
					);
			static MoneroSeed create(
					uint64_t height = 0,
					uint64_t time = 0, 
					Network network = Network::MAIN
					);
	};

	class Polyseed : public EncryptableSeed {
		public:
			std::string phrase(const SeedLanguage& language) const override;
			std::vector<int> values() const override;
			std::string fingerprint() const override;
			key_handle_t storeKey(KeyJar& keyJar, const std::string& label = {}) override;
			bool valid() const override;
			bool encrypted() const override;
			bool encrypt(const std::string& password) override;
			bool decrypt(const std::string& password) override;
			static Polyseed create(
					uint64_t time,
					const SeedLanguage& language, 
					Network network = Network::MAIN
					);
			static Polyseed decode(
					const std::string& phrase, 
					Network network = Network::MAIN
					);
			static Polyseed decode(
					const std::string& phrase, 
					const SeedLanguage& language, 
					Network network = Network::MAIN
					);
			static Polyseed decode(
					const std::vector<int>& values, 
					Network network = Network::MAIN
					);
	};

	class Address {
		public:
			explicit Address(const std::string& address);

			[[nodiscard]] bool isValid() const noexcept;
			[[nodiscard]] Network network() const;
			[[nodiscard]] std::pair<int, int> index(const Wallet& wallet) const;

			explicit operator std::string() const;
		private:
			std::string m_address;
	};

	class OTS {
		public:
			explicit OTS();
			inline static const std::string version() { return OTS_VERSION_STRING; };
			inline static std::array<int, 3> versionComponents() {
				return {OTS_VERSION_MAJOR, OTS_VERSION_MINOR, OTS_VERSION_PATCH};
			};
			bool validAddress(
					const std::string& address, 
					Network network = Network::MAIN
					) const;
			static uint64_t heightFromTimestamp(uint64_t timestamp, Network network = Network::MAIN);
			static uint64_t timestampFromHeight(uint64_t height, Network network = Network::MAIN);
	};

	class SeedJar {
		public:
			seed_handle_t store(const Seed& seed) const;
			const Seed& get(seed_handle_t handle) const;
			const Seed& get(const std::string& fingerprint) const;
			bool has(seed_handle_t handle) const;
			bool has(const std::string& fingerprint) const;
			std::vector<std::reference_wrapper<const Seed>> list() const;
			static const SeedJar& instance();
	};

	class KeyJar {
		public:
			key_handle_t store(
					const crypto::secret_key& key, 
					const std::string& label = {}, 
					Seed* seed = nullptr
					);
			const crypto::secret_key get(const std::string& label) const;
			const crypto::secret_key get(const Seed& seed) const;
			const crypto::secret_key get(key_handle_t handle) const;
			bool has(const std::string& label) const;
			bool has(const Seed& seed) const;
			bool remove(key_handle_t handle);
			const Seed& getSeed(key_handle_t handle) const;
			const std::string& getLabel(key_handle_t handle) const;
			Network getNetwork(key_handle_t handle) const;
			Wallet getWallet(key_handle_t handle) const;
			static const KeyJar& instance();
	};

	class Wallet {
		public:
			Address address(int account = 0, int index = 0) const;
			std::vector<Address> accounts(int max = 10, int offset = 0) const;
			std::vector<Address> subAddresses(int account = 0, int max = 10, int offset = 0) const;
			bool hasAddress(const std::string& address) const;
			bool hasAddress(const Address& address) const;
			std::pair<int, int> addressIndex(const std::string& address) const;
			std::pair<int, int> addressIndex(const Address& address) const;
			uint64_t importOutputs(const std::string& outputs);
			std::string exportKeyImages() const;
			// Transaction-related methods
			TxDescription describeTransaction(const std::string& unsignedTransaction) const;
			std::vector<TxWarning> checkTransaction(const std::string& unsignedTransaction) const;
			std::vector<TxWarning> checkTransaction(const TxDescription& description) const;
			std::string signTransaction(const std::string& unsignedTransaction) const;
			std::string signData(const std::string& data) const;
			bool verifyData(
					const std::string& data, 
					const std::string& address, 
					const std::string& signature
					) const;
	};
	// Placeholder classes for TxDescription and TxWarning
	class TxDescription {};
	class TxWarning {};

} // namespace ots
