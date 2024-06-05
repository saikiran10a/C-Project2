#include <stdio.h>
#include <string.h>
#include "view.h"
#include "main.h"

OperationType check_operation_type(char *argv[])
{
    if ( strcmp(argv[1], "-v") == 0 )
    {
        return mp3_view;
    }
    else if ( strcmp(argv[1], "-e") == 0 )
    {
        return mp3_edit;
    }
    else if( strcmp(argv[1], "--help") == 0 )
    {
        return mp3_help;
    }
    else
    {
    	return no_arguments;
    }
}
void view_mp3_help()
{
	printf("\n---------------------HELP MENU------------------------------\n\n");
		printf("1. -v -> to view mp3 file contents\n");
		printf("2. -e -> to edit mp3 file contents\n");
		printf("2.1. -t -> to edit song title\n2.2. -a -> to edit artist name\n2.3. -A -> to edit album name\n2.4. -y -> to edit year\n2.5. -m -> to edit content\n2.6. -c -> to edit comment\n");
		printf("------------------------------------------------------------\n\n");
}

int file_validation(FILE *mp3_ptr)
{
    if(mp3_ptr == NULL)
		return FAILURE;
    else
		return SUCCESS;
}
Status check_title_tag(FILE *mp3_ptr, char tag[])
{
    char arr[5];
    fread(arr, 1, 4, mp3_ptr);
    if(!(strcmp(arr, tag)))
		return mp3_success;
    else
		return mp3_failure;
}
int read_tag_size(FILE *mp3_song_ptr)
{
    char size[4];
    fread(size, 4, 1, mp3_song_ptr);
    return size[3];
}
Status print_tag_content(FILE *mp3_song_ptr, int tag_size)
{
    int i = 0;
    char ch, flag = 1;
    while(i <= tag_size-2)
    {
		ch = fgetc(mp3_song_ptr);
		if(ch == '\0')
			flag = 0;

		if(flag)
			putchar(ch);	
		i++;
    }
    return 0;
}
void view_mp3_file(char *argv[])
{
	int tag_size = 0;
	FILE *mp3_ptr = fopen(argv[SAMPLE_MP3], "r");
	if(file_validation(mp3_ptr) == SUCCESS)
	{
		printf("\n----------------------SELECTED VIEW DETAILS------------------------\n\n");
		printf("\n-------------------------------------------------------------------\n");
		printf("                 MP3 TAG READER AND EDITOR FOR ID3v2\n");
		printf("-------------------------------------------------------------------\n");
		fseek(mp3_ptr, 10, SEEK_SET);
		if(check_title_tag(mp3_ptr, "TIT2") == mp3_success)
		{
			tag_size = read_tag_size(mp3_ptr);
			fseek(mp3_ptr, 3, SEEK_CUR);
			printf("Title		: 		");
			print_tag_content(mp3_ptr, tag_size);
		}
		if(check_title_tag(mp3_ptr, "TPE1") == mp3_success)
		{
			tag_size = read_tag_size(mp3_ptr);
			fseek(mp3_ptr, 3, SEEK_CUR);
			printf("\nArtist		: 		");
			print_tag_content(mp3_ptr, tag_size);
		}
		if(check_title_tag(mp3_ptr, "TALB") == mp3_success)
		{
			tag_size = read_tag_size(mp3_ptr);
			fseek(mp3_ptr, 3, SEEK_CUR);
			printf("\nAlbum		: 		");
			print_tag_content(mp3_ptr, tag_size);
		}
		if(check_title_tag(mp3_ptr, "TYER") == mp3_success)
		{
			tag_size = read_tag_size(mp3_ptr);
			fseek(mp3_ptr, 3, SEEK_CUR);
			printf("\nYear		: 		");
			print_tag_content(mp3_ptr, tag_size);
		}
		if(check_title_tag(mp3_ptr, "TCON") == mp3_success)
		{
			tag_size = read_tag_size(mp3_ptr);
			fseek(mp3_ptr, 3, SEEK_CUR);
			printf("\nGenre		: 		");
			print_tag_content(mp3_ptr, tag_size);
		}
		if(check_title_tag(mp3_ptr, "COMM") == mp3_success)
		{
			tag_size = read_tag_size(mp3_ptr);
			fseek(mp3_ptr, 3, SEEK_CUR);
			printf("\nComment		: 		");
			print_tag_content(mp3_ptr, tag_size);
		}
		printf("\n-------------------------------------------------------------------\n\n");
		printf("\n-------------------DETAILS DISPLAYED SUCCESSFULLY------------------\n\n");
	}
	else
    {
		printf("\n--------------------------OPENING FAILED---------------------------\n");
		printf("              mp3 file does not exists, please verify it.\n\n");
    }

}
