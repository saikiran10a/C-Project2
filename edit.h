#ifndef EDIT_H
#define EDIT_H
#include "edit.c"

Status edit_mp3_file(char *argv[]);
OperationType check_edit_type(char *argv[]);
int veriy_change_tag(FILE *mp3_song_ptr, char *argv[], char check);

#endif
