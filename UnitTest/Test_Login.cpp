#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

TEST(LoginTest, BasicSanity) {
    //Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
