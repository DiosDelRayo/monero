#pragma once

/**
 * @file ots-exceptions.hpp
 * @brief Header for the C++ library Exceptions
 */

#ifdef __PRETTY_FUNCTION__
#define NOT_IMPLEMENTED_YET() throw ots::exception::NotImplementedYet(__PRETTY_FUNCTION__)
#else
#define NOT_IMPLEMENTED_YET() throw ots::exception::NotImplementedYet(__func__)
#endif

#include <stdexcept>
#include <string>

namespace ots {
    /**
     * @namespace ots::exception
     * @brief All ots library related exceptions are in this namespace
     * @see https://en.cppreference.com/w/cpp/header/stdexcept
     */
	namespace exception {

        /**
         * @class RuntimeError
         * @brief Conditions only detectable at runtime
         * @note Should not used directly, is to override only
         */
		class RuntimeError: std::runtime_error {
			public:
				inline explicit RuntimeError(const std::string& msg): std::runtime_error(msg) {};
		};

        /**
         * @class LogicError
         * @brief violation of logical preconditions or class invariants
         * @note Should not used directly, is to override only
         */
		class LogicError: std::logic_error {
			public:
				inline explicit LogicError(const std::string& msg): std::logic_error(msg) {};
		};

        /**
         * @class InvalidArgument
         * @brief provided an invalid argument
         * @note Should not used directly, is to override only
         */
		class InvalidArgument: std::invalid_argument {
			public:
				inline explicit InvalidArgument(const std::string& msg): std::invalid_argument(msg) {};
		};

        /**
         * @class OutOfRange
         * @brief arguments outside of expected range. Needle not in Haystack ;)
         * @note Should not used directly, is to override only
         */
		class OutOfRange: std::out_of_range {
			public:
				inline explicit OutOfRange(const std::string& msg): std::out_of_range(msg) {};
		};

        /**
         * @class RangeError
         * @brief range error in internal computation
         * @note Should not used directly, is to override only
         */
		class RangeError: std::range_error {
			public:
				inline explicit RangeError(const std::string& msg): std::range_error(msg) {};
		};

        /**
         * @class NotImplementedYet
         * @brief Sole purpose of this exception is to create already the stub and mark as incomplete, you should never get such exception in the complete library
         */
		class NotImplementedYet: std::logic_error {
			public:
				inline NotImplementedYet(): std::logic_error("Not implemented yet") {};
				inline explicit NotImplementedYet(const std::string& msg): std::logic_error(std::string("Not implemented yet: ") + msg) {};
		};

        /**
         * @class DomainError
         * @brief errors related to the library use itself
         * @note Should not used directly, is to override only
         */
		class DomainError: std::domain_error {
			public:
				inline explicit DomainError(const std::string& msg): std::domain_error(msg) {};
		};

        /**
         * @namespace ots::exception::seed
         * @brief All exceptions related to ots::Seed
         */
		namespace seed {
            /**
             * @class NoDefaultLanguageSet
             * @brief a default language is expected but not set
             */
			class NoDefaultLanguageSet: DomainError {
				public:
				inline NoDefaultLanguageSet(): DomainError("No default language set for seed type") {};
			};

            /**
             * @class LanguageNotFound
             * @brief a language expected if not found
             */
			class LanguageNotFound: OutOfRange {
				public:
					inline LanguageNotFound(): OutOfRange("Language not found") {};
			};
		}

        /**
         * @namespace ots::exception::seedjar
         * @brief All exceptions related to ots::SeedJar
         */
        namespace seedjar {

            /**
             * @class SeedNotFound
             * @brief a seed expected if not found
             */
			class SeedNotFound: OutOfRange {
				public:
					inline SeedNotFound(): OutOfRange("Seed not found") {};
			};
        }

        /**
         * @namespace ots::exception::wallet
         * @brief All exceptions related to ots::Wallet
         */
		namespace wallet {

            /**
             * @class AddressNotFound
             * @brief wallet does not contain the provided address
             */
			class AddressNotFound: OutOfRange {
				public:
					inline AddressNotFound(): OutOfRange("Address not found in wallet") {};
			};

            /**
             * @class ImportOutputs
             * @brief Import outputs failed
             */
            class ImportOutputs: InvalidArgument {
				public:
					inline explicit ImportOutputs(): InvalidArgument("Import outputs failed") {};
					inline explicit ImportOutputs(const std::string& msg): InvalidArgument(msg) {};
            };

            /**
             * @class ExportKeyImages
             * @brief export key images failed
             */
            class ExportKeyImages: DomainError {
				public:
					inline explicit ExportKeyImages(): DomainError("Import outputs failed") {};
					inline explicit ExportKeyImages(const std::string& msg): DomainError(msg) {};
            };
		}

        /**
         * @namespace ots::exception::tx
         * @brief All exceptions related Transactions in ots::Wallet, ots::TxWarning, ots::TxDescription
         */
		namespace tx {

            /**
             * @class Invalid
             * @brief the provided unsigned transaction is not valid
             */
            class Invalid: InvalidArgument {
				public:
					inline explicit Invalid(): InvalidArgument("Transaction is invalid") {};
					inline explicit Invalid(const std::string& msg): InvalidArgument(msg) {};
            };
		}

        /**
         * @namespace ots::exception::address
         * @brief All exceptions related to ots::Address
         */
		namespace address {

            /**
             * @class Invalid
             * @brief The provided string is not a valid Monero address
             */
			class Invalid: InvalidArgument {
				public:
					inline Invalid(): InvalidArgument("Not a valid Monero address") {};
			};
		}
	}
}
