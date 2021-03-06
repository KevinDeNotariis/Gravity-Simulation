/*
 * print.cpp
 *
 *  Created on: 13 gen 2017
 *      Author: kevin
 */

#include "screencast.h"

#define LEN 8192

void printv(va_list args, const char* format)
{
	char buf[LEN];
	char* ch = buf;
	vsnprintf(buf, LEN, format, args);
	while(*ch)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *ch++);
	}
}

void print(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printv(args, format);
	va_end(args);
}

void printAt(int x, int y, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printv(args, format);
	va_end(args);
}
