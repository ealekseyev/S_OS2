#include "lib/IO/screen.h"
#include "lib/types.h"

void kmain() {
	cstring str = "my first kernel";
	screen_clear(screen_colorgen(BLACK, GREEN));
	screen_writestr(str, screen_colorgen(BLACK, GREEN));
}