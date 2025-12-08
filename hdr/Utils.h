#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "picosha2.h" // Sha256 hasher https://github.com/okdshin/PicoSHA2
#include "../mysql-connector-c++-9.4.0-winx64/include/mysql/jdbc.h"
#include <QByteArray>

class Utils {
    public:
    static inline std::string sessionID = "";
        static inline sql::mysql::MySQL_Driver* driver = nullptr;
        static inline sql::Connection* connection = nullptr;

        static void InitSql(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase) {
            driver = sql::mysql::get_mysql_driver_instance();
            connection = driver->connect(sqlIp, sqlUser, sqlPassword);
            connection->setSchema(sqlDatabase);
        }

        static sql::Connection* GetConn() {
            return connection;
        }

        static void Close() {
            if (connection) {
                try {
                    connection->close();
                } catch (...) {
                    std::cerr << "error on closing connection\n";
                }
                delete connection;
                connection = nullptr;
            }
        }

         /******************************************************************************************************
         * @brief validates the users login info
         * @details once called a sql check is peformed user and pass, then it sets sessionID for session
         * @return void
         ******************************************************************************************************/
        static bool Login(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string UserName, std::string UserPassword) {
            try {

                sql::PreparedStatement* pstmtgetSalt;
                pstmtgetSalt = connection->prepareStatement("SELECT User.Salt FROM User WHERE Username = ?");
                pstmtgetSalt->setString(1, UserName);
                std::string salt;
                sql::ResultSet* res1 = pstmtgetSalt->executeQuery();
                if (res1->next()) {
                    std::cout << "\ngot salt\n";
                    salt = res1->getString("Salt");
                } else {
                    return false;
                }


                std::string hashedPass = picosha2::hash256_hex_string((UserPassword+salt));
                std::cout << "\nhashed pass: " << hashedPass << "\n";
                //create statement
                sql::PreparedStatement* statement;
                //create a result object
                sql::ResultSet* res;

                //this statement should be optimized this is essentially a select * statement
                statement = connection->prepareStatement("SELECT User.Username, User.Password FROM User WHERE User.Username COLLATE utf8mb4_general_ci = ? AND User.Password = ?");
                statement->setString(1, UserName);
                statement->setString(2, hashedPass);
                res = statement->executeQuery();
                std::cout << "\nTEST1\n";
                bool foundMatch = false;
                if (res->next()) {
                    std::string name = res->getString("Username");
                    std::string pass = res->getString("Password");
                    foundMatch = true;
                    std::cout << "Login found matching user and pass\n";
                } else {
                    std::cout << "no login found\n";
                }
                std::cout << "\nTEST1\n";

                UserPassword.clear(); //no except this cannot fail
                sql::PreparedStatement* pstmt;

                if (foundMatch) { //create a session token
                    std::srand(static_cast<unsigned int>(std::time(nullptr)));
                    int min = 1000;
                    int max = 999999999;
                    int randomNumber = min + (std::rand() % (max - min + 1));
                    std::string token = std::to_string(randomNumber);
                    token += UserName;
                    token = picosha2::hash256_hex_string(token);

                    pstmt = connection->prepareStatement(
                        "UPDATE User SET User.SessionID = ? WHERE User.Username = ?"
                        );
                    pstmt->setString(1, token);
                    pstmt->setString(2, UserName);
                    pstmt->execute();
                    sessionID = token;
                    delete res1;
                    delete pstmtgetSalt;
                    delete pstmt;
                    delete res;
                    delete statement;
                    return true;


                }
                delete res1;
                delete pstmtgetSalt;
                delete statement;

            } 
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return false;
        }

