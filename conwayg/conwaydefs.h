#pragma once
#include "stdafx.h"

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

// Arrays
char array_c[999][999];			// Displayed Array
char array_cN[999][999];		// Calculated Array
char array_cB[999][999];		// Build Mode Array
int x; // Array Height
int y; // Array Width
int update; // update rate in milliseconds

			// Cell States
const char LIVE = (char)254;		// box
const char DEAD = NULL;				// empty

									// UI for Build Mode
const char SELECT = (char)219;		// cursor appearance
const char EMPTY = (char)240;		// empty cell
const char OVERLAP = (char)177;		// cursor appearance in case of cell already having a live state

									// integers to store coordinate values for various functions
int n = 0, m = 0;

// Program states
bool building = false;
bool simulating = false;


// End the program
void end() {
	if (GetKeyState(VK_ESCAPE) & 0x8000) {
		simulating = false;
		building = false;
	}
}
