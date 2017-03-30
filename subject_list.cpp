#include"subject_list.h"
#include<iostream>
#include<cstring>

using namespace std;

//Constructor for node struct.
l_node::l_node() 
{
	subject = NULL;
	l_next = NULL;
}



//Destructor eliminates dynamically allocated subject name.
l_node::~l_node() 
{
	if (subject) 
	{
		delete [] subject;
		subject = NULL;
	}
}


//Constructor for list class with pointer to the node struct.
subject_list::subject_list() 
{
	l_head = NULL;
}



//Destructor for the list of subjects.  Deletes each node in the list.
subject_list::~subject_list() 
{
	l_node * current = l_head;
	//Traverses and DESTROYS the LLL!	
	while (l_head != NULL) 
	{
		l_head = l_head->l_next;
		delete current;
		current = l_head;
	}
}



//Prints the subjects stored in the list.
int subject_list::view_list(void) 
{
	//Checkes for empty list
	if (l_head == NULL)
	{
		return 0;
	}

	//Traverses list until end
	for (l_node * current = l_head; current; current = current->l_next) 
	{
		cout << current->subject << "   ";
	}

	cout << endl << endl;
	return 1;
}



//Accesses the functions of the class of ways of help, stored in each list node.
//This particular function prints just the types of help (not the location, hours, etc)
//for all of the ways of help stored in the nested list.
//The argument passed here is the users input for subject name.
int subject_list::view_way_names(const char subject_name[])
{
	//Diplays only the help types of the chosen subject
	l_node * current = l_head;

	while(strcmp(current->subject,subject_name) != 0)
	{
		current = current->l_next;
	}

	current->subject_help.print_way_name();
}	