        /******************************************************************************************************
         * @brief validates if user is ALREADY logged in
         * @details Once called a sql check for the session token is peformed
         * @return returns the userName and UUID
         ******************************************************************************************************/
        static std::pair<std::string, int> SessionTokenCheck(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string sessionToken) {
            try {

                sql::PreparedStatement* pstmtbdID = connection->prepareStatement(
                    "SELECT User.UserName, User.UserID FROM User WHERE SessionID = ?"
                    );

                pstmtbdID->setString(1, sessionToken);
                sql::ResultSet* res1 = pstmtbdID->executeQuery();
                std::string sqlUserName = "";
                int sqlUUID = -1;

                if (res1->next()) {
                    sqlUserName = res1->getString("UserName");
                    sqlUUID = res1->getInt("UserID");
                }

                delete res1;
                delete pstmtbdID;
                std::pair<std::string, int> credentials;
                credentials.first = sqlUserName;
                credentials.second = sqlUUID;
                return credentials;
            }

            catch(sql::SQLException& e) {
                std::cerr << "IN AUTHENTICATION : " << e.what() << std::endl;
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            std::cerr << "\n\nFAILED TO GET USER CREDENTIALS\n\n";
            return {"", -1};

        }

        static void AddInterest(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase,
                                std::vector<std::string> interestList) {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            std::cout << "FOREVER TOGETHJER\n";

            try {

                if (userCred.second == -1) {return;}

                sql::PreparedStatement* pstmt2 = connection->prepareStatement(
                    "INSERT INTO UserInterests (UserID, InterestID) VALUES (?, ?)"
                    );
                sql::PreparedStatement* pstmt3 = connection->prepareStatement(
                    "DELETE FROM UserInterests WHERE UserID = ? AND InterestID = ?"
                    );

                for (const auto& interestID : interestList) {
                    pstmt3->setInt(1, userCred.Second);
                    pstmt3->setString(2, interestID);
                    pstmt3->executeUpdate();
                }
                    

                for (const auto& interestID : interestList) {
                    pstmt2->setInt(1, userCred.second);
                    pstmt2->setString(2, interestID);
                    pstmt2->executeUpdate(); //insert alot of interest if need be
                }

                delete pstmt2;
                delete pstmt3;
            }

            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

        }

        //this function purely serves for CreateProfile as we dont generate session tokens until user logins
        static void AddInterest(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase,
                                std::vector<std::string> interestList, std::string userName) {

            try {


                sql::PreparedStatement* getUUID = connection->prepareStatement(
                    "SELECT User.UserID FROM User WHERE User.Username = ?");
                getUUID->setString(1, userName);

                //create a result object
                sql::ResultSet* resUUID;

                resUUID = getUUID->executeQuery();
                int userID = -1;
                if (resUUID->next()) {
                    userID = resUUID->getInt("UserID");
                }

                delete resUUID;
                delete getUUID;

                if (userID == -1) {
                    return;
                }

                sql::PreparedStatement* pstmt2 = connection->prepareStatement(
                    "INSERT INTO UserInterests (UserID, InterestID) VALUES (?, ?)"
                    );

                for (const auto& interestID : interestList) {
                    pstmt2->setInt(1, userID);
                    pstmt2->setString(2, interestID);
                    pstmt2->executeUpdate(); //insert alot of interest if need be
                }

                delete pstmt2;
            }

            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

        }

        //this function purely serves for CreateProfile as we dont generate session tokens until user logins
        static void AddInterestTest(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase,
                                std::vector<std::string> interestList) {

            sql::mysql::MySQL_Driver* driver;
            sql::Connection* connection;

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {
                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);

                sql::PreparedStatement* getUUID = connection->prepareStatement(
                    "SELECT User.UserID FROM User WHERE User.Username = ?");
                getUUID->setString(1, userCred.first);

                delete getUUID;

                if (userCred.second == -1) {
                    return;
                }

                sql::PreparedStatement* pstmt2 = connection->prepareStatement(
                    "INSERT INTO UserInterests (UserID, InterestID) VALUES (?, ?)"
                    );

                for (const auto& interestID : interestList) {
                    pstmt2->setInt(1, userCred.second);
                    pstmt2->setString(2, interestID);
                    pstmt2->executeUpdate(); //insert alot of interest if need be
                }

                delete pstmt2;
                delete connection;
            }

            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

        }


