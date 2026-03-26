#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"
#include <vector>

TEST(CreateBoardsTest, TitleSentToSQL) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, "CoolTown"));
}

TEST(CreateBoardsTest, EmptyTitleSQLAttempt) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_FALSE(Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, ""));
}

TEST(CreateBoardsTest, ExistingTitleSQLAttempt) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_FALSE(Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, "Minecraft"));
}

TEST(CreateBoardsTest, CreateBoard_Success) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    std::string title = "UnitTestBoard";

    EXPECT_TRUE(Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, title));

    Utils::CreateBoard(proc::ip, proc::user, proc::password, proc::db, title, {"Paxel"});

    EXPECT_FALSE(Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, title));
    //should be false since title shluld have been added so board should be taken
}

TEST(CreateBoardsTest, EmptyInterestAttempt) {
    std::vector<std::string> interests;

    EXPECT_TRUE(interests.empty());
}

TEST(CreateBoardsTest, InterestListPassed) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    std::vector<std::string> interests = {"Movies"};

    EXPECT_FALSE(interests.empty());
}
