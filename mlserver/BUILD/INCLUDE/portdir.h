
#if defined (WIN32)

/*...sincludes:0:*/
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include <stdlib.h>

#define	DIRT_C


#if defined (WIN32)

#ifndef DIRT_H
#define	DIRT_H

#define	DIRTE_OK            0
#define	DIRTE_GEN_ERROR     1
#define	DIRTE_NO_MEMORY     2
#define	DIRTE_NOT_FOUND     3
#define	DIRTE_NOT_DIRECTORY 4
#define	DIRTE_NO_ACCESS     5

#ifndef DIRT_C

typedef void DIRT;

extern DIRT *dirt_open(const char *dirname, int *rc);
extern const char *dirt_next(DIRT *dirt);
extern void dirt_close(DIRT *dirt);

extern const char *dirt_error(int rc);

#endif

#endif

#else //unix


#ifndef DIRT_H
#define	DIRT_H

#define	DIRTE_OK            0
#define	DIRTE_GEN_ERROR     1
#define	DIRTE_NO_MEMORY     2
#define	DIRTE_NOT_FOUND     3
#define	DIRTE_NOT_DIRECTORY 4
#define	DIRTE_NO_ACCESS     5
#define	DIRTE_NO_RESOURCE   6

#ifndef DIRT_C

typedef void DIRT;

extern DIRT *dirt_open(const char *dirname, int *rc);
extern const char *dirt_next(DIRT *dirt);
extern void dirt_close(DIRT *dirt);

extern const char *dirt_error(int rc);

#endif

#endif

#endif


/*...vdirt\46\h:0:*/
/*...e*/

typedef struct
	{
	HANDLE hff;
	WIN32_FIND_DATA fd;
	BOOL empty;
	BOOL first;
	} DIRT;

/*...sdirt_open:0:*/
DIRT *dirt_open(const char *dirname, int *rc)
	{
	DIRT *dirt;
	char pattern[MAX_PATH+2+1];
	*rc = DIRTE_OK;
	if ( strlen(dirname) > MAX_PATH )
		{
		*rc = DIRTE_NOT_FOUND;
		return NULL;
		}
	if ( (dirt = (DIRT *) malloc(sizeof(DIRT))) == NULL )
		{
		*rc = DIRTE_NO_MEMORY;
		return NULL;
		}
	strcpy(pattern, dirname);
	strcat(pattern, "\\*");
	if ( (dirt->hff = FindFirstFile(pattern, &(dirt->fd))) == (HANDLE) -1 )
		{
		switch ( GetLastError() )
			{
			case ERROR_FILE_NOT_FOUND:
				dirt->empty = TRUE;
				return dirt;
			case ERROR_PATH_NOT_FOUND:
				*rc = DIRTE_NOT_FOUND;
				break;
			case ERROR_DIRECTORY:
				*rc = DIRTE_NOT_DIRECTORY;
				break;
			case ERROR_ACCESS_DENIED:
				*rc = DIRTE_NO_ACCESS;
				break;
			case ERROR_NOT_ENOUGH_MEMORY:
				*rc = DIRTE_NO_MEMORY;
				break;
			default:
				*rc = DIRTE_GEN_ERROR;
				break;
			}
		free(dirt);
		return NULL;
		}
	dirt->empty = FALSE;
	dirt->first = TRUE;
	return dirt;
	}
/*...e*/
/*...sdirt_next:0:*/
const char *dirt_next(DIRT *dirt)
	{
	if ( dirt->empty )
		return NULL;
	else if ( dirt->first )
		dirt->first = FALSE;
	else if ( ! FindNextFile(dirt->hff, &(dirt->fd)) )
		return NULL;
	return dirt->fd.cFileName;
	}
/*...e*/
/*...sdirt_close:0:*/
void dirt_close(DIRT *dirt)
	{
	free(dirt);
	}
/*...e*/

/*...sdirt_error:0:*/
const char *dirt_error(int rc)
	{
	const char *errlist[] =
		{
		NULL,
		"general error",
		"out of memory",
		"not found",
		"not a directory",
		"access denied",
		};
	return errlist[rc];
	}
/*...e*/

#else //unix



/*...sincludes:0:*/
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define	DIRT_C
#if defined (WIN32)

#ifndef DIRT_H
#define	DIRT_H

#define	DIRTE_OK            0
#define	DIRTE_GEN_ERROR     1
#define	DIRTE_NO_MEMORY     2
#define	DIRTE_NOT_FOUND     3
#define	DIRTE_NOT_DIRECTORY 4
#define	DIRTE_NO_ACCESS     5

#ifndef DIRT_C

typedef void DIRT;

extern DIRT *dirt_open(const char *dirname, int *rc);
extern const char *dirt_next(DIRT *dirt);
extern void dirt_close(DIRT *dirt);

extern const char *dirt_error(int rc);

#endif

#endif

#else //unix


#ifndef DIRT_H
#define	DIRT_H

#define	DIRTE_OK            0
#define	DIRTE_GEN_ERROR     1
#define	DIRTE_NO_MEMORY     2
#define	DIRTE_NOT_FOUND     3
#define	DIRTE_NOT_DIRECTORY 4
#define	DIRTE_NO_ACCESS     5
#define	DIRTE_NO_RESOURCE   6

#ifndef DIRT_C

typedef void DIRT;

extern DIRT *dirt_open(const char *dirname, int *rc);
extern const char *dirt_next(DIRT *dirt);
extern void dirt_close(DIRT *dirt);

extern const char *dirt_error(int rc);

#endif

#endif

#endif


/*...vdirt\46\h:0:*/
/*...e*/

typedef struct
	{
	DIR *dir;
	} DIRT;

/*...sdirt_open:0:*/
DIRT *dirt_open(const char *dirname, int *rc)
	{
	DIRT *dirt;
	*rc = DIRTE_OK;
	if ( (dirt = (DIRT *) malloc(sizeof(DIRT))) == NULL )
		{
		*rc = DIRTE_NO_MEMORY;
		return NULL;
		}
	if ( (dirt->dir = opendir(dirname)) == NULL )
		{
		switch ( errno )
			{
			case ENOMEM:	*rc = DIRTE_NO_MEMORY;		break;
			case ENOENT:	*rc = DIRTE_NOT_FOUND;		break;
			case ENOTDIR:	*rc = DIRTE_NOT_DIRECTORY;	break;
			case EACCES:	*rc = DIRTE_NO_ACCESS;		break;
			case EMFILE:
			case ENFILE:	*rc = DIRTE_NO_RESOURCE;	break;
			default:	*rc = DIRTE_GEN_ERROR;		break;
			}
		free(dirt);
		return NULL;
		}
	return dirt;
	}
/*...e*/
/*...sdirt_next:0:*/
const char *dirt_next(DIRT *dirt)
	{
	struct dirent *de;
	if ( (de = readdir(dirt->dir)) == NULL )
		return NULL;
	return de->d_name;
	}
/*...e*/
/*...sdirt_close:0:*/
void dirt_close(DIRT *dirt)
	{
	closedir(dirt->dir);
	free(dirt);
	}
/*...e*/

/*...sdirt_error:0:*/
const char *dirt_error(int rc)
	{
	const char *errlist[] =
		{
		NULL,
		"general error",
		"out of memory",
		"not found",
		"not a directory",
		"access denied",
		"out of resource",
		};
	return errlist[rc];
	}
/*...e*/


#endif