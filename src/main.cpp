#include <iostream>
#include "profile.h"

int main(int argc, char* argv[])
{
	Profile a;

	//std::cout << a.getCreationDate().day << '/' << a.getCreationDate().month << '/' << a.getCreationDate().year;

	/*
	if (a.setUsername("12345678901234567"))
		std::cout << "good";
	else
		std::cout << "bad";
	*/

	a.setBirthday({ 25, 2, 2000 });
	std::cout << a.getBirthday().day << '/' << a.getBirthday().month << '/' << a.getBirthday().year;

	return 0;
}