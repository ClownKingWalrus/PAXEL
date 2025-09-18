#include <iostream>
#include <vector>
#include <cstdlib>
#include <memory>
#include <functional>
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

            } 
            catch(sql::SQLException& e) {
                std::cerr << "Error connecting to MySQL: " << e.what() << std::endl;
                std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
                std::cerr << "SQLState: " << e.getSQLState() << std::endl;
            }

            delete connection;

        }


};