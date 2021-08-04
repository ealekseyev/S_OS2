#ifndef _SCREEN_H_
#define _SCREEN_H_
#include "../types.h"

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LGREY 7
#define DGREY 8
#define LBLUE 9
#define LGREEN 0x0A
#define LCYAN 0x0B
#define LRED 0x0C
#define LMAGENTA 0x0D
#define LBROWN 0x0E
#define WHITE 0x0F

char* vidptr = (char*) 0xb8000; 	// video memory begins here
//char* vidptr_curloc = (char*) vidptr;		// location of cursor

inline uint8_t screen_colorgen(uint8_t bg, uint8_t fg) {
	return (bg << 8) + fg;
}

void screen_clear(uint8_t color) {
	unsigned int j = 0;

	/* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while(j < 80 * 25 * 2) {
		/* blank character */
		vidptr[j] = ' ';
		/* attribute-byte - light grey on black screen */
		vidptr[j+1] = color;
		j = j + 2;
	}
}

void screen_writestr(char* str, uint8_t color) {
	unsigned int i = 0;
	unsigned int j = 0;

	/* this loop writes the string to video memory */
	while(str[j] != '\0') {
		/* the character's ascii */
		vidptr[i] = str[j];
		/* attribute-byte: give character black bg and light grey fg */
		vidptr[i+1] = color;
		++j;
		i = i + 2;
	}
}

void screen_writechar(char c, uint8_t color) {
		vidptr[0] = c;
		vidptr[1] = color;
}

#endif