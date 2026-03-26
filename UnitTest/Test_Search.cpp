#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

//YaervigTest 43

TEST(SearchTest, SearchByUsername) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "YaervigTest") == "43");
}

TEST(SearchTest, SearchByID) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserIDLookup(proc::ip, proc::user, proc::password, proc::db, "43") == "yaervigtest");
}

TEST(SearchTest, SearchCaseSensitivity) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "yaervigtest") == "43" &&
        Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "YAERVIGTEST") == "43");
}

TEST(SearchTest, InvalidUsername) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "imnotactuallyauser") == "\0");
}

TEST(SearchTest, EmptyUsername) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "") == "\0");
}

TEST(SearchTest, LongUsername) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == "\0");
}

TEST(SearchTest, EmojiUsername) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "🍕") == "\0");
}

TEST(SearchTest, SQLInject) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, "' OR '1'='1 --") == "\0");
}