        static void CreateProfile(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase,
                                  std::string UserName, std::string UserPassword, std::string Email) {

            try {


                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                std::srand(static_cast<unsigned int>(std::time(nullptr)));
                int min = 1000;
                int max = 999999999;
                int randomNumber = min + (std::rand() % (max - min + 1));

                std::string salt = UserName;
                salt += std::to_string(randomNumber);
                salt += UserPassword;
                salt = picosha2::hash256_hex_string(salt);

                std::string hashedPass = picosha2::hash256_hex_string((UserPassword+salt));
                UserPassword.clear(); //no except this cannot fail

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "INSERT INTO User (Username, Password, Email, Age, DayCreated, Salt) VALUES (?, ?, ?, ?, ?, ?)" //use nullable values for ease of use
                    );

                pstmt->setString(1, UserName);
                pstmt->setString(2, hashedPass);
                pstmt->setString(3, Email);
                pstmt->setInt(4, 1);
                pstmt->setString(5, "2025-10-10");
                pstmt->setString(6, salt);
                pstmt->executeUpdate();
                pstmt->clearParameters();
                pstmt->clearAttributes();
                hashedPass.clear();

                delete pstmt;
                delete statement;
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
        }

        static void CreateBoard(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase,std::string BoardName, std::vector<std::string> interestList) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {


                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "INSERT INTO Board (BoardName, DayCreated) VALUES (?, ?)" //use nullable values for ease of use
                );
                pstmt->setString(1, BoardName);
                pstmt->setString(2, "2025-10-10");
                pstmt->executeUpdate();

                sql::PreparedStatement* pstmtbdID = connection->prepareStatement(
                    "SELECT BoardID FROM Board WHERE BoardName = ?"
                    );

                pstmtbdID->setString(1, BoardName);
                sql::ResultSet* res = pstmtbdID->executeQuery();
                int boardID = 0;
                std::cout << "2\n\n";

                if (res->next()) {
                    boardID = res->getInt("BoardID");
                } else {
                    return; //bad means no thread was created
                }

                sql::PreparedStatement* pstmt2 = connection->prepareStatement(
                    "INSERT INTO BoardInterests (BoardID, InterestID) VALUES (?, ?)"
                    );

                for (const auto& interestID : interestList) {
                    pstmt2->setInt(1, boardID);
                    pstmt2->setString(2, interestID);
                    pstmt2->executeUpdate(); //insert alot of interest if need be
                }

                sql::PreparedStatement* pstmtO = connection->prepareStatement(
                    "INSERT INTO UserBoards (UserID, BoardID) VALUES (?, ?)" //use nullable values for ease of use
                    );
                pstmtO->setInt(1, userCred.second);
                pstmtO->setInt(2, boardID);
                pstmtO->executeUpdate();

