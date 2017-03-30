/*
Joshua Sander
10-7-2016
CS163
Program 1

This program takes console input from a user and creates a list of class subjects.  
Each subject created also contains a list of ways of help for that subject, 
to be input through main by the user.  
A way of help is represented as an object, which contains data on the way of help 
(e.g. time, location) and functions for managing and displaying that data.  
Error states are returned to main via bool or int values 
while the values of the data themselves are printed by the classes that contain them.
*/

#include"subject_list.h"
#include"subject_info.h"
#include"help_info.h"
#include<iostream>
#include<cstring>

using namespace std;

const int max_char = 100;

void add_subject(subject_list & master_list);
void view(subject_list & master_list);
void add_way(subject_list & master_list);
void edit_way(subject_list & master_list);
void remove_subject(subject_list & master_list);


//A switch nested inside a do-while loop keeps the program running until the user chooses to exit
int main() {

	char user_choice;
	subject_list master_list;

	cout << endl;
	cout << "Welcome to the class assistance directory." << endl << endl;

	do 
	{
		cout << "Please choose an option: " << endl;
		cout << "A: Add a subject to the list" << endl;
		cout << "B: Add ways of help to a subject" << endl;
		cout << "C: View help information from a subject" << endl;
		cout << "D: Edit help information from a subject" << endl;
		cout << "E: Remove a subject from the list" << endl;
		cout << "F: Exit the program" << endl;

		cin >> user_choice;
		cin.ignore();
		cout << endl;

		switch (user_choice) 
		{	
			case 'a':
			case 'A':
				add_subject(master_list);
				break;
			case 'b':
			case 'B':
				add_way(master_list);
				break;
			case 'c':
			case 'C':
				view(master_list);
				break;
			case 'd':
			case 'D':
				edit_way(master_list);
				break;
			case 'e':
			case 'E':
				remove_subject(master_list);
				break;
			case 'f':
			case 'F':
				break;
			default:
				cout << "This is not a valid input." << endl;

		}
	}while (user_choice != 'f' && user_choice != 'F');

	return 0;

}


//This allows a user to input a subject into the list.
//It gives an error message if the subject already exists 
//and doesn't allow the user to add it
//It passes the address of the master list from main for access.
void add_subject(subject_list & master_list) 
{
	char subject_name[max_char];

	cout << "Please enter a subject name" << endl;
	cin.getline(subject_name,max_char, '\n');
	cout << endl;

	if (master_list.add_subject(subject_name) < 1)
	{
		cout << "This subject is already in the list!" << endl;
	}
	cout << endl;
	
	return;
}


//This allows the user to view either all ways of help for a chosen subject
//or only the ways of help rated 8 or above for the given subject.
//An error message is printed if the subject does not exist or
//if there are no ways of help stored for that subject
//It passes the address of the master list from main for access.
void view(subject_list & master_list) 
{
	char subject_name[max_char];
	char choice;

	if (master_list.view_list() < 1)
	{
		cout << "There are no subjects in the list!" << endl << endl;
		return;
	}

	cout << endl;

	cout << "Which of these subjects would you like to see?" << endl;
	cin.getline(subject_name,max_char,'\n');
	cout << endl;

	if (!master_list.search(subject_name))
	{
		cout << "This is not in the list!" << endl << endl;
	}

	else
	{
		do
		{
			cout << "Choose between seeing: " << endl;
			cout << "A: all ways of help" << endl;
			cout << "B: highest rated ways of help" << endl;
			cin.get(choice);
			cin.ignore();
			cout << endl << endl;

			switch(choice) 
			{
				case 'a':
				case 'A':
				case 'b':
				case 'B':
					break;
				default:
					cout << "Invalid choice!" << endl;
					choice = 'x';
			}
		} while (choice == 'x');

		if (master_list.view_ways(subject_name,choice) < 1)
		{
			cout << "No ways to display!" << endl << endl;
		}
	}
	
	return;
}


