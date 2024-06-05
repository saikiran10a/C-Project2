#ifndef VIEW_H
#define VIEW_H
#include "view.c"

OperationType check_operation_type(char *argv[]);
void view_mp3_help();
void view_mp3_file(char *agrv[]);
int file_validation(FILE *);
Status check_title_tag(FILE *mp3_ptr, char tag[]);
int read_tag_size(FILE *mp3_song_ptr);

#endif
