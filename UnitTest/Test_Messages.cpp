#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

//YaervigTest 43
//Regnazo1 44
//Popper123 46

TEST(MessageTest, LoadFollowedUsers) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "YaervigTest", "awesomepassword");

    EXPECT_TRUE(!Utils::FollowingList(proc::ip, proc::user, proc::password, proc::db).empty());
}

TEST(MessageTest, NoFollowedUsers) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Popper123", "Popper123");

    EXPECT_TRUE(Utils::FollowingList(proc::ip, proc::user, proc::password, proc::db).empty());
}

TEST(MessageTest, SortedFollowList) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "YaervigTest", "awesomepassword");

    std::list test1 = Utils::FollowingList(proc::ip, proc::user, proc::password, proc::db);
    std::list test2 = test1;
    test2.sort();

    EXPECT_TRUE(test1 == test2);
}

TEST(MessageTest, LoadDMHistory) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(!Utils::DMHistory(proc::ip, proc::user, proc::password, proc::db, "44").empty());
}

TEST(MessageTest, EmptyDMHistory) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::DMHistory(proc::ip, proc::user, proc::password, proc::db, "46").empty());
}

//same messages for sender and recipient
TEST(MessageTest, DMHistoryEquality) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    std::vector test1 = Utils::DMHistory(proc::ip, proc::user, proc::password, proc::db, "46");

    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Popper123", "Popper123");
    std::vector test2 = Utils::DMHistory(proc::ip, proc::user, proc::password, proc::db, "43");

    EXPECT_TRUE(test1 == test2);
}

TEST(MessageTest, LoadDMList) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "YaervigTest", "awesomepassword");

    EXPECT_TRUE(!Utils::DMList(proc::ip, proc::user, proc::password, proc::db).empty());
}

TEST(MessageTest, EmptyDMList) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Popper123", "Popper123");

    EXPECT_TRUE(Utils::DMList(proc::ip, proc::user, proc::password, proc::db).empty());
}

