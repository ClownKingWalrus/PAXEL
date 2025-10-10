#include <iostream>
#include <vector>
<<<<<<< HEAD
#include <utility>
#include <cstdlib>
#include <memory>
#include <functional>
#include <vector>
=======
#include <cstdlib>
#include <memory>
#include <functional>
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
#include "picosha2.h" // Sha256 hasher https://github.com/okdshin/PicoSHA2
#include "../mysql-connector-c++-9.4.0-winx64/include/mysql/jdbc.h"

class Utils {
    public:
         /******************************************************************************************************
         * @brief validates the users login info
         * @details Once called this function takes the user and pass and checks to see if it's
         *          a valid user it logs them in
         * @return returns a vector of strings which are their interest
         ******************************************************************************************************/
        static void Login(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase) {
            sql::mysql::MySQL_Driver* driver;
            sql::Connection* connection;
            
            //initlize user and pass
            std::string UserName = "";
            std::string UserPassword = "";

<<<<<<< HEAD
            ///testing purposes
            UserName = "Trunks";
            UserPassword = "Password";

=======
            std::cout << "Please enter Username: ";
            while (UserName.size() == 0) {
                std::getline(std::cin, UserName);
                if (UserName.size() == 0) {
                    std::cout << "Invalid input please try again: ";
                }
            }

            std::cout << "Please enter Password: ";
              while (UserPassword.size() == 0) {
                std::getline(std::cin, UserPassword);
                if (UserPassword.size() == 0) {
                    std::cout << "Invalid input please try again: ";
                }
            }
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
            std::string hashedPass = picosha2::hash256_hex_string(UserPassword);
            UserPassword.clear(); //no except this cannot fail

            try {
                
                driver = sql::mysql::get_mysql_driver_instance();

                //simple test
                connection = driver->connect(sqlIp, sqlUser, sqlPassword);
                connection->setSchema(sqlDatabase);
<<<<<<< HEAD
                std::cout << "connected to sql\n";
=======
                std::cout << "connected to sql\n"; 
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
                
                //create statement
                sql::Statement* statement;
                statement = connection->createStatement();
                //create a result object
                sql::ResultSet* res;

                //this statement should be optimized this is essentially a select * statement
                res = statement->executeQuery("SELECT UserName, UserPass FROM user");
                int i = 0;
                bool foundMatch = false;
                while (res->next()) {
                    std::string name = res->getString("UserName");
                    std::string pass = res->getString("UserPass");
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
<<<<<<< HEAD
                delete connection;
=======
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b

            } 
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }
<<<<<<< HEAD
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

        /******************************************************************************************************
         * @brief Gets around 50 threads
         * @details calls sql and pulls 10
         * @return returns UserID, threadNam
         ******************************************************************************************************/
        static std::vector<std::pair<std::string, std::string>> ThreadUpdate(std::string sqlIp, std::string sqlUser, std::string sqlPassword, std::string sqlDatabase, std::string boardID) {
            std::vector<std::pair<std::string, std::string>> threadVect;
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

            std::string query = "SELECT Threads.ThreadName, Threads.UserID FROM Threads WHERE Threads.BoardID = ";
            query += boardID;

            std::cout << query;

            //this statement should be optimized this is essentially a select * statement
            res = statement->executeQuery(query);
            int i = 0;
            while (res->next() && i < 10) {
                std::string threadName = res->getString("ThreadName");
                std::string userID = res->getString("UserID");
                threadVect.push_back(std::pair<std::string, std::string>(userID, threadName));
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
};
=======

            delete connection;

        }


};
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
