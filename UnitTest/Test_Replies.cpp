#include <gtest/gtest.h>
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

TEST(ReplyTest, SQLInject_One) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    Utils::CreateReplyTest(proc::ip, proc::user, proc::password, proc::db, "62", "Test Comment 1", "");
    Utils::CreateReplyTest(proc::ip, proc::user, proc::password, proc::db, "62", "Test Comment 2", "30");
    //EXPECT_TRUE(Utils::FindGoogleTestReply(proc::ip, proc::user, proc::password, proc::db,0));
}




TEST(ReplyTest, NormalComment) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::FindGoogleTestReply(proc::ip, proc::user, proc::password, proc::db, 0));
}


TEST(ReplyTest, ReplyComment) {
    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    EXPECT_TRUE(Utils::FindGoogleTestReply(proc::ip, proc::user, proc::password, proc::db,30));
}

