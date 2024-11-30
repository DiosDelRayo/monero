#ifndef OTS_HPP
#define OTS_HPP

#include "version.h"
// #include "crypto/crypto.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace ots {
    struct ec_scalar {
	char data[32];
    };

    // Custom exceptions
    class OTSException : public std::runtime_error {
	public:
	    explicit OTSException(const std::string& msg) : std::runtime_error(msg) {}
    };

    class OTS {
	public:
	    explicit OTS(int version = OTS_LATEST);
	    ~OTS();  // Declare destructor

	    // Add move operations since we're using pimpl
	    OTS(OTS&&) noexcept;
	    OTS& operator=(OTS&&) noexcept;

	    // Delete copy operations
	    OTS(const OTS&) = delete;
	    OTS& operator=(const OTS&) = delete;

	    std::string generateSeed() const;
	    std::string generateSeedFromHash(const std::vector<unsigned char>& data) const;
	    // crypto::secret_key secretSpendKeyFromSeed(const std::string& seed_phrase) const;
	    ec_scalar secretSpendKeyFromSeed(const std::string& seed_phrase) const;

	private:
	    class Impl;
	    std::unique_ptr<Impl> pimpl;
	    int version;
    };

} // namespace ots

#endif // OTS_HPP
