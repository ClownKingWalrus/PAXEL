#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

TEST(FollowingTest, ProfSQLInject) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Samuel", "RandomPassword");
    Utils::UserFollow(proc::ip, proc::user, proc::password, proc::db, "4");
}

TEST(FollowingTest, BoardSQLInject) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Samuel", "RandomPassword");
    Utils::BoardFollow(proc::ip, proc::user, proc::password, proc::db, "30");
}

TEST(FollowingTest, FollowTest) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Samuel", "RandomPassword");
    EXPECT_TRUE(Utils::UserFollowTest(proc::ip, proc::user, proc::password, proc::db, "4"));
    Utils::UserFollow(proc::ip, proc::user, proc::password, proc::db, "4");
}

TEST(FollowingTest, BoardTest) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Samuel", "RandomPassword");
    EXPECT_TRUE(Utils::BoardFollowTest(proc::ip, proc::user, proc::password, proc::db, "30"));
    Utils::BoardFollow(proc::ip, proc::user, proc::password, proc::db, "30");
}
