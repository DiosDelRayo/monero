#pragma once

#ifdef __PRETTY_FUNCTION__
#define NOT_IMPLEMENTED_YET() throw ots::exception::NotImplementedYet(__PRETTY_FUNCTION__)
#else
#define NOT_IMPLEMENTED_YET() throw ots::exception::NotImplementedYet(__func__)
#endif

#include <stdexcept>
#include <string>

namespace ots {
	namespace exception {
		class RuntimeError: std::runtime_error {
			public:
				inline RuntimeError(const std::string& msg): std::runtime_error(msg) {};
		};
		class InvalidArgument: std::invalid_argument {
			public:
				inline InvalidArgument(const std::string& msg): std::invalid_argument(msg) {};
		};
		class OutOfRange: std::out_of_range {
			public:
				inline OutOfRange(const std::string& msg): std::out_of_range(msg) {};
		};
		class NotImplementedYet: std::logic_error {
			public:
				inline NotImplementedYet(): std::logic_error("Not implemented yet") {};
				inline NotImplementedYet(const std::string& msg): std::logic_error(std::string("Not implemented yet: ") + msg) {};
		};
		class DomainError: std::domain_error {
			public:
				inline DomainError(const std::string& msg): std::domain_error(msg) {};
		};
		namespace seed {
			class NoDefaultLanguageSet: DomainError {
				public:
				inline NoDefaultLanguageSet(): DomainError("No default language set for seed type") {};
			};
			class LanguageNotFound: OutOfRange {
				public:
					inline LanguageNotFound(): OutOfRange("Language not found") {};
			};
		}
		namespace wallet {
			class AddressNotFound: OutOfRange {
				public:
					inline AddressNotFound(): OutOfRange("Address not found in wallet") {};
			};
		}
		namespace keyjar {
		}
		namespace tx {
		}
		namespace address {
			class Invalid: InvalidArgument {
				public:
					inline Invalid(): InvalidArgument("Not a valid Monero address") {};
			};
		}
	}
}
