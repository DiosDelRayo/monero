#include <gtest/gtest.h>
#include "ots.hpp"
#include "version.h"
#include <vector>
#include <string>
#include <algorithm>

class OTSTest : public ::testing::Test {
protected:
    ots::OTS ots;
};

TEST_F(OTSTest, Version) {
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

TEST_F(OTSTest, MoveSemantics) {
    // Test move constructor
    ots::OTS movedOTS(std::move(ots::OTS()));
    EXPECT_NO_THROW() << "Move constructor should work without exceptions";

    // Test move assignment
    ots::OTS assignedOTS = std::move(ots::OTS());
    EXPECT_NO_THROW() << "Move assignment should work without exceptions";
}
