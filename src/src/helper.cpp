// Helper file for avoiding the confliction between conio.h and EGE.
// Lukaß Zhang, 2023/12/19

#include <conio.h>
#include "DSDisplay.h"

char wait_key() {
	char ch = _getch();
	return ch > 'Z' ? ch - 32 : ch;
}
