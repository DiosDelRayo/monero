#pragma once

#include "ots-exceptions.hpp"
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <utility>

/**
 * @file ots.hpp
 * @brief Offline Transaction Signing Header for the C++ library
 * @see ots.h for the C ABI
 *
 * @namespace ots
 * @brief The library exists complete only in this namespace
 *
 * This header file provides following features for the ots library for C++:
 *
 * - Legacy Seed (13 words) handling - except generating, omited on purpose
 * - Monero Seed (25 words) handling
 * - Polyseed (16 words) handling
 * - Address management
 * - Address verification
 * - Import of outputs
 * - Export of key images
 * - inspect unsigned transaction
 * - sign a unsigned transaction
 */
namespace ots {

    /**
     * @enum Network
     * @brief Represents the monero network
     *
     * - MAIN: production and default network
     * - TEST: development and testing network
     * - STAGE: pre-production testing
     */
	enum class Network {
		MAIN,
		TEST,
		STAGE
	};

    /**
     * @enum SeedType
     * @brief Represents the seed type, and is used for the different dictionaries (languages) available
     *
     * - Monero: Languages for Monero Seeds (@see LegacySeed, @see MoneroSeed)
     * - Polyseed: Languages for @see Polyseed
     */
	enum class SeedType {
		Monero,
		Polyseed
	};

	// Forward declarations
	class Seed;
	class Wallet;
	class KeyJar;
    class KeyStore;
	class TxDescription;
	class TxWarning;

	// Type aliases
	using key_handle_t = size_t;
	using seed_handle_t = size_t;

    /**
     * @class SeedLanguage
     * @brief Manages seed phrase languages and their properties
     * 
     * Provides methods to retrieve, validate, and manage seed phrase languages
     */
	class SeedLanguage {
		public:
            /**
             * @brief Retrieves the native name of the seed language
             * @return std::string Language native name
             */
			[[nodiscard]] std::string name() const;

            /**
             * @brief Retrieves the English name of the seed language
             * @return std::string Language name in English
             */
			[[nodiscard]] std::string englishName() const;

            /**
             * @brief Retrieves the two-letter language code, which could be extended by a dash with a variation
             * @return std::string language code
             */
			[[nodiscard]] std::string code() const;

            /**
             * @brief Checks if the language is supported for a specific seed type
             * @param type SeedType to check support for (default: Monero), alternative Polyseed
             * @return bool True if the language is supported, false otherwise
             */
			[[nodiscard]] bool supported(SeedType type = SeedType::Monero) const;

            /**
             * @brief Checks if this is the default language for a given seed type
             * @param type SeedType to check (default: Monero), alternative Polyseed
             * @return bool True if this is the default language, false otherwise
             */
			[[nodiscard]] bool isDefault(SeedType type = SeedType::Monero) const;

            /**
             * @brief Compares two SeedLanguage objects for equality
             * @param other SeedLanguage to compare against
             * @return bool True if languages are the same, false otherwise
             */
			bool operator==(const SeedLanguage& other) const;

            /**
             * @brief Retrieves a SeedLanguage by its native name
             * @param name Native language name
             * @return const SeedLanguage Found language object
             * @throws std::runtime_error If language not found
             */
			static const SeedLanguage fromName(const std::string& name);

            /**
             * @brief Retrieves a SeedLanguage by its English name
             * @param name English language name
             * @return const SeedLanguage Found language object
             * @throws std::runtime_error If language not found
             */
			static const SeedLanguage fromEnglishName(const std::string& name);

            /**
             * @brief Retrieves a SeedLanguage by its language code
             * @param code Language code
             * @return const SeedLanguage Found language object
             * @throws std::runtime_error If language not found
             */
			static const SeedLanguage fromCode(const std::string& code);


            /**
             * @brief Retrieves the complete list of available seed languages
             * @return const std::vector<SeedLanguage>& List of all supported languages
             */
			static const std::vector<SeedLanguage>& list();

            /**
             * @brief Retrieves languages supported for a specific seed type
             * @param type SeedType to filter languages: (default: Monero), alternative Polyseed
             * @return const std::vector<SeedLanguage> Languages supporting the seed type
             */
			static const std::vector<SeedLanguage> listFor(SeedType type);

            /**
             * @brief Gets the default language for a given seed type
             * @param type SeedType to find default language (default: Monero), alternative Polyseed
             * @return const SeedLanguage& Default language for the seed type
             */
			static const SeedLanguage& defaultLanguage(SeedType type = SeedType::Monero);

		private:
			static std::vector<SeedLanguage> s_list;
			static std::map<SeedType, SeedLanguage> s_default;
			std::string m_code;
			std::string m_name;
			std::string m_englishName;
			std::map<SeedType, bool> m_supported;
	};

