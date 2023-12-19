/**********************************************************************
* Helper file for avoiding the confliction between conio.h and EGE.
*
* Yuhao Zhang. 12/19/2023
**********************************************************************/

#include <conio.h>
#include <cstdio>
#include "DSDisplay.h"

char wait_key() {
	char ch = _getch();
	return ch > 'Z' ? ch - 32 : ch;
}