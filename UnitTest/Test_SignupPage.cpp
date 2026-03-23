#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

// TEST(SignupTest, SQLInject_One) {
//     Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

//     // Expect equality.
//     EXPECT_FALSE(Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, "' OR '1'='1 --", "Should Not Matter"));
// }

// TEST(SignupTest, SQLInject_Two) {
//     Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

//     // Expect equality.
//     EXPECT_FALSE(Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, "Popper123", "' OR '1'='1 --"));
// }

// TEST(SignupTest, SQLInject_Three) {
//     Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

//     // Expect equality.
//     EXPECT_FALSE(Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, "' OR '1'='1 --", "' OR '1'='1 --"));
// }

TEST(SignupTest, EmptyUserField) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_TRUE(Utils::UserEmptyCheck(""));
}

TEST(SignupTest, ValidationEmptyUser) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, "", "Popper123", "Unique@gmail.com"));
}

TEST(SignupTest, EmptyPasswordField) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_TRUE(Utils::PassEmptyCheck(""));
}

TEST(SignupTest, ValidationCheckEmptyPassword) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, "Popper123", "", "Unique@gmail.com"));
}

TEST(SignupTest, Username_Length) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::UserLengthCheck("12345678912345678912"));
}

TEST(SignupTest, ValidationCheckLength) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, "12345678912345678912", "Popper123", "Unique@gmail.com"));
}

TEST(SignupTest, Username_LengthLarge) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    std::string huge(100000, 'A');
    // Expect equality.
    EXPECT_FALSE(Utils::UserLengthCheck(huge));
}

TEST(SignupTest, ValidationCheckLengthLarge) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    std::string huge(100000, 'A');
    // Expect equality.
    EXPECT_FALSE(Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, huge, "Popper123", "Unique@gmail.com"));
}

TEST(SignupTest, EmailEmpty) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_TRUE(Utils::UserLengthCheck(""));
}

TEST(SignupTest, EmailRegex) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_TRUE(Utils::EmailRegexChecker("Unique@gmail.com"));
}

TEST(SignupTest, EmailFailRegex) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::EmailRegexChecker("Uniquegmail.com"));
}

TEST(SignupTest, EmailFailRegex2) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::EmailRegexChecker("Unique@gmailcom"));
}

TEST(SignupTest, EmailFailRegex3) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    // Expect equality.
    EXPECT_FALSE(Utils::EmailRegexChecker("Unique Someworeds.com"));
}

//we dont actually have a valid way to test this since we dont actually have a inbuilt counter so we are going off IP rules here
TEST(SignupTest, BruteForceLogin) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    int falseCounter = 0;
    for (int i = 0; i < 5; i++) {
        Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, "IDONTKNOW", "IDONTKNOWSUMTHIN", "INVALIDEMAIL");
        falseCounter++;
    }
    EXPECT_LT(falseCounter, 3);
}
