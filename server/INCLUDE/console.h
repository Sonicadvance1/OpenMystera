#ifndef _MLCONSOLE_
#define _MLCONSOLE_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static char quietMode = 0;
static void newLine(const char *fmt,...)
{
	if(quietMode)
		return;

	char		text[256];							// Holds Our String
	va_list		ap;									// Pointer To List Of Arguments

	// Parse The String For Variables
	va_start(ap, fmt);					
	vsprintf(text, fmt, ap);
	va_end(ap);

	for(unsigned int i=0;i<strlen(text);i++)
		if(text[i]=='\n')text[i]=' ';
	
	printf("%s\n",text);
}

#endif