    /**
     * @class Seed
     * @brief Abstract base class for cryptographic seed management
     * 
     * Provides core functionality for managing seeds
     */
	class Seed {
		public:
            /**
             * @brief Virtual destructor to ensure proper cleanup of derived classes
             */
			virtual ~Seed() = default;

            /**
             * @brief Generates the seed phrase in a specified language
             * @param language SeedLanguage to generate phrase in
             * @return std::string Seed phrase
             */
			virtual std::string phrase(const SeedLanguage& language) const = 0;

            /**
             * @brief Gets the raw numeric values representing the seed
             * @return std::vector<int> Seed numeric representation
             */
			virtual inline std::vector<int> values() const { return m_values; };

            /**
             * @brief Generates a unique fingerprint for the seed
             * @return std::string Seed fingerprint
             */
			virtual std::string fingerprint() const = 0;

            /**
             * @brief Stores the seed key in a key management system
             * @param keyJar KeyJar to store the key in
             * @param label Optional label for the stored key
             * @return key_handle_t Handle to the stored key
             *
             * TODO: probably to be removed how the key will be now stored in the KeyStore
             */
			virtual key_handle_t storeKey(KeyJar& keyJar, const std::string& label = {}) = 0;

            /**
             * @brief Checks if the seed is valid
             * @return bool True if the seed is valid, false otherwise
             *
             * TODO: should be removed how the seed should be on this point always valid
             *       because on creating the object will be an exception thrown if invalid
             *       if at all it would make sense to provide a static method to pre-check,
             *       but preferable, simply remove.
             */
			virtual bool valid() const = 0;

            /**
             * @brief Gets the seed's creation timestamp
             * @return uint64_t Seed creation timestamp
             *
             * For Polyseed this is more exact as height()
             * For Monero seeds it depends what was provided by the user,
             *  if there date was provided it will be more accurate, in
             *  case the block height on creation was provide this is also
             *  only a rough estimation
             */
			virtual uint64_t birthday() const;

            /**
             * @brief Gets the blockchain height associated with the seed
             * @return uint64_t Blockchain height
             *
             * For Polyseed this is an estimation minus a security time span of 30 days in the past
             * For Monero seeds it will be the same if the user provided a date, otherwise
             *  it will be the height the user provided, can be 0 also.
             */
			virtual uint64_t height() const;

            /**
             * @brief Checks if the seed is encrypted
             * @return bool True if the seed is encrypted, false otherwise
             */
			virtual inline bool encrypted() const { return false; };

            /**
             * @brief Gets the network associated with the seed
             * @return Network Cryptocurrency network
             *
             * Main importance is that the addresses are based on the key
             * and the network - other network different keys
             */
			virtual inline Network network() const { return m_network; };

            /**
             * @brief Checks if a specific language is supported for the seed
             * @param language SeedLanguage to check
             * @return bool True if the language is supported, false otherwise
             *
             * convinience method, calls language->isSupported(SeedType)
             * TODO: should probably be removed
             */
			virtual bool languageSupported(const SeedLanguage& language) const;

            /**
             * @brief Creates a wallet from the seed
             * @return std::shared_ptr<Wallet> Wallet created from the seed
             *
             * will return always the same wallet, wallet is created only once.
             */
            virtual std::shared_ptr<Wallet> wallet();
            // Explicitly delete copy operations
            Seed(const Seed&) = delete;
            Seed& operator=(const Seed&) = delete;
            // Allow move operations
            Seed(Seed&&) noexcept = default;
            Seed& operator=(Seed&&) noexcept = default;

		protected:
            Seed();
			uint64_t m_birthday = 0;
			uint64_t m_height = 0;
            std::unique_ptr<KeyStore> m_key;
			std::vector<int> m_values;
			Network m_network;
	};


    /**
     * @class EncryptableSeed
     * @brief Abstract base class for seeds that support encryption
     * 
     * Extends Seed with encryption and decryption capabilities
     */
	class EncryptableSeed : public Seed {
		public:
            /**
             * @brief Encrypts the seed with a password
             * @param password Encryption password
             * @return bool True if encrypted, false otherwise
             */
			virtual bool encrypt(const std::string& password) = 0;

            /**
             * @brief Decrypts the seed with a password
             * @param password Decryption password
             * @return bool True if decrypted, false otherwise
             */
			virtual bool decrypt(const std::string& password) = 0;
        protected:
            EncryptableSeed() = default;
	};


