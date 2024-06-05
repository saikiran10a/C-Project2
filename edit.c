#include <stdio.h>
#include <string.h>
#include "edit.h"
#include "main.h"
#include "view.h"

OperationType check_edit_type(char *argv[])
{
    if(!(strcmp(argv[EDIT_TAG], "-t")))
		return mp3_title;
		
    else if(!(strcmp(argv[EDIT_TAG], "-a")))
		return mp3_artist;
		
    else if(!(strcmp(argv[EDIT_TAG], "-A")))
		return mp3_album;
		
    else if(!(strcmp(argv[EDIT_TAG], "-y")))
		return mp3_year;
		
    else if(!(strcmp(argv[EDIT_TAG], "-c")))
		return mp3_comment_tag;
		
    else if(!(strcmp(argv[EDIT_TAG], "-g")))
		return mp3_genre_tag;
		
    else 
		return FAILURE;
}

int verify_change_tag(FILE *mp3_ptr, char *argv[], char check)
{
	char var;
	var = check_edit_type(argv);
	switch(var)
	{
		case mp3_title:
			if(check_title_tag(mp3_ptr, "TIT2") == mp3_success);
			break;
		case mp3_artist:
			if(check_title_tag(mp3_ptr, "TPE1") == mp3_success);
			break;
		case mp3_album:
			if(check_title_tag(mp3_ptr, "TALB") == mp3_success);
			break;
		case mp3_year:
			if(check_title_tag(mp3_ptr, "TYER") == mp3_success);
			break;
		case mp3_genre_tag:
			if(check_title_tag(mp3_ptr, "TCON") == mp3_success);
			break;
		case mp3_comment_tag:
			if(check_title_tag(mp3_ptr, "COMM") == mp3_success);
			break;
		default: 
			return FAILURE;
	}
	if(check == var)
		return SUCCESS;
	else
		return FAILURE;
}

Status edit_mp3_file(char *argv[])
{
	if(check_edit_type(argv) == FAILURE)
    {
		printf("-----------------------Wrong commands passed-------------------\n");
		printf("\n------------Go for help, by typing the below commmande---------\n");
		printf("\n---------------------   :./a.out --help    --------------------\n");
		return FAILURE;
    }
	
	int tag_size = 0;
	FILE *mp3_ptr = fopen(argv[SAMPLE_MP3_EDIT], "r+");
	printf("\n---------------------SELECTED EDIT DETAILS---------------------\n");
	if(file_validation(mp3_ptr) == SUCCESS)
	{
		fseek(mp3_ptr, 10, SEEK_SET);
		char check = mp3_title;
		
		while(1)
		{
			if(verify_change_tag(mp3_ptr, argv, check) == SUCCESS)
			{
				tag_size = read_tag_size(mp3_ptr);
				
				if(strlen(argv[NEW_TAG]) > tag_size - 1)
				{
					printf("The size of new tag is more.\n");
					printf("The size of new tag should not be greater than previous tag.\n");
					break;
				}
				
				fseek(mp3_ptr, 3, SEEK_CUR);
			
				if(check == mp3_year)
				{
					printf("\n------------------------CHANGE THE YEAR-----------------------\n\n");
					fwrite(argv[NEW_TAG], 1, strlen(argv[NEW_TAG]), mp3_ptr);
					printf("YEAR      :      %s\n", argv[NEW_TAG]);
					printf("\n-------------------YEAR CHANGED SUCCESSFULLY------------------\n\n");
				}
				else
				{
					fwrite(argv[NEW_TAG], 1, strlen(argv[NEW_TAG])+1, mp3_ptr);
					if(check_edit_type(argv) == mp3_title)
					{
						printf("\n-----------------------CHANGE THE TITLE------------------------\n\n");
						printf("TITLE      :      %s\n", argv[NEW_TAG]);
						printf("\n-------------------TITLE CHANGED SUCCESSFULLY------------------\n\n");
					}
					else if(check_edit_type(argv) == mp3_artist)
					{
						printf("\n-----------------------CHANGE THE ARTIST------------------------\n\n");
						printf("ARTIST      :      %s\n", argv[NEW_TAG]);
						printf("\n-------------------ARTIST CHANGED SUCCESSFULLY------------------\n\n");
					}
					else if(check_edit_type(argv) == mp3_album)
					{
						printf("\n------------------------CHANGE THE ALBUM-----------------------\n\n");
						printf("ALBUM      :      %s\n", argv[NEW_TAG]);
						printf("\n-------------------ALBUM CHANGED SUCCESSFULLY------------------\n\n");
					}
					else if(check_edit_type(argv) == mp3_genre_tag)
					{
						printf("\n------------------------CHANGE THE GENRE-----------------------\n\n");
						printf("GENRE      :      %s\n", argv[NEW_TAG]);
						printf("\n-------------------GENRE CHANGED SUCCESSFULLY------------------\n\n");
					}
					else if(check_edit_type(argv) == mp3_comment_tag)
					{
						printf("\n-----------------------CHANGE THE COMMENT------------------------\n\n");
						printf("COMMENT      :      %s\n", argv[NEW_TAG]);
						printf("\n-------------------COMMENT CHANGED SUCCESSFULLY------------------\n\n");
					}
				}
				break;
			} 
			else
			{
				tag_size = read_tag_size(mp3_ptr);
				fseek(mp3_ptr, 3, SEEK_CUR);
				fseek(mp3_ptr, tag_size-1, SEEK_CUR);
			}
			check++;
		}
	}
	else
	{
		printf("\n--------------------------OPENING FAILED---------------------------\n");
		printf("              mp3 file does not exists, please verify it.\n\n");
	}
}
