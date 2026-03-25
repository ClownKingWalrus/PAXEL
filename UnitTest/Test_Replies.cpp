#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

TEST(ReplyTest, SQLInject_One) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    Utils::CreateReplyTest(proc::ip, proc::user, proc::password, proc::db, "62", "Test Comment 1", "", "65");
    Utils::CreateReplyTest(proc::ip, proc::user, proc::password, proc::db, "62", "Test Comment 2", "30", "65");
    //EXPECT_TRUE(Utils::FindGoogleTestReply(proc::ip, proc::user, proc::password, proc::db,0));
}




TEST(ReplyTest, NormalComment) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::FindGoogleTestReply(proc::ip, proc::user, proc::password, proc::db, ""));
}


TEST(ReplyTest, ReplyComment) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::FindGoogleTestReply(proc::ip, proc::user, proc::password, proc::db, "30"));
}

TEST(ReplyTest, EmptyComment) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_FALSE(Utils::CreateReplyTest(proc::ip, proc::user, proc::password, proc::db, "62", "", "", "65"));

}

TEST(ReplyTest, LongComment) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);
    //500 characters
    EXPECT_ANY_THROW(Utils::CreateReplyTest(proc::ip, proc::user, proc::password, proc::db, "62", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", "", "65"));

}

TEST(ReplyTest, WeirdComment) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_ANY_THROW(Utils::CreateReplyTest(proc::ip, proc::user, proc::password, proc::db, "62", "Weird Character: Æ", "", "65"));

}


