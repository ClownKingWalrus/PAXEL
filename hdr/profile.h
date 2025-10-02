#ifndef PROFILEH
#define PROFILEH

#include <string>
#include <ctime>
#include <vector>

struct date
{
	int day;
	int month;
	int year;
};

class Profile
{
private:
	std::string username;
	std::string userpass;
	std::string f_pfp;
	std::string bio;

	date creationDate;
	date birthday;

	unsigned int uid;
	std::vector<std::string> interests;

public:
	Profile();

	std::string getUsername(void);
	std::string getUserpass(void);
	std::string getProfilePicture(void);
	std::string getBio(void);

	date getCreationDate(void);
	date getBirthday(void);

	int getUid(void);
	std::vector<std::string> getInterests(void);

	bool setUsername(std::string newUsername);
	bool setUserpass(std::string newUserpass);
	bool setProfilePicture(std::string newProfilePicture);
	bool setBio(std::string newBio);

	void setCreationDate(void);
	bool setBirthday(date newBirthday);
};

#endif