//This function also accesses the object within the chosen node
//to use its print functions to either output all of the information
//about a chosen way OR output only the ways rated 8 or above.
//The arguments passed here are the users inputs for the subject name
//and for their choice of either displaying all or the highest rated.
int subject_list::view_ways(const char subject_name[], char choice) 
{
	l_node * current = l_head;

	while(strcmp(current->subject,subject_name) != 0)
	{
		current = current->l_next;
	}

	if (choice == 'a' || choice == 'A')
	{
		if (current->subject_help.print_ways() == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	else
	{
		if (current->subject_help.print_best_ways() < 1)
		{
			return 0;
		}
		return 1;
	}
}



//This function checkes to make sure that the user's choice of subject
//and way of help actually exist so that the user does not begin
//entering information to edit without knowing if that information
//will be added or not.
//The arguments are the subject and way of help input by the user.
bool subject_list::find_way(const char subject_name[], const char way_name[])
{
	l_node * current = l_head;
	
	while(current)
	{
		if (strcmp(current->subject,subject_name) == 0)
		{
			return current->subject_help.search_ways(way_name) ;
		}
		current = current->l_next;
	}

	return false;
}

	

//This function also checks to see if a given subject exists or not
//to prevent the user from adding editing information to a subject
//that does not exist.
//Its argument is the subject name input by the user.
bool subject_list::search(const char subject_name[])
{
	l_node * current = l_head;

	while(current)
	{
		if (strcmp(current->subject,subject_name) == 0)
		{
			return true;
		}
		current = current->l_next;
	}

	return false;
}



//This is a recursive wrapper function to add a new subject to the list alphabetically.
//The argument is the subject name given by user input.
int subject_list::add_subject(const char subject_name[]) 
{
	//Special case: If list is empty, this assigns head to the new node	
	if (l_head == NULL) 
	{
		l_head = new l_node;
		l_head->subject = new char[strlen(subject_name) + 1];
		strcpy(l_head->subject,subject_name);
		l_head->l_next = NULL;
		return 1;
	}
	//Special case: If the head of the list is alphabetically after the new node, this adds the new one before.  
	//This also accounts for a list with only one node, alphabetically after the current
	else if (strcmp(l_head->subject,subject_name) > 0)
	{
		l_node * newNode = new l_node;

		newNode->subject = new char[strlen(subject_name) + 1];
		strcpy(newNode->subject,subject_name);
		newNode->l_next = l_head; 
		l_head = newNode;
		return 1;
	}
	//This means the list does not have no nodes or 1 node which is alphabetically after the new node. 
	//Recursive call begins
	else 
	{
		return add_subject(subject_name,l_head);
	}
}



//The arguments designate this function as the recursive one.
//It traverses the list through each recursive call until it reaches the target node.
//The arguments are both the subject name given by user input and
//the node pointer to the current node, beginning with head.
int subject_list::add_subject(const char subject_name[], l_node * current) 
{
	//Checks to see if the list already contains the subject and returns a 0 if so.
	if (strcmp(current->subject,subject_name) == 0) 
	{
		return 0;
	}
	//If you reach the end of the list, this adds the node at the end.  
	//This also works for a list of one assuming the single node is alphabetically before the new node 
	//(if it is alphabetically after, that is taken care of in the wrapper function)
	else if (current->l_next == NULL) 
	{
		l_node * newNode = new l_node;
		newNode->subject = new char[strlen(subject_name) + 1];
		strcpy(newNode->subject,subject_name);
		newNode->l_next = NULL;
		current->l_next = newNode;
		return 1;
	}
	//If you have not reached the end of the list, but you have found a node alphabetically after yours,
	//this creates a new node with the input subject name, links it to the found node alphabetically after yours
	//and then links the previous node to your new node.
	else if (strcmp(current->l_next->subject,subject_name) > 0) 
	{
		l_node * newNode = new l_node;
		newNode->subject = new char[strlen(subject_name) + 1];
		strcpy(newNode->subject,subject_name);
		newNode->l_next = current->l_next; 
		current->l_next = newNode;
		return 1;
	}	
	//This last else assumes no matches were found at this spot in the list, and calls the recursive function again
	//with the next pointer to move down the list one place.
	else 
	{
		return add_subject(subject_name,current->l_next);
	}
}



//This function traverses the linked list to find the chosen subject and add the values of the new
//way of help to the current list by calling the add function in the member class.
//The arguments are the user's input subject name and address of the temporary object containing all
//the data on help.
int subject_list::add_help_way(const char subject_name[], help_info & new_help)
{	
	l_node * current = l_head;

	while(strcmp(current->subject,subject_name) != 0)
	{
		current = current->l_next;
	}

	return current->subject_help.add_way(new_help);
}



//This function passes the user's choice of subject name, way of help, and new score
//to edit the existing score in the class to the new one chosen by the user.
int subject_list::edit_help_rating(const char subject_name[], const char * way_name,int update_score) 
{
	//This does not need to return 1/0 if item is not found because search is already p
	l_node * current = l_head;

	while(strcmp(current->subject,subject_name) != 0)
	{
		current = current->l_next;
	}

	return current->subject_help.edit_rating(way_name, update_score);
}



//This function calls the member class's function of delete
//to eliminate all of the methods of the chosen subject that
//score belowe a 4.
//The argument is the subject name provided by the user.
int subject_list::delete_low(const char subject_name[]) 
{
	l_node * current = l_head;

	while(strcmp(current->subject,subject_name) != 0)
	{
		current = current->l_next;
	}

	return current->subject_help.delete_low_scores();
}



//This function traverses the linked list until
//the argument passed by the user of the subject name
//is found and then that particular node is deleted.
//If there are adjacent nodes, they are linked after the deletion.
int subject_list::remove(const char subject_name[])
{
	l_node * current = l_head->l_next;
	l_node * previous = l_head;
	
	//Special case: the list is empty.  Return error.
	if (l_head == NULL)
	{
		return 0;
	}

	//Special case: the head of the list is the desired subject.
	//Head is moved to the next node prior to deletion.
	if (strcmp(l_head->subject,subject_name) == 0)
	{
		l_head = l_head->l_next;
		delete previous;
		return 1;
	}
	//Traverses until one matching entry is found and deletes it.
	while (current)
	{
		if (strcmp(current->subject,subject_name) == 0)
		{
			previous->l_next = current->l_next;
			delete current;
			return 1;
		}
		previous = current;
		current = current->l_next;
	}
	
	return 0;
}
	
