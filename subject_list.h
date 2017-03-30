#ifndef SUBJECT_LIST
#define SUBJECT_LIST

#include"subject_info.h"
#include"help_info.h"

//This ADT maintains the linked list of subjects.
//Users can add, view, edit, and remove subjects with the functions here.
//Input: user subject of choice.
//Output: edited linked list or display of subjects.
//Functions here also access the functions within each node,
//connecting the user to the functions of the next ADT linked list

struct l_node {
		//Constructor and destructor
		l_node();
		~l_node();

		char * subject; 
		l_node * l_next;
		subject_info subject_help;	
};

class subject_list {

	public:
		//Constructor and destructor functions
		subject_list();
		~subject_list();

		//Accessor functions
		int view_list(void);
		bool find_way(const char subject_name[], const char way_name[]);
		bool search(const char subject_name[]);
		int view_way_names(const char subject_name[]);
		int view_ways(const char subject_name[], char choice);

		//Mutator functions
		int add_subject(const char subject_name[]);
		int add_subject(const char subject_name[], l_node * current);
		int add_help_way(const char subject_name[],help_info & new_help);
		int edit_help_rating(const char subject_name[], const char * way_name, int update_score);
		int delete_low(const char subject_name[]);
		int remove(const char subject_name[]);

	private:
		l_node * l_head;
};


#endif
