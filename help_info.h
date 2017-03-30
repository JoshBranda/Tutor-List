#ifndef HELP_INFO
#define HELP_INFO

/*
This class object contains each subject's way of help's information.
Functions access those data members to add or edit them.
*/

class help_info {
	public:
		help_info();
		help_info(char h_type[], char h_time[], int h_rating,
			char h_location[], char h_contacts[]);
		~help_info();

		//Accessor functions
		void print_help(void);
		char * return_help_name(void);
		int return_rating(void);

		//Mutator functions
		int help_info_copy(const help_info & to_copy);
		int edit_rating(int newRating);

	private:
		char * help_type;
		char * help_time;
		int help_rating;
		char * help_location;
		char * help_contacts;
};

#endif