                delete pstmt;
                delete pstmt2;
                delete pstmtbdID;
                delete pstmtO;
                delete res;
                delete statement;
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

        }

        static void CreateThread(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase,std::string ThreadName, std::string BoardID) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "INSERT INTO Threads (ThreadName, DayCreated, BoardID, UserID) VALUES (?, ?, ?, ?)" //use nullable values for ease of use
                    );
                pstmt->setString(1, ThreadName);
                pstmt->setString(2, "2025-10-10");
                pstmt->setString(3, BoardID);
                pstmt->setInt(4, userCred.second);
                pstmt->executeUpdate();
                std::cout << "1\n\n";

                sql::PreparedStatement* pstmt2 = connection->prepareStatement(
                    "SELECT ThreadID FROM Threads WHERE ThreadName = ?"
                    );

                pstmt2->setString(1, ThreadName);
                sql::ResultSet* res = pstmt2->executeQuery();
                int threadID = 0;
                std::cout << "2\n\n";

                if (res->next()) {
                    threadID = res->getInt("ThreadID");
                } else {
                    return; //bad means no thread was created
                }

                sql::PreparedStatement* pstmt3 = connection->prepareStatement(
                    "INSERT INTO UserThreads (UserID, ThreadID) VALUES (?, ?)"
                    );

                pstmt3->setInt(1, userCred.second);
                pstmt3->setInt(2, threadID);
                pstmt3->executeUpdate();

                std::cout << "3\n\n";

                delete pstmt;
                delete pstmt2;
                delete pstmt3;
                delete statement;
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

        }






        static void SaveImageToSql(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, QByteArray byte) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //do a basic check
                if (!LoadImageFromSql(sqlIp, sqlUser, sqlPassword, sqlDatabase).isNull()) {
                    std::cerr << "Image already exist in DB\n";
                    return;
                }

                //conver to std::istream
                std::string blobStr(byte.constData(), byte.size());
                std::istringstream blobStream(blobStr);

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "INSERT INTO Image_Store (image_name, image_data, UserID) VALUES (?, ?, ?)" //use nullable values for ease of use
                    );
                pstmt->setString(1, "NotNeededField");
                pstmt->setBlob(2, &blobStream);
                pstmt->setInt(3, userCred.second);
                pstmt->executeUpdate();
                std::cout << "1\n\n";

                delete pstmt;
                delete statement;
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

        }




        static QByteArray LoadImageFromSql(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "SELECT image_data FROM Image_Store WHERE UserID = ?" //use nullable values for ease of use
                    );
                pstmt->setInt(1, userCred.second);

                sql::ResultSet* res = pstmt->executeQuery();
                std::istream* imageBlob;

                if (res->next()) {
                    imageBlob = res->getBlob("image_data");
                } else {
                    return {}; //bad means no thread was created
                }

                const std::streamsize bufferSize = 4096;
                std::vector<char> buffer(bufferSize);

                QByteArray byte;
                while (true) {
                    imageBlob->read(buffer.data(), bufferSize);
                    std::streamsize count = imageBlob->gcount();
                    if (count > 0) {
                        byte.append(buffer.data(), count);
                    }
                    if (count < bufferSize) {
                        break; // reached end of blob
                    }
                }

                delete pstmt;
                delete statement;
                return byte;

            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return {};
        }



        static QByteArray LoadImageFromSql(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, int userID) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {


                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "SELECT image_data FROM Image_Store WHERE UserID = ?" //use nullable values for ease of use
                    );
                pstmt->setInt(1, userID);

                sql::ResultSet* res = pstmt->executeQuery();
                std::istream* imageBlob;

                if (res->next()) {
                    imageBlob = res->getBlob("image_data");
                } else {
                    return {}; //bad means no thread was created
                }

                const std::streamsize bufferSize = 4096;
                std::vector<char> buffer(bufferSize);

                QByteArray byte;
                while (true) {
                    imageBlob->read(buffer.data(), bufferSize);
                    std::streamsize count = imageBlob->gcount();
                    if (count > 0) {
                        byte.append(buffer.data(), count);
                    }
                    if (count < bufferSize) {
                        break; // reached end of blob
                    }
                }
                std::cout << "IN UTIL++ \n" << byte.isNull() << "\n\n\n";

                delete pstmt;
                delete statement;
                return byte;

            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return {};
        }


        static int GetUserIDFromBoardID(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, int BoardID) {


            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "SELECT UserID FROM UserBoards WHERE BoardID = ?" //use nullable values for ease of use
                    );
                pstmt->setInt(1, BoardID);

                sql::ResultSet* res = pstmt->executeQuery();
                int userID;
                if (res->next()) {
                    userID = res->getInt("UserID");
                }

                delete res;
                delete statement;
                return userID;
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return -1;
        }






        static bool UsernameChecker(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string UN) {


            //set Username
            std::string UserName = UN;

            if (UserName == "") {
                return false; //bad string
            }

            try {

                //create statement
                sql::PreparedStatement* statement;
                //create a result object
                sql::ResultSet* res;

                //this statement should be optimized this is essentially a select * statement
                statement = connection->prepareStatement("SELECT User.Username FROM User WHERE User.Username COLLATE utf8mb4_general_ci = ?");
                statement->setString(1, UserName);

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery();
                if (res->next()) { //implies its true as if there is one that means we have a match
                    delete res;
                    delete statement;
                    return true;
                }
                delete res;
                delete statement;
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return false; //assuming somthing failed we will return false
        }

        static bool EmailChecker(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string EM) {


            //initlize user and pass
            std::string Email = EM;

            if (Email == "") {
                return false; //bad string
            }


            try {

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
                        return true;
                    }
                delete res;
                delete statement;
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return false; //assuming somthing failed we will return false
        }


        static void ThreadLike(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string threadID) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {

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
                user += std::to_string(userCred.second);
                user += "'";

                query += user;

                std::cout << query << "\n";

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(query);
                if (res->next()) {
                    std::cout << "User already liked\n";
                } else {
                    std::string query = "INSERT INTO LikeThreads (UserID, ThreadID) VALUES ('";
                    query += std::to_string(userCred.second);
                    query += "','";
                    query += threadID;
                    query += "')";
                    std::cout << "LIKING: \n" << query << "\n";
                    statement->executeUpdate(query);

                }
                delete res;
                delete statement;
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
        }
        catch(sql::SQLException& e) {
            std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
            std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
            std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        }
        return threadVect;
    }

        static std::vector<std::pair<std::string, std::string>> BoardUpdate(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase) {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);
            std::vector<std::pair<std::string, std::string>> boardVect;
            try {

                //create statement
                sql::PreparedStatement* statement = connection->prepareStatement(
                    "SELECT DISTINCT Board.BoardID, Board.BoardName FROM Board "
                    "JOIN BoardInterests ON Board.BoardID = BoardInterests.BoardID "
                    "JOIN UserInterests ON UserInterests.InterestID = BoardInterests.InterestID "
                    "WHERE UserInterests.UserID = ?"); // very long easier to read like so
                statement->setInt(1, userCred.second);
                //create a result object
                sql::ResultSet* res;

                res = statement->executeQuery();

                // statement gets all the boards and loads them onto the window
                while (res->next()) {
                    std::string boardID = res->getString("BoardID");
                    std::string boardName = res->getString("BoardName");
                    boardVect.push_back(std::make_pair(boardID, boardName));
                }

                delete res;
                delete statement;
            }
            catch (sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

            return boardVect;
        }

        static bool BoardNameCheck(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string BoardName) {


            //set Username
            std::string BN = BoardName;

            if (BN == "") {
                return false; //bad string
            }

            try {
                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string arg = "SELECT Board.BoardName FROM Board WHERE Board.BoardName = '" + BN + "'";

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(arg);
                if (!res->next()) { //implies its true as if there is one that means we have a match
                    delete res;
                    delete statement;
                    return true;
                }
                delete res;
                delete statement;
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

        static bool ThreadNameCheck(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string ThreadName) {

            //set Username
            std::string BN = ThreadName;

            if (BN == "") {
                return false; //bad string
            }

            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string arg = "SELECT Threads.ThreadName FROM Threads WHERE Threads.ThreadName = '" + BN + "'";

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(arg);
                if (!res->next()) { //implies its true as if there is one that means we have a match
                    delete res;
                    delete statement;
                    return true;
                }
                delete res;
                delete statement;
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

        static std::vector<std::pair<std::string, std::string>> GetInterestButtons(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase) {
            std::vector<std::pair<std::string, std::string>> boardVect;
            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                // Adjust this query to match your actual table/column names
                std::string query = "SELECT Interests.InterestName, Interests.InterestID FROM Interests";
                res = statement->executeQuery(query);

                // statement gets all the boards and loads them onto the window
                while (res->next()) {
                    std::string InterestName = res->getString("InterestName");
                    std::string InterestID = res->getString("InterestID");
                    boardVect.push_back(std::make_pair(InterestName, InterestID));
                }

                delete res;
                delete statement;
            }
            catch (sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

            return boardVect;
        }

        static std::vector<std::pair<std::string, std::string>> GetOwnBoards(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            std::vector<std::pair<std::string, std::string>> boardVect;
            try {


                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                // Adjust this query to match your actual table/column names
                std::string query = "SELECT Board.BoardID, Board.BoardName FROM Board JOIN UserBoards ON Board.BoardID = UserBoards.BoardID Where UserBoards.UserID = '" + std::to_string(userCred.second) + "'";
                res = statement->executeQuery(query);

                // statement gets all the boards and loads them onto the window
                while (res->next()) {
                    std::string boardID = res->getString("BoardID");
                    std::string boardName = res->getString("BoardName");
                    boardVect.push_back(std::make_pair(boardID, boardName));
                }

                delete res;
                delete statement;
            }
            catch (sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

            return boardVect;
        }

        static bool UserInterestCheck(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::vector<std::string> interestList) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                int size = interestList.size();
                for(int i = 0; i < size; i++) {

                    bool testing = false;

                std::string arg = "SELECT * FROM UserInterests WHERE UserInterests.UserID = '" + std::to_string(userCred.second) + "' AND UserInterests.InterestID = '" + interestList.at(i) + "'";
                    std::cerr << arg << "\n";
                    //this statement should be optimized this is essentially a select * statement
                    res = statement->executeQuery(arg);
                    if (!res->next()) { //implies its true as if there is one that means we have a match
                        testing = true;
                    }
                    delete res;
                    delete statement;
                    return testing;
                }
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;

            }
            return false;
        }

        //this function purely serves for CreateProfile as we dont generate session tokens until user logins
        static bool UserInterestCheck(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::vector<std::string> interestList, std::string userName) {

            try {

                sql::PreparedStatement* getUUID = connection->prepareStatement(
                    "SELECT User.UserID FROM User WHERE User.Username = ?");
                getUUID->setString(1, userName);

                //create a result object
                sql::ResultSet* resUUID;

                resUUID = getUUID->executeQuery();
                std::string userID = "";
                if (resUUID->next()) {
                    userID = resUUID->getString("UserID");
                }

                delete resUUID;
                delete getUUID;

                if (userID == "") {
                    return false;
                }
                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                int size = interestList.size();
                for(int i = 0; i < size; i++) {



                std::string arg = "SELECT * FROM UserInterests WHERE UserInterests.UserID = '" + userID + "' AND UserInterests.InterestID = '" + interestList.at(i) + "'";

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery(arg);
                if (!res->next()) { //implies its true as if there is one that means we have a match
                    delete res;
                    delete statement;
                    return true;
                }
                delete res;
                delete statement;
                }
            }
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;

            }
            return false;
        }

        static std::vector<std::vector<std::string>> RepliesUpdate(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string threadID) {
            std::vector<std::vector<std::string>> commentVect;
            try {

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
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "INSERT INTO Comments (ThreadID, UserID, CommentName, CommentReply) VALUES ('";
                //placeholder for commentID - needs to be original
                query += threadID;
                query += "','";
                query += std::to_string(userCred.second);
                query += "','";
                query += commentName;
                query += "','";
                query += commentReply;
                query += "')";

                statement->executeUpdate(query);
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return;
        }

        static void ThreadFollow(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string threadID) {

            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT * FROM UserThreads WHERE UserID = '";
                query += std::to_string(userCred.second);
                query += "' AND ThreadID = '";
                query += threadID;
                query += "'";
                std::cout << "\nTest: " << query << "\n";

                res = statement->executeQuery(query);
                if (res->next())
                {
                    std::string query = "DELETE FROM UserThreads WHERE UserID = '";
                    query += std::to_string(userCred.second);
                    query += "' AND ThreadID = '";
                    query += threadID;
                    query += "'";
                    std::cout << "No longer following" << std::endl;
                    statement->executeUpdate(query);
                }
                else
                {
                    std::string query = "INSERT INTO UserThreads (UserID, ThreadID) VALUES ('";
                    query += std::to_string(userCred.second);
                    query += "','";
                    query += threadID;
                    query += "')";
                    std::cout << "Now following" << std::endl;
                    statement->executeUpdate(query);
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return;
        }

        static void SendDM(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string msgRecipient, std::string msg)
        {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                time_t currentTime = time(0);
                tm* time = localtime(&currentTime);

                std::string query = "INSERT IGNORE INTO DMs (UserID1, UserID2, Message, DateTime) VALUES ('";
                query += std::to_string(userCred.second);
                query += "','";
                query += msgRecipient;
                query += "','";
                query += msg;
                query += "','";

                query += std::to_string(1900 + time->tm_year);
                query += "-";
                query += std::to_string(1 + time->tm_mon);
                query += "-";
                query += std::to_string(time->tm_mday);
                query += " ";
                query += std::to_string(time->tm_hour);
                query += ":";
                query += std::to_string(time->tm_min);
                query += ":";
                query += std::to_string(time->tm_sec);
                query += "')";

                //query += "','1')";

                std::cout << query;

                statement->executeUpdate(query);
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return;
        }

        //all messages user has sent to another single user
        static std::vector<std::vector<std::string>> DMHistory(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string User2)
        {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);
            std::vector<std::vector<std::string>> DMVect;

            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT DMs.UserID1, DMs.Message, DMs.DateTime FROM DMs WHERE (DMs.UserID1 = ";
                query += std::to_string(userCred.second);
                query += " AND DMs.UserID2 = ";
                query += User2;
                query += ") OR (DMs.UserID1 = ";
                query += User2;
                query += " AND DMs.UserID2 = ";
                query += std::to_string(userCred.second);
                query += ")";

                res = statement->executeQuery(query);
                while (res->next()) {
                    std::vector<std::string> tempVect;
                    tempVect.push_back(UserIDLookup(sqlIp, sqlUser, sqlPassword, sqlDatabase, res->getString("UserID1")));
                    tempVect.push_back(res->getString("Message"));
                    tempVect.push_back(res->getString("DateTime"));
                    DMVect.push_back(tempVect);
                }

                delete res;
                delete statement;
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return DMVect;
        }

        //all users current user has a message history with
        static std::list<std::string> DMList(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase)
        {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);
            std::list<std::string> DMUsers;

            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT DMs.UserID2 FROM DMs WHERE DMs.UserID1 = ";
                query += std::to_string(userCred.second);

                res = statement->executeQuery(query);
                while (res->next()) {
                    std::vector<std::string> tempVect;
                    DMUsers.push_back(UserIDLookup(sqlIp, sqlUser, sqlPassword, sqlDatabase, res->getString("UserID2")));
                }

                query = "SELECT DMs.UserID1 FROM DMs WHERE DMs.UserID2 = ";
                query += std::to_string(userCred.second);

                res = statement->executeQuery(query);
                while (res->next()) {
                    std::vector<std::string> tempVect;
                    DMUsers.push_back(UserIDLookup(sqlIp, sqlUser, sqlPassword, sqlDatabase, res->getString("UserID1")));
                }

                DMUsers.sort();
                DMUsers.unique();

                delete res;
                delete statement;
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return DMUsers;
        }

        //return the username of everyone user is following
        static std::list<std::string> FollowingList(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase)
        {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);
            std::list<std::string> followList;

            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT Following.Followee FROM Following WHERE Following.Follower = ";
                query += std::to_string(userCred.second);

                res = statement->executeQuery(query);
                while (res->next()) {
                    std::vector<std::string> tempVect;
                    followList.push_back(UserIDLookup(sqlIp, sqlUser, sqlPassword, sqlDatabase, res->getString("Followee")));
                }

                followList.sort();

                delete res;
                delete statement;
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return followList;
        }

        //checks if username exists and returns userid
        static std::string UserLookup(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string username) {
            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT User.UserID FROM User WHERE User.Username = '";
                query += username;
                query += "'";

                res = statement->executeQuery(query);
                if (res->next())
                {
                    return res->getString("UserID");
                }
                else
                {
                    return "\0";
                }

                delete res;
                delete statement;
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return "\0";
        }

        //checks if userid exists and returns username
        static std::string UserIDLookup(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string userID) {
            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT User.Username FROM User WHERE User.UserID = '";
                query += userID;
                query += "'";

                res = statement->executeQuery(query);
                if (res->next())
                {
                    return res->getString("Username");
                }
                else
                {
                    return "\0";
                }

                delete res;
                delete statement;
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return "\0";
        }

        static std::vector<std::pair<std::string, std::string>> FollowerProfile(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string userID){
            std::vector<std::pair<std::string, std::string>> followerVect;
            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT User.Username, Following.Follower FROM User INNER JOIN Following WHERE User.UserID = Following.Follower";

                res = statement->executeQuery(query);

                while (res->next()) {
                    std::string Username = res->getString("Username");
                    std::string Follower = res->getString("Follower");
                    followerVect.push_back(std::make_pair(Follower, Username));
                }

                delete res;
                delete statement;
            }

            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return followerVect;
        }

        static std::vector<std::pair<std::string, std::string>> FolloweeProfile(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string userID){
            std::vector<std::pair<std::string, std::string>> followeeVect;
            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT User.Username, Following.Followee FROM User INNER JOIN Following WHERE User.UserID = Following.Followee";

                res = statement->executeQuery(query);

                while (res->next()) {
                    std::string Username = res->getString("Username");
                    std::string Followee = res->getString("Followee");
                    followeeVect.push_back(std::make_pair(Followee, Username));
                }

                delete res;
                delete statement;
            }

            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return followeeVect;
        }
        static std::vector<std::pair<std::string, std::string>> UserID(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase){
            std::vector<std::pair<std::string, std::string>> userVect;
            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT Username, userID FROM User";

                res = statement->executeQuery(query);

                while (res->next()) {
                    std::string Username = res->getString("Username");
                    std::string userID = res->getString("userID");
                    userVect.push_back(std::make_pair(Username, userID));
                }

                delete res;
                delete statement;
            }

            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return userVect;
        }

        static void UserFollow(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string userID) {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);
            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT * FROM Following WHERE Follower = '";
                query += std::to_string(userCred.second);
                query += "' AND Followee = '";
                query += userID;
                query += "'";

                res = statement->executeQuery(query);
                if (res->next())
                {
                    std::string query = "DELETE FROM Following WHERE Follower = '";
                    query += std::to_string(userCred.second);
                    query += "' AND Followee = '";
                    query += userID;
                    query += "'";
                    std::cout << "No longer following" << std::endl;
                    statement->executeUpdate(query);
                }
                else
                {
                    std::string query = "INSERT IGNORE INTO Following (Follower, Followee) VALUES('";
                    query += std::to_string(userCred.second);
                    query += "','";
                    query += userID;
                    query += "')";
                    std::cout << "Now following" << std::endl;
                    statement->executeUpdate(query);
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return;
        }
        static void BoardFollow(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string boardID) {
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);

            try
            {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT * FROM FollowedBoards WHERE UserID = '";
                query += std::to_string(userCred.second);
                query += "' AND BoardID = '";
                query += boardID;
                query += "'";
                std::cout << "\nTest: " << query << "\n";

                res = statement->executeQuery(query);
                if (res->next())
                {
                    std::string query = "DELETE FROM FollowedBoards WHERE UserID = '";
                    query += std::to_string(userCred.second);
                    query += "' AND BoardID = '";
                    query += boardID;
                    query += "'";
                    std::cout << "No longer following board" << std::endl;
                    statement->executeUpdate(query);
                }
                else
                {
                    std::string query = "INSERT IGNORE INTO FollowedBoards (UserID, BoardID) VALUES ('";
                    query += std::to_string(userCred.second);
                    query += "','";
                    query += boardID;
                    query += "')";
                    std::cout << "Now following board" << std::endl;
                    statement->executeUpdate(query);
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return;
        }
        static std::vector<std::pair<std::string, std::string>> BoardFollowList(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string boardID){
            std::vector<std::pair<std::string, std::string>> boardfollowVect;
            std::pair<std::string,int> userCred = SessionTokenCheck(sqlIp,sqlUser, sqlPassword, sqlDatabase, sessionID);
            try {

                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();

                //create a result object
                sql::ResultSet* res;

                std::string query = "SELECT Board.BoardName, FollowedBoards.BoardID FROM Board INNER JOIN FollowedBoards ON FollowedBoards.BoardID = Board.BoardID WHERE UserID = '";
                query += std::to_string(userCred.second);
                query += "'";
                std::cout << query << "\n";

                res = statement->executeQuery(query);

                while (res->next()) {
                    std::string BoardName = res->getString("BoardName");
                    std::string BoardID = res->getString("BoardID");
                    boardfollowVect.push_back(std::make_pair(BoardID, BoardName));
                }

                delete res;
                delete statement;
            }

            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
            return boardfollowVect;
        }
    };