//This allows the user to add a way of help for a chosen subject.
//It gives an error message if there are no subjects
//or the subject does not exist.
//If no error occurs, the user puts their new data into local variables:
//static arrays and an int variable.
//Those values are passed into a local object of the ways of help.
//Then, the address of that object is passed into the "add_help_way" function.
//A copy function within the added node will copy the information from this local object
//before this local object goes out of scope when returning to main, thus destroying its content.
//It passes the address of the master list from main for access.
void add_way(subject_list & master_list) 
{
	char subject_choice[max_char];
	char h_type[max_char], h_time[max_char], h_location[max_char], h_contacts[max_char];
	int rating;

	if (master_list.view_list() < 1)
	{
		cout << "There are no subjects in the list!" << endl << endl;
		return;
	}
	cout << endl;

	cout << "Which of these subjects would you like to add help to?" << endl;
	cin.getline(subject_choice,max_char,'\n');
	cout << endl;

	if (!master_list.search(subject_choice))
	{
		cout << "This is not in the list!" << endl;
		return;
	}

	cout << "Enter the way of getting help" << endl;
	cin.getline(h_type,max_char,'\n');
	cout << "Enter the hours for this way" << endl;
	cin.getline(h_time,max_char,'\n');
	cout << "Enter the rating for its usefullness" << endl;
	cin >> rating;
	cin.ignore();
	cout << "Enter the location for this way" << endl;
	cin.getline(h_location,max_char,'\n');
	cout << "Enter the contact info for this way" << endl;
	cin.getline(h_contacts,max_char,'\n');
	cout << endl;

	help_info test(h_type,h_time,rating,h_location,h_contacts);

	master_list.add_help_way(subject_choice, test);	
	
	return;
}


//This allows a user to edit the rating for a way of help
//or delete all ways of help with a score lower than 4.
//It gives an error message if there are no subjects in the list,
//or if the input subject is not in the list,
//or if the way of help is not in the list.
//It passes the address of the master list from main for access.
void edit_way(subject_list & master_list) 
{
	char subject_name[max_char];
	char way_name[max_char];
	char choice;
	int rating;

	if (master_list.view_list() < 1)
	{
		cout << "There are no subjects in the list!" << endl << endl;
		return;
	}
	cout << endl;

	cout << "For which of these subjects would you like to edit the help information?" << endl;
	cin.getline(subject_name,max_char,'\n');
	
	if (!master_list.search(subject_name))
	{
		cout << "This is not in the list!" << endl;
		return;
	}

	cout << endl << endl;
	cout << "Current ways:" << endl;
	cout << endl;

	do
	{
		if (master_list.view_way_names(subject_name) < 1)
		{
			cout << "No ways of help exist for this subject!" << endl << endl;
			return;
		}
		cout << endl;

		cout << "Choose between: " << endl;
		cout << "A: Edit the rating for a way" << endl;
		cout << "B: Delete all ways with a score lower than 4" << endl;
		cout << "C: Cancel edit" << endl;
		cin.get(choice);
		cin.ignore();
		cout << endl;

		switch(choice)  
		{
			case 'a':
			case 'A':
			case 'b':
			case 'B':
			case 'C':
			case 'c':
				break;
			default:
				cout << "Invalid choice!" << endl;
				choice = 'x';
		}
	} while (choice == 'x');

	if (choice == 'a' || choice == 'A') 
	{
		cout << "For which of these ways of help would you like to edit the rating?" << endl;
		cin.getline(way_name,max_char, '\n');

		if (!master_list.find_way(subject_name,way_name))
		{
			cout << "This way is not in the list!" << endl;
		}

		else
		{
			cout << "What is the new rating?" << endl;
			cin >> rating;

			master_list.edit_help_rating(subject_name, way_name, rating);
		}
	}
	else if (choice == 'b' || choice == 'B')
	{
		if (master_list.delete_low(subject_name) < 1)
		{
			cout << "There are no low scores in this category!" << endl << endl;
		}
		else
		{
			cout << "Low scoring ways of help removed!" << endl << endl;
		}
		
	}
	
	return;
}


//This extra function allows the user to remove a subject from their list.
//It gives an error message if the list is empty
//or the input subject is not in the list.
//It passes the address of the master list from main for access.
void remove_subject(subject_list & master_list)
{
	char subject_name[max_char];

	if (master_list.view_list() < 1)
	{
		cout << "There are no subjects in the list!" << endl << endl;
		return;
	}
	cout << endl;
	
	cout << "Which of these subjects would you like to remove?" << endl << endl;

	cin.getline(subject_name,max_char,'\n');
	cout << endl;

	if (master_list.remove(subject_name) == 0)
	{
		cout << "This subject is not in your list!" << endl << endl;
	}
	else
	{
		cout << "Subject removed!" << endl << endl;
	}

	return;
}
