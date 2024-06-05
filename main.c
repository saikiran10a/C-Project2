#include <stdio.h>
#include "main.h"
#include "view.h"
#include "edit.h"

int main(int argc, char *argv[])
{
	if(argc <= 1)
	{
		printf("\n------------------------------------------------------------\n\n");
		printf("ERROR: ./a.out : INVALID ARGUMENTS\nUSAGE:\n");
		printf("To view please pass like: ./a.out -v mp3filename\nTo edit pass like: ./a.out -e -t/-a/-A/-g/-y/-c changing_text mp3filename\nTo get help pass like : ./a.out --help\n");
		printf("------------------------------------------------------------\n\n");
	}
	else if(check_operation_type(argv) == mp3_help)
	{
		view_mp3_help();
	}
	else if(check_operation_type(argv) == mp3_view)
	{
		if(argc == MAX_VIEW_ARGC)
		{
			view_mp3_file(argv);
		}
		else
		{
			printf("-----------------------Wrong commands passed-------------------\n");
			printf("\n------------Go for help, by typing the below commmande---------\n");
			printf("\n---------------------   :./a.out --help    --------------------\n");
		}
	}
	else if(check_operation_type(argv) == mp3_edit)
	{
		if(argc == MAX_EDIT_ARGC)
		{
			edit_mp3_file(argv);
		}
		else
		{
			printf("-----------------------Wrong commands passed-------------------\n");
			printf("\n------------Go for help, by typing the below commmande---------\n");
			printf("\n---------------------   :./a.out --help    --------------------\n");
		}
	}
}
