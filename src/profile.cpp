#define _CRT_SECURE_NO_WARNINGS
#include "profile.h"

using namespace std;

Profile::Profile()
{
	username = '\0';
	f_pfp = '\0';
	bio = '\0';

	setCreationDate();
	birthday = { 0, 0, 0 };

	uid = 0;
	interests = 0;
	
	return;
}

std::string Profile::getUsername(void)
{
	return username;
}

std::string Profile::getProfilePicture(void)
{
	return f_pfp;
}

std::string Profile::getBio(void)
{
	return bio;
}

date Profile::getCreationDate(void)
{
	return creationDate;
}

date Profile::getBirthday(void)
{
	return birthday;
}

int Profile::getUid(void)
{
	return uid;
}

int Profile::getInterests(void)
{
	return interests;
}





bool Profile::setUsername(std::string newUsername)
{
	if (newUsername.length() <= 0 || newUsername.length() > 16)
		return 0;

	//only allow letters/numbers in username
	for (int i = 0; i < newUsername.length(); i++)
		if ( (newUsername[i] < 48) || (newUsername[i] > 57 && newUsername[i] < 65) || (newUsername[i] > 90 && newUsername[i] < 97) || (newUsername[i] > 122) )
			return 0;

	username = newUsername;
	return 1;
}

bool Profile::setProfilePicture(std::string newProfilePicture)
{
	f_pfp = newProfilePicture;
	return 1;
}

bool Profile::setBio(std::string newBio)
{
	if (newBio.length() > 0 && newBio.length() <= 160)
	{
		bio = newBio;
		return 1;
	}
	return 0;
}

void Profile::setCreationDate(void)
{
	//creation date is always set to the current day
	time_t now = time(0);
	tm* time = localtime(&now);

	creationDate = { time->tm_mday, 1 + time->tm_mon, 1900 + time->tm_year };
	return;
}

bool Profile::setBirthday(date newBirthday)
{
	//vile date validation
	if(newBirthday.year / 1000 == 1 || newBirthday.year / 1000 == 2)
		if(newBirthday.month > 0 && newBirthday.month <= 12)
			if(newBirthday.day > 0 && newBirthday.day <= 31)
			{
				if (((newBirthday.month == 4 || newBirthday.month == 6 || newBirthday.month == 9 || newBirthday.month == 11) && newBirthday.day > 30) || (newBirthday.month == 2 && newBirthday.day > 29))
					return 0;

				birthday = newBirthday;
				return 1;
			}

	return 0;
}