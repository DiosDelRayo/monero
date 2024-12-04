#include <gtest/gtest.h>
#include "ots.hpp"
#include "ots-exceptions.hpp"
#include "version.h"
#include <vector>
#include <array>
#include <string>
#include <algorithm>

class OTSTest : public ::testing::Test {
protected:
    ots::OTS ots;
};

TEST_F(OTSTest, OtsVersion) {
    std::string version = ots::OTS::version();
    EXPECT_FALSE(version.empty()) << "Generated version should not be empty";
    EXPECT_TRUE(version == OTS_VERSION_STRING) << "Version string must be the same as defined int version.h";
}

TEST_F(OTSTest, OTSConstructor) {
    // Test default constructor
    EXPECT_NO_THROW({
        ots::OTS defaultOTS;
    }) << "Default constructor should not throw";

}

TEST_F(OTSTest, OtsMoveSemantics) {
    // Test move constructor
    EXPECT_NO_THROW(ots::OTS movedOTS(std::move(ots::OTS()))) << "Move constructor should work without exceptions";

    // Test move assignment
    EXPECT_NO_THROW(ots::OTS assignedOTS = std::move(ots::OTS())) << "Move assignment should work without exceptions";
}

TEST_F(OTSTest, OtsRandom) {
    ;
    EXPECT_THROW(auto r1 = ots::OTS::random(), ots::exception::NotImplementedYet) << "Move constructor should work without exceptions";
    /* TODO: enable after implementation and resolving dependencies
    auto r2 = ots::OTS::random();
    EXPECT_FALSE(r1.empty()) << "Random should have 32 bytes";
    EXPECT_FALSE(r2.empty()) << "Random should have 32 bytes";
    EXPECT_FALSE(r1 == r2) << "Randoms should not be the same";
    */
}
