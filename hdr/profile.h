#ifndef PROFILEH
#define PROFILEH

#include <string>
#include <ctime>

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
		std::string f_pfp;
		std::string bio;
		
		date creationDate;
		date birthday;

		int uid;
		int interests;

	public:
		Profile();

		std::string getUsername(void);
		std::string getProfilePicture(void);
		std::string getBio(void);

		date getCreationDate(void);
		date getBirthday(void);

		int getUid(void);
		int getInterests(void);

		bool setUsername(std::string newUsername);
		bool setProfilePicture(std::string newProfilePicture);
		bool setBio(std::string newBio);

		void setCreationDate(void);
		bool setBirthday(date newBirthday);
};

#endif