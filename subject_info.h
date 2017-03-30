#ifndef SUBJECT_INFO
#define SUBJECT_INFO

#include"help_info.h"

/*
These 2 objects are part of the ADT managing the list of ways of help
for a given subject.  The struct defines the nodes of the linear linked list.
The class's functions can add new nodes (ways of help) to the list.
Each node itself contains a class which has all of the actual data on the 
ways of help and operations to manipulate or output them.
Thus, the functions here mainly call and interact with the fucntions
of the class embedded in the node.
*/

struct s_node {
	help_info h_data;
	s_node * s_next;

	s_node();
//	~s_node();
};

class subject_info {

	public:
		//Constructor and destructor
		subject_info();
		~subject_info();

		//Accessor functions
		bool search_ways(const char way_name[]);
		int print_way_name(void);
		int print_ways(void);
		int print_best_ways(void);

		//Mutator Functions
		int add_way(help_info & new_way);
		int edit_rating(const char * way_name, int new_score);
		int delete_low_scores(void);


	private:
		s_node * s_head;
};

#endif
