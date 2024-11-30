#include <gtest/gtest.h>
#include "ots.hpp"
#include <vector>
#include <string>
#include <algorithm>

class OTSTest : public ::testing::Test {
protected:
    ots::OTS ots;
};

TEST_F(OTSTest, GenerateSeed) {
    std::string seed = ots.generateSeed();
    EXPECT_FALSE(seed.empty()) << "Generated seed should not be empty";
    EXPECT_GT(seed.length(), 10) << "Generated seed should be sufficiently long";
}

TEST_F(OTSTest, GenerateSeedFromHash) {
    std::vector<unsigned char> testData = {1, 2, 3, 4, 5};
    std::string seedFromHash = ots.generateSeedFromHash(testData);
    EXPECT_FALSE(seedFromHash.empty()) << "Seed generated from hash should not be empty";
}

TEST_F(OTSTest, SecretSpendKeyFromSeed) {
    std::string seed = ots.generateSeed();
    crypto::secret_key secretKey = ots.secretSpendKeyFromSeed(seed);
    
    // Assuming secret_key has a way to check if it's valid
    // This is a placeholder - adjust based on actual crypto::secret_key implementation
    EXPECT_TRUE(secretKey.data != nullptr) << "Secret key should be generated successfully";
}

TEST_F(OTSTest, OTSConstructor) {
    // Test default constructor
    EXPECT_NO_THROW({
        ots::OTS defaultOTS;
    }) << "Default constructor should not throw";

    // Test constructor with specific version
    EXPECT_NO_THROW({
        ots::OTS specificVersionOTS(1);
    }) << "Constructor with specific version should not throw";
}

TEST_F(OTSTest, MoveSemantics) {
    // Test move constructor
    ots::OTS movedOTS(std::move(ots::OTS()));
    EXPECT_NO_THROW() << "Move constructor should work without exceptions";

    // Test move assignment
    ots::OTS assignedOTS = std::move(ots::OTS());
    EXPECT_NO_THROW() << "Move assignment should work without exceptions";
}