    /**
     * @class LegacySeed
     * @brief Represents a monero 13-words seed type for backward compatibility
     * 
     * Provides only decoding
     */
	class LegacySeed : public Seed {
		public:
            /**
             * @brief seed phrase in a specified language
             * @param language SeedLanguage to use
             * @return std::string Seed phrase
             */
			std::string phrase(const SeedLanguage& language) const override;
			std::vector<int> values() const override;
			std::string fingerprint() const override;
			key_handle_t storeKey(KeyJar& keyJar, const std::string& label = {}) override;
			bool valid() const override;
			bool languageSupported(const SeedLanguage& language) const override;

            /**
             * @brief Decodes a seed from a phrase
             * @param phrase Seed phrase
             * @param language SeedLanguage of the phrase
             * @param height Optional blockchain height
             * @param time Optional timestamp
             * @param network Network type (default: MAIN)
             * @return LegacySeed Decoded seed
             */
			static LegacySeed decode(
					const std::string& phrase,
					const SeedLanguage& language, 
					uint64_t height = 0,
					uint64_t time = 0, 
					Network network = Network::MAIN
					);

            /**
             * @brief Decodes a seed from numeric values
             * @param values Numeric representation of the seed
             * @param height Optional blockchain height
             * @param time Optional timestamp
             * @param network Network type (default: MAIN)
             * @return LegacySeed Decoded seed
             */
			static LegacySeed decode(
					const std::vector<int>& values, 
					uint64_t height = 0,
					uint64_t time = 0, 
					Network network = Network::MAIN
					);
	};

    /**
     * @class MoneroSeed
     * @brief Represents a Monero 25-words seed
     * 
     * Provides Monero seed generation and decoding
     */
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

            /**
             * @brief Creates a Monero seed from a random source
             * @param random 32-byte random input
             * @param height Optional blockchain height
             * @param time Optional timestamp
             * @param network Network type (default: MAIN)
             * @return MoneroSeed Created seed
             *
             * Can be used to:
             * - recover a seed
             * - generate from external entropy
             */
			static MoneroSeed create(
                    const std::array<unsigned char, 32>& random,
					uint64_t height = 0,
					uint64_t time = 0, 
					Network network = Network::MAIN
					);

            /**
             * @brief Generates a new Monero seed
             * @param height Optional blockchain height
             * @param time Optional timestamp
             * @param network Network type (default: MAIN)
             * @return MoneroSeed Generated seed
             *
             * Warning!
             * Generates a seed from the device provided entropy.
             * Use with caution if the device can't provide good
             * enough entropy!
             */
			static MoneroSeed generate(
					uint64_t height = 0,
					uint64_t time = 0, 
					Network network = Network::MAIN
					);
	};

    /**
     * @class Polyseed
     * @brief Represents a Polyseed type
     * 
     * Provides Polyseed generation, encoding, and management
     */
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

            /**
             * @brief Creates a Polyseed with specific parameters
             * @param time Timestamp for seed creation
             * @param language Seed language
             * @param network Network type (default: MAIN)
             * @return Polyseed Created seed
             */
			static Polyseed create(
					uint64_t time,
					const SeedLanguage& language, 
					Network network = Network::MAIN
					);

            /**
             * @brief Decodes a Polyseed from a phrase
             * @param phrase Seed phrase
             * @param network Network type (default: MAIN)
             * @return Polyseed Decoded seed
             */
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
			static const std::string version() noexcept;
			static std::array<int, 3> versionComponents() noexcept;
			static bool validAddress(
					const std::string& address, 
					Network network = Network::MAIN
					);
			static uint64_t heightFromTimestamp(uint64_t timestamp, Network network = Network::MAIN);
			static uint64_t timestampFromHeight(uint64_t height, Network network = Network::MAIN);
            static std::array<unsigned char, 32> random();
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

	class Wallet {
		public:
            uint64_t height() const { return m_height; };
			Address address(int account = 0, int index = 0) const;
			std::vector<Address> accounts(int max = 10, int offset = 0) const;
			std::vector<Address> subAddresses(int account = 0, int max = 10, int offset = 0) const;
			bool hasAddress(const std::string& address) const;
			bool hasAddress(const Address& address) const;
			std::pair<int, int> addressIndex(const std::string& address) const;
			std::pair<int, int> addressIndex(const Address& address) const;
			uint64_t importOutputs(const std::string& outputs);
            std::string secretViewKey() const { return ""; /* TODO: implement */ };
            std::string publicViewKey() const { return ""; /* TODO: implement */ };
            std::string secretSpendKey() const { return ""; /* TODO: implement */ };
            std::string publicSpendKey() const { return ""; /* TODO: implement */ };
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
            Wallet(const std::array<unsigned char, 32>&, uint64_t height);
            Wallet(const KeyStore& key, uint64_t height);
        protected:
            std::unique_ptr<KeyStore> m_key;
            uint64_t m_height = 0;
	};
	// Placeholder classes for TxDescription and TxWarning
	class TxDescription {};
	class TxWarning {};

} // namespace ots
