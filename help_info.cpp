#include"help_info.h"
#include<iostream>
#include<cstring>

using namespace std;



//Default constructor
help_info::help_info() 
{
	help_type = NULL;
	help_time = NULL;
	help_rating = 0;
	help_location = NULL;
	help_contacts = NULL;
}



//Constructor with arguments.
//This allows the user in main to enter each of the data members into this object.
//The only purpose of this object is to be copied into the actual list with the copy function.
//Thus, the object containing these values will be destroyed once the calling function returns
//to main and goes out of scope. 
help_info::help_info(char h_type[], char h_time[], int h_rating, char h_location[],char h_contacts[])
{
	
	help_type = new char[strlen(h_type) + 1];
	strcpy(help_type, h_type);
	help_time = new char[strlen(h_time) + 1];
	strcpy(help_time, h_time);
	help_rating = h_rating;
	help_location = new char[strlen(h_location) + 1];
	strcpy(help_location, h_location);
	help_contacts = new char[strlen(h_contacts) + 1];
	strcpy(help_contacts, h_contacts);
}



//Destructor checks to see if data is NULL and deletes if not.
help_info::~help_info() 
{
	if (help_type) 
	{
		delete []help_type;
	}
	if (help_time) 
	{
		delete []help_time;
	}
	if (help_location) 
	{
		delete []help_location;
	}
	if (help_contacts) {
		delete []help_contacts;
	}
}



//This function prints the data members of the chosen way of help.
void help_info::print_help(void) 
{
	//Left as void because wrapper function determines if help method is empty

	cout << "Help type: " << help_type << endl;;
	cout << "Time: " << help_time << endl;
	cout << "Rating: " << help_rating << endl;
	cout << "Location: " << help_location << endl;
	cout << "Contacts: " << help_contacts << endl;
	cout << endl;

	return;
}



//This function returns the char * of the help name so that
//calling functions can check to see if the user's choice
//matches the name of (one of) the way of help node.
char * help_info::return_help_name(void) 
{
	return help_type;
}



//This function returns the way of help rating
//so that the calling function can compare it
//to 4 and determine if it needs to be deleted or not.
int help_info::return_rating(void) 
{
	return help_rating;
}



//This function copies the information from the temporary object
//passed from main and places it into the new way of help object
//that has been added to the list.
int help_info::help_info_copy(const help_info & to_copy) 
{
	if (to_copy.help_type == NULL) //returns 0 if the object to copy is empty
	{
		return 0;
	}

	help_type = new char[strlen(to_copy.help_type) + 1];
	strcpy(help_type, to_copy.help_type);
	help_time = new char[strlen(to_copy.help_time) + 1];
	strcpy(help_time, to_copy.help_time);
	help_rating = to_copy.help_rating;
	help_location = new char[strlen(to_copy.help_location) + 1];
	strcpy(help_location, to_copy.help_location);
	help_contacts = new char[strlen(to_copy.help_contacts) + 1];
	strcpy(help_contacts, to_copy.help_contacts);

	return 1;
}



int help_info::edit_rating(int newRating) 
{
	help_rating = newRating;
	return 1;
}
