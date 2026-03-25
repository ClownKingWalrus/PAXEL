#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"
#include <vector>

//EXISTING INTERESTS - 1, 4, 5, 17

TEST(UInterestsTest, SQLInject_One) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    std:: vector<std::string> InterestVector = {"1", "4", "5", "17"};

    Utils::AddInterestTest(proc::ip, proc::user, proc::password, proc::db, InterestVector, "65");

    //EXPECT_TRUE(Utils::FindGoogleTestReply(proc::ip, proc::user, proc::password, proc::db,0));
}

TEST(UInterestsTest, Add1NewInterest) {
    std:: vector<std::string> InterestVector;
    InterestVector.push_back("2");

    Utils::AddInterestTest(proc::ip, proc::user, proc::password, proc::db, InterestVector, "65");

    std::vector<std::string> ExpectedInterests = {"1", "4","5","17","2"};

    EXPECT_TRUE(Utils::CheckDeleteInterestsTest(proc::ip, proc::user, proc::password, proc::db, ExpectedInterests));
    //EXPECT_PRED1(1, 1);
}


TEST(UInterestsTest, Add2NewInterests) {
    std:: vector<std::string> InterestVector;
    InterestVector.push_back("2");
    InterestVector.push_back("3");
    Utils::AddInterestTest(proc::ip, proc::user, proc::password, proc::db, InterestVector, "65");

    std::vector<std::string> ExpectedInterests = {"1", "4","5","17","2","3"};

    EXPECT_TRUE(Utils::CheckDeleteInterestsTest(proc::ip, proc::user, proc::password, proc::db, ExpectedInterests));

}



TEST(UInterestsTest, Add1SameInterest) {
    std:: vector<std::string> InterestVector;
    InterestVector.push_back("1");
    Utils::AddInterestTest(proc::ip, proc::user, proc::password, proc::db, InterestVector, "65");

    std::vector<std::string> ExpectedInterests = {"1", "4","5","17"};

    EXPECT_TRUE(Utils::CheckDeleteInterestsTest(proc::ip, proc::user, proc::password, proc::db, ExpectedInterests));

}




TEST(UInterestsTest, Add1Same1Different) {
    std:: vector<std::string> InterestVector;
    InterestVector.push_back("2");
    InterestVector.push_back("1");
    Utils::AddInterestTest(proc::ip, proc::user, proc::password, proc::db, InterestVector, "65");

    std::vector<std::string> ExpectedInterests = {"1","4","5","17","2"};

    EXPECT_TRUE(Utils::CheckDeleteInterestsTest(proc::ip, proc::user, proc::password, proc::db, ExpectedInterests));

}


TEST(UInterestsTest, Add2SameInterest) {
    std:: vector<std::string> InterestVector;
    InterestVector.push_back("1");
    InterestVector.push_back("4");
    Utils::AddInterestTest(proc::ip, proc::user, proc::password, proc::db, InterestVector, "65");

    std::vector<std::string> ExpectedInterests = {"1", "4","5","17"};

    EXPECT_TRUE(Utils::CheckDeleteInterestsTest(proc::ip, proc::user, proc::password, proc::db, ExpectedInterests));

}

TEST(UInterestsTest, Add0Interest) {
    std:: vector<std::string> InterestVector;
    Utils::AddInterestTest(proc::ip, proc::user, proc::password, proc::db, InterestVector, "65");

    std::vector<std::string> ExpectedInterests = {"1", "4","5","17"};

    EXPECT_TRUE(Utils::CheckDeleteInterestsTest(proc::ip, proc::user, proc::password, proc::db, ExpectedInterests));

}




