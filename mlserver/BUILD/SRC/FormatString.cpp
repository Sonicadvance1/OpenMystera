#include "FormatString.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#if defined(__GNUC__)
#define _vsnprintf vsnprintf
#endif

char * FormatString(const char *format, ...)
{
	static int textIndex=0;
	static char text[4][8096];
	va_list ap;
	va_start(ap, format);
	if (++textIndex==4)
		textIndex=0;
	_vsnprintf(text[textIndex], 8096, format, ap);
	va_end(ap);
	text[textIndex][8096-1]=0;

	return text[textIndex];
}

