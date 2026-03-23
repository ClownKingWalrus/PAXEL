#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

TEST(LoginTest, SQLInject_One) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "' OR '1'='1 --", "Should Not Matter"));
}

TEST(LoginTest, SQLInject_Two) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Popper123", "' OR '1'='1 --"));
}

TEST(LoginTest, SQLInject_Three) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "' OR '1'='1 --", "' OR '1'='1 --"));
}

TEST(LoginTest, Correct_UserAndPass) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_TRUE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Popper123", "Popper123"));
}

TEST(LoginTest, CorrectUser_IncorrectPass) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Popper123", "Incorrect"));
}

TEST(LoginTest, IncorrectUser_CorrectPass) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Incorrect", "Popper123"));
}

TEST(LoginTest, EmptyUserField) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_TRUE(Utils::UserEmptyCheck(""));
}

TEST(LoginTest, ValidationEmptyUser) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "", "Popper123"));
}

TEST(LoginTest, EmptyPasswordField) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_TRUE(Utils::PassEmptyCheck(""));
}

TEST(LoginTest, ValidationCheckEmptyPassword) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "Popper123", ""));
}

TEST(LoginTest, Username_Length) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::UserLengthCheck("12345678912345678912"));
}

TEST(LoginTest, ValidationCheckLength) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, "12345678912345678912", "Popper123"));
}

TEST(LoginTest, Username_LengthLarge) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    std::string huge(100000, 'A');
    // Expect equality.
    EXPECT_FALSE(Utils::UserLengthCheck(huge));
}

TEST(LoginTest, ValidationCheckLengthLarge) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    std::string huge(100000, 'A');
    // Expect equality.
    EXPECT_FALSE(Utils::Login(proc::ip, proc::user, proc::password, proc::db, huge, "Popper123"));
}

//we dont actually have a valid way to test this since we dont actually have a inbuilt counter so we are going off IP rules here
TEST(LoginTest, BruteForceLogin) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    int falseCounter = 0;
    for (int i = 0; i < 5; i++) {
        Utils::Login(proc::ip, proc::user, proc::password, proc::db, "IDONTKNOW", "IDONTKNOWSUMTHIN");
        falseCounter++;
    }
    EXPECT_LT(falseCounter, 3);
}

