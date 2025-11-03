#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <memory>
#include <functional>
#include <vector>
#include "picosha2.h" // Sha256 hasher https://github.com/okdshin/PicoSHA2
#include "../mysql-connector-c++-9.4.0-winx64/include/mysql/jdbc.h"
#include "../hdr/proc.h"

class Utils {
    public:
    static std::string GetUserID() {
        return "0QRPRCBBBA7PSV2";
    }
         /******************************************************************************************************
         * @brief validates the users login info
         * @details Once called this function takes the user and pass and checks to see if it's
         *          a valid user it logs them in
         * @return returns a vector of strings which are their interest
         ******************************************************************************************************/
        static void Login(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string UserName, std::string UserPassword) {
            sql::mysql::MySQL_Driver* driver;
            sql::Connection* connection;

            std::string hashedPass = picosha2::hash256_hex_string(UserPassword);
            UserPassword.clear(); //no except this cannot fail

            try {
                
                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);
                std::cout << "connected to sql\n";
                
                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery("SELECT UserName, Salt FROM User");
                int i = 0;
                bool foundMatch = false;
                while (res->next()) {
                    std::string name = res->getString("Username");
                    std::string pass = res->getString("Salt");
                    if (name == UserName && pass == hashedPass) {
                        //at this point we should call a function or implement some sort of functionailty here that actually logs the user in
                        foundMatch = true;
                        std::cout << "Login found matching user and pass\n";
                    }
                    i++;
                }

                if (foundMatch) {

                } else {
                    std::cout << "No Login found\n";
                }
                delete res;
                delete statement;
                delete connection;

            } 
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
        }


        //salt needs to be added but thats not a rn problem
        static void CreateProfile(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase,
                                  std::string UserName, std::string UserPassword, std::string Email) {

            sql::mysql::MySQL_Driver* driver;
            sql::Connection* connection;

            std::string hashedPass = picosha2::hash256_hex_string(UserPassword);
            UserPassword.clear(); //no except this cannot fail

            try {

                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string arg = "INSERT INTO User (Username, Salt, Email, UserID, Age, DayCreated) VALUES ('" + UserName + "', '" + hashedPass + "', '" + Email + "', '" + UserName + "', '1', '2025-10-10')";

                res = statement->executeQuery(arg);
                delete res;
                delete statement;
                delete connection;

            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
        }

        static bool UsernameChecker(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string UN) {
            sql::mysql::MySQL_Driver* driver;
            sql::Connection* connection;

            //set Username
            std::string UserName = UN;

            if (UserName == "") {
                return false; //bad string
            }

            try {

                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string arg = "SELECT Username FROM User WHERE Username = '" + UserName + "'";

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(arg);
                if (!res->next()) { //implies its true as if there is one that means we have a match
                    delete res;
                    delete statement;
                    delete connection;
                    return true;
                }
                delete res;
                delete statement;
                delete connection;
            }
            catch(sql::SQLException& e) {
                std::cout << "==============this error is not important but it is in UsernameChecker() in Utils.h\n";
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
                std::cout << "==============this error is not important but it is in UsernameChecker() in Utils.h\n";
            }
            return true; //assuming somthing failed we will return false
        }

        static bool EmailChecker(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string EM) {
            sql::mysql::MySQL_Driver* driver;
            sql::Connection* connection;

            //initlize user and pass
            std::string Email = EM;

            if (Email == "") {
                return false; //bad string
            }


            try {

                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);
                std::cout << "connected to sql\n";

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string arg = "SELECT Email FROM User WHERE Email = '" + Email + "'";

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(arg);
                if (!res->next()) { //implies its true as if there is one that means we have a match
                        delete res;
                        delete statement;
                        delete connection;
                        return true;
                    }
                delete res;
                delete statement;
                delete connection;

            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return false; //assuming somthing failed we will return false
        }

         /******************************************************************************************************
         * @brief Returns a set of strings coorelating with intrest on SQL witha  max of five intrest
         * @details once called from qt this sets the persons class interest
         * @return returns a vector of strings which are their interest
         ******************************************************************************************************/
        static std::vector<std::string> GatherIntrest() {
            //this can be two ways for now we will pretend there is a call made to QT
            std::vector<std::string> intrestVect;
            //some call to qt
            //QtFunctionToGiveUserOptions();

            while (intrestVect.size() > 5) {
                intrestVect.pop_back();
            }

            ////////////////////////////TEMPORARY//////////////////////////////////
            intrestVect.push_back("Music");
            intrestVect.push_back("Food");
            intrestVect.push_back("Link");
            intrestVect.push_back("fitness");

            //sets all chars to lower to make sql easier and more consistent
            for (int i = 0; i < intrestVect.size(); i++) {
                for (int j = 0; j < intrestVect[i].size(); j++) {
                    intrestVect[i][j] = std::tolower(intrestVect[i][j]);
                }
            }
            ////////////////////////////TEMPORARY//////////////////////////////////

            //Class person can now have a std::vector of strings to reference this
            return  intrestVect;
        }

        static void ThreadLike(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string threadID, std::string userID) {
            try {
                sql::mysql::MySQL_Driver* driver;
                sql::Connection* connection;

                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);
                std::cout << "connected to sql\n";

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT * FROM LikeThreads WHERE ThreadID = ";

                std::string thd = "'";
                thd += threadID;
                thd += "'";
                query += thd;

                query += " AND UserID = ";

                std::string user = "'";
                user += userID;
                user += "'";

                query += user;

                std::cout << query << "\n";

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(query);
                if (res->next()) {
                    std::cout << "User already liked\n";
                    connection->close();
                } else {
                    std::string query = "INSERT INTO LikeThreads (UserID, ThreadID) VALUES ('";
                    query += userID;
                    query += "','";
                    query += threadID;
                    query += "')";
                    std::cout << "LIKING: \n" << query << "\n";
                    statement->executeUpdate(query);
                    connection->close();

                }
                delete res;
                delete statement;
                delete connection;

            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
        }

        /******************************************************************************************************
         * @brief Gets around 50 threads
         * @details calls sql and pulls 10
         * @return returns UserID, threadNam
         ******************************************************************************************************/
        static std::vector<std::vector<std::string>> ThreadUpdate(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string boardID) {
            std::vector<std::vector<std::string>> threadVect;
            try {
            sql::mysql::MySQL_Driver* driver;
            sql::Connection* connection;

            driver = sql::mysql::get_mysql_driver_instance();

            //simple test
            connection = driver->connect(sqlIp, sqlUser, sqlPassword);
            connection->setSchema(sqlDatabase);
            std::cout << "connected to sql\n";

            //create statement
            sql::Statement* statement;
            statement = connection->createStatement();
            //create a result object
            sql::ResultSet* res;

            ///TESTING
            if (boardID.front() != '\'') {
                boardID = '\'' + boardID;
            }

            if (boardID.back() != '\'') {
                boardID += '\'';
            }

            std::string query = "SELECT Threads.ThreadName, Threads.UserID, Threads.ThreadID FROM Threads WHERE Threads.BoardID = ";
            query += boardID;

            std::cout << query << "\n";

            //this statement should be optimized this is essentially a select * statement
            res = statement->executeQuery(query);
            int i = 0;
            while (res->next() && i < 10) {
                std::string threadID = res->getString("ThreadID");
                std::string threadName = res->getString("ThreadName");
                std::string userID = res->getString("UserID");
                threadVect.push_back(std::vector<std::string>{ userID, threadName, threadID });
                i++;
            }
            delete res;
            delete statement;
            delete connection;

        }
        catch(sql::SQLException& e) {
            std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
            std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
            std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        }
        return threadVect;
    }

        static std::vector<std::pair<std::string, std::string>> BoardUpdate(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase) {
            std::vector<std::pair<std::string, std::string>> boardVect;
            try {
                sql::mysql::MySQL_Driver* driver;
                sql::Connection* connection;

                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);
                std::cout << "Connected to sql\n";

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                // Adjust this query to match your actual table/column names
                std::string query = "SELECT BoardID, BoardName FROM Board";
                res = statement->executeQuery(query);

                // statement gets all the boards and loads them onto the window
                while (res->next()) {
                    std::string boardID = res->getString("BoardID");
                    std::string boardName = res->getString("BoardName");
                    boardVect.push_back(std::make_pair(boardID, boardName));
                }

                delete res;
                delete statement;
                delete connection;
            }
            catch (sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

            return boardVect;
        }

        static std::vector<std::vector<std::string>> RepliesUpdate(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string threadID) {
            std::vector<std::vector<std::string>> commentVect;
            try {
                sql::mysql::MySQL_Driver* driver;
                sql::Connection* connection;

                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);
                std::cout << "connected to sql\n";

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                ///TESTING
                if (threadID.front() != '\'') {
                    threadID = '\'' + threadID;
                }

                if (threadID.back() != '\'') {
                    threadID += '\'';
                }

                std::string query = "SELECT Threads.ThreadName, Threads.UserID, Threads.ThreadID FROM Threads WHERE Threads.ThreadID = ";
                query += threadID;

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(query);
                while (res->next()) {
                    std::vector<std::string> tempVect;
                    tempVect.push_back(res->getString("UserID"));
                    tempVect.push_back(res->getString("ThreadName"));
                    tempVect.push_back(res->getString("ThreadID"));
                    tempVect.push_back("");
                    commentVect.push_back(tempVect);
                }

                query = "SELECT Comments.CommentName, Comments.UserID, Comments.CommentID, Comments.CommentReply FROM Comments WHERE Comments.ThreadID = ";
                query += threadID;

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(query);
                while (res->next()) {
                    std::vector<std::string> tempVect;
                    tempVect.push_back(res->getString("UserID"));
                    tempVect.push_back(res->getString("CommentName"));
                    tempVect.push_back(res->getString("CommentID"));
                    tempVect.push_back(res->getString("CommentReply"));
                    commentVect.push_back(tempVect);
                }

                delete res;
                delete statement;
                delete connection;

            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return commentVect;
        }

        ///gets comment information and sends it to sql
        static void CreateReply(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string threadID, std::string commentName, std::string commentReply)
        {
            try
            {
                sql::mysql::MySQL_Driver* driver;
                sql::Connection* connection;

                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);
                std::cout << "Connected to sql\n";

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "INSERT INTO Comments (CommentID, ThreadID, UserID, CommentName, CommentReply) VALUES ('";
                //placeholder for commentID - needs to be original
                query += "YI5JDQX64CEL35N";
                query += "','";
                query += threadID;
                query += "','";
                //placeholder for userID
                query += "8X0Y5BGOFFGJALH";
                query += "','";
                query += commentName;
                query += "','";
                query += commentReply;
                query += "')";

                statement->executeUpdate(query);
                connection->close();
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return;
        }
};
