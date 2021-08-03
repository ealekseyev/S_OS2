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

inline unsigned char screen_colorgen(unsigned char bg, unsigned char fg) {
	return (bg << 8) + fg;
}

void screen_clear(unsigned char color) {
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

void screen_writestr(char* str, unsigned char color) {
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