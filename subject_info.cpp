#include"subject_info.h"
#include"help_info.h"
#include<cstring>
#include<iostream>

using namespace std;



//Constructor function.
s_node::s_node()
{
	s_next = NULL;
}

//No DESTRUCTOR needed!  Subject_info class traverses and destroyes the nodes.  The nodes do not contain any dynamically allocated members.  The class in each node has it's own destructor;

subject_info::subject_info() 
{
	s_head = NULL;
}



//Traverses and destroys all of the nodes in the list of ways of help.
subject_info::~subject_info()
{
	s_node * current = s_head;

	while (s_head) 
	{
		s_head = s_head->s_next;
		delete current;
		current = s_head;
	}
}



//This searches the list of ways of help to make sure that the argument
//which is the user's input of intended way of help
//is actually in the list before the user begins adding information to edit.
//That way, if it is not in the list, the user does not waste time adding information
//that will only inevitably produce an error message.
bool subject_info::search_ways(const char way_name[])
{
	s_node * current = s_head;

	while(current)
	{
		if (strcmp(current->h_data.return_help_name(),way_name) == 0)
		{
			return true;
		}
		current = current->s_next;
	}

	return false;
}



//This function prints only the name of the way of help.
//This allows the user in the main function to see their options before
//typing in a choice.
int subject_info::print_way_name(void)
{
	s_node * current = s_head;

	if (!current)
	{
		return 0;
	}
	
	while (current)
	{
		cout << current->h_data.return_help_name() << endl;
		current = current->s_next;
	}

	return 1;
}

	

//This traverses the list and calls the print function for each
//way of help object within the nodes.  The result is all of the ways of help
//for any chosen subject are printed.
int subject_info::print_ways(void)
{
	s_node * current = s_head;

	if (s_head == NULL)
	{
		return 0;
	}

	while (current)
	{
		current->h_data.print_help();
		current = current->s_next;
	}

	return 1;
}



//Similar to the above function, this one just prints
//the ways of help that have a rating higher than 7.
int subject_info::print_best_ways(void) 
{
	s_node * current = s_head;
	
	if (s_head == NULL)
	{
		return 0;
	}

	while (current)
	{
		if (current->h_data.return_rating() > 7)
		{
			current->h_data.print_help();
		}
		current = current->s_next;
	}

	return 1;
}



//This function calls the copy function of the embedded
//ways of help class.  Its argument is the address for the
//temporary object in main containing all of the new information
//to be added to the new node.
int subject_info::add_way(help_info & new_way) 
{
	//If the object to be copied is empty, this returns an error.
	if (new_way.return_help_name() == NULL)
	{
		return 0;
	}

	//If the list is empty, this sets the head to the new node.
	if (!s_head)
	{
		s_head = new s_node;
		s_head->h_data.help_info_copy(new_way);
		s_head->s_next = NULL;
	}
	//This adds the node to an already existing list (of at least 1).
	else
	{
		s_node * new_node = new s_node;
		new_node->h_data.help_info_copy(new_way);
		new_node->s_next = s_head;
		s_head = new_node;
	}

	return 1;
}



//This uses the user's arguments of way of help name and desired score
//to call the edit function of the member class and change the existing
//score to the new one.
int subject_info::edit_rating(const char * way_name, int new_score) 
{
	s_node * current = s_head;
	
	while (current) 
	{
		if (strcmp(current->h_data.return_help_name(),way_name) == 0)
		{
			return current->h_data.edit_rating(new_score);
		}
		else 
		{
			current = current->s_next;
		}
	}

	return 0;
}	



//This function traverses the list and deletes all nodes that contain
//a way of help score of 3 or lower.
int subject_info::delete_low_scores(void) 
{
	s_node * current = s_head;
	s_node * previous;
	int tally = 0; //This totals the number of changes or nodes removed from the list.

	while (current) 
	{
		if (current->h_data.return_rating() < 4)
		{
			++tally;
			//Checks to see if the head needs to be deleted
			//If all values are less than 4, this is the only statement executed until current becomes null.
			if (current == s_head)
			{
				s_head = s_head->s_next;
				delete current;
				current = s_head;
			}
			//If low score node was found that was not head, this removes it and links the adjacent nodes.
			else
			{
				previous->s_next = current->s_next;
				delete current;
				current = previous->s_next;
			}
		}
		else 
		{
			previous = current;
			current = current->s_next;
		}
	}

	if (tally == 0)//If no nodes were found with a score less than 4, and thus not removed, this sends a 0 back to main.
	{
		return 0;
	}

	return 1;
}
