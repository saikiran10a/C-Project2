#ifndef MAIN_H
#define MAIN_H

#define SUCCESS 1
#define FAILURE 0

#define OPERATION_TAG 1
#define SAMPLE_MP3 2
#define EDIT_TAG 2
#define MAX_VIEW_ARGC 3
#define SAMPLE_MP3_EDIT 4
#define NEW_TAG 3
#define MAX_EDIT_ARGC 5

/* Status will be used in fn. return type */
typedef enum
{
    mp3_success,//0
    mp3_failure //1
} Status;

typedef enum
{
    mp3_view,
    mp3_edit,
    mp3_help, 
    no_arguments,
    mp3_title,
    mp3_artist,
    mp3_album,
    mp3_year,
    mp3_genre_tag,
    mp3_comment_tag
} OperationType;

#endif
