#include "stdafx.h"
#include "conwaydefs.h"

// File handling
void file_output() {
	system("CLS");
	string filenameout;
	cout << "input a file name to export, making sure to end the filename with '.txt' or '.dat'" << endl << "filename: ";
	cin >> filenameout;

	ofstream file;
	file.open(filenameout.c_str()); // takes user input and outputs a file accordingly

	for (int n = 0; n < y; n++) // Loop takes values from the build array and converts them into characters
	{
		for (int m = 0; m < x; m++)
		{
			if (array_cB[m][n] == EMPTY) { file << EMPTY; }
			if ((array_cB[m][n] == LIVE) || (array_cB[m][n] == OVERLAP)) { file << LIVE; }
		}
		file << endl; // adds another line when the previous line is finished writing
	}
file.close(); // close file
}

void file_input() {
	system("CLS");
	string filenamein;
	cout << "input a file name to import, make sure to end the file with a '.txt' or '.dat'" << endl << "filename: ";
	cin >> filenamein;

	string C;
	ifstream inFile(filenamein.c_str()); // imports file with the input name
	if (!inFile) { cout << "Error! File cannot be opened"; Sleep(1000); inFile.close(); } // if no such file exists, show an error message before returning to the build grid
		
	if (inFile) {
		for (int n = 0; n < y; n++) // For loop reads the txt file and transfers the values into the building array
		{
			for (int m = 0; m < x; m++)
			{
				inFile >> array_cB[m][n];
			}
		}

		Sleep(1000);
		inFile.close(); // file closes after reading
	}
}

// Arrays
class ConwayGrid {
public:
	// Input grid dimensions and refresh rate
	void grid_in() // INPUT GRID BOUNDARY
	{
		// default values so that the compiler does not see array_c as an empty array on startup
		x = 12; y = 12;

		cout << "Welcome to Conway's Game of life, this is a celluar automation" << endl << endl;

		cout << "Please input a size for your grid:" << endl;
		cout << "X: "; cin >> x;
		cout << "Y: "; cin >> y;
		system("CLS");
		cout << "The refresh rate of the grid determines the speed at which it updates in milliseconds" << endl << "reccomended: 50ms" << endl << endl;
		cout << "Input your refresh rate in ms" << endl;
		cin >> update;
		system("CLS");
	}
	// Prints grid
	void grid_out() // PRINT GRID
	{
		system("CLS");
		for (int n = 0; n < y; n++) // prints out each individual cell for the input size
		{
			for (int m = 0; m < x; m++)
			{
				cout << array_c[m][n] << DEAD; // the non-breaking space is there for aesthetic purposes
			}
			cout << endl;
		}
	}
	// Calculating next grid
	void grid_compute() //CHECK NEIGBHORS
	{
		int cX, cY; // cell coordinates
		for (cY = 0; cY < y; cY++) // run through all cells
		{
			for (cX = 0; cX < x; cX++)
			{
				array_cN[cX][cY] = DEAD; // DEFAULT NEW BOARD STATE

				int n = 0;
				// ALIVE VERTICAL AND HORIZONTAL ADJACENCY
				if (array_c[cX][cY + 1] == LIVE) { n++; }
				if (array_c[cX][cY - 1] == LIVE) { n++; }
				if (array_c[cX - 1][cY] == LIVE) { n++; }
				if (array_c[cX + 1][cY] == LIVE) { n++; }
				// ALIVE DIAGONAL ADJACENCY
				if (array_c[cX - 1][cY + 1] == LIVE) { n++; }
				if (array_c[cX - 1][cY - 1] == LIVE) { n++; }
				if (array_c[cX + 1][cY + 1] == LIVE) { n++; }
				if (array_c[cX + 1][cY - 1] == LIVE) { n++; }

				//	CHANGING STATE
				if (array_c[cX][cY] == LIVE && n < 2) { // less than 2 neighbors
					array_cN[cX][cY] = DEAD;
				}
				else if (array_c[cX][cY] == LIVE && (n == 2 || n == 3)) { // 2 or 3 neighbors
						array_cN[cX][cY] = LIVE;
					}
					else
						if (array_c[cX][cY] == LIVE && n > 3) { // more than 3 neighbors
							array_cN[cX][cY] = DEAD;
						}
						else
							if (n == 3) { // 3 neighbors
								array_cN[cX][cY] = LIVE;
							}
			}
		}
	}
	// Moves calculated data onto the main grid to be printed
	void grid_update() { // rewrites the grid state
		system("CLS");
		for (int n = 0; n < y; n++)
		{
			for (int m = 0; m < x; m++)
			{
				cout << array_c[m][n] << DEAD;
				array_c[m][n] = array_cN[m][n];
			}
			cout << endl;
		}
	}
};

class ConwayInput {
public:
	// Initialise Build Mode
	void build_init()
	{
		building = true;
		simulating = false;

		for (int n = 0; n < y; n++) // Sets every cell to be EMPTY 
		{
			for (int m = 0; m < x; m++)
			{
				array_cB[m][n] = EMPTY;
			}
			cout << endl;
		}
		array_cB[0][0] = SELECT; // Set cursor defalut position for user input
		system("CLS");
	}
	// Generate Random Cells
	void build_random()
	{
		int seed; 
		system("CLS");
		cout << endl << "input seed: ";
		cin >> seed;

		for (int n = 0; n < y; n++) // for every cell, generate a new random number
		{
			for (int m = 0; m < x; m++)
			{
				srand(seed);
				int r = rand() % 11; // generates random numbers between 0 - 11
				// modulus operation to convert r into 2 states
				if (r % 2 == 0) { array_cB[m][n] = EMPTY; }
				if (r % 2 == 1) { array_cB[m][n] = LIVE; }
				seed = seed + rand(); // seed summed with the randomly generated number to create a new seed
			}
		}

	}
	// Grid Output and UI
	void build_gridout()
	{
		for (int n = 0; n < y; n++) // For loop prints out array
		{
			for (int m = 0; m < x; m++)
			{
				cout << array_cB[m][n] << DEAD; // the DEAD is a empty space for aesthetic purposes
			}
			cout << endl;
		}
		// User Interface, Keybinds
		cout << "Cursor Coordinates: " << m << ", " << n; // display the COORD of the cursor
		cout << endl;
		cout << endl << "SPACE to create a live cell \t\t\t\t DELETE to delete live cell";
		cout << endl;
		cout << endl << "Press INSERT to start the simulation \t \t \t Press PGUP to export a file";
		cout << endl << "Press HOME to generate a random grid \t \t \t Press PGDN to import a file";
		cout << endl;
		cout << endl << "Hold Esc to cancel the program";
	}
	// Cursor selection and deselection logic
	void build_selection()
	{
		// Cell selection
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			if (m < x - 1)
			{
				m++;
				// MOVING CURSOR TO NEW CELL, TAKING CONTEXT
				if (array_cB[m][n] == LIVE) { array_cB[m][n] = OVERLAP; }
				else if (array_cB[m][n] == EMPTY) { array_cB[m][n] = SELECT; }
				// UPDATING OLD SPOT FOR CURSOR
				if (array_cB[m - 1][n] == OVERLAP) { array_cB[m - 1][n] = LIVE; }
				else if (array_cB[m - 1][n] == SELECT) { array_cB[m - 1][n] = EMPTY; }

				system("CLS");
				build_gridout();
				Sleep(20); // delay prevents infinitely fast repetition
			}
		}
		if (GetKeyState(VK_LEFT) & 0x8000) {
			if (m > 0)
			{
				m--;
				// MOVING CURSOR TO NEW CELL, TAKING CONTEXT
				if (array_cB[m][n] == LIVE) { array_cB[m][n] = OVERLAP; }
				else if (array_cB[m][n] == EMPTY) { array_cB[m][n] = SELECT; }
				// UPDATING OLD SPOT FOR CURSOR
				if (array_cB[m + 1][n] == OVERLAP) { array_cB[m + 1][n] = LIVE; }
				else if (array_cB[m + 1][n] == SELECT) { array_cB[m + 1][n] = EMPTY; }
				system("CLS");
				build_gridout();
				Sleep(20);
			}
		}
		if (GetKeyState(VK_DOWN) & 0x8000) {
			if (n < y - 1)
			{
				n++;
				// MOVING CURSOR TO NEW CELL, TAKING CONTEXT
				if (array_cB[m][n] == LIVE) { array_cB[m][n] = OVERLAP; }
				else if (array_cB[m][n] == EMPTY) { array_cB[m][n] = SELECT; }
				// UPDATING OLD SPOT FOR CURSOR
				if (array_cB[m][n - 1] == OVERLAP) { array_cB[m][n - 1] = LIVE; }
				else if (array_cB[m][n - 1] == SELECT) { array_cB[m][n - 1] = EMPTY; }
				system("CLS");
				build_gridout();
				Sleep(20);
			}
		}
		if (GetKeyState(VK_UP) & 0x8000) {
			if (n > 0)
			{
				n--;
				// MOVING CURSOR TO NEW CELL, TAKING CONTEXT
				if (array_cB[m][n] == LIVE) { array_cB[m][n] = OVERLAP; }
				else if (array_cB[m][n] == EMPTY) { array_cB[m][n] = SELECT; }
				// UPDATING OLD SPOT FOR CURSOR
				if (array_cB[m][n + 1] == OVERLAP) { array_cB[m][n + 1] = LIVE; }
				else if (array_cB[m][n + 1] == SELECT) { array_cB[m][n + 1] = EMPTY; }
				system("CLS");
				build_gridout();
				Sleep(20);
			}
		}
		// Inputs
		if (GetKeyState(VK_SPACE) & 0x8000) {	// Sets selected cell to LIVE
			array_cB[m][n] = LIVE;
			Sleep(20);
		}
		if (GetKeyState(VK_DELETE) & 0x8000) {	// Sets selected cell to EMPTY / DEAD
			array_cB[m][n] = EMPTY;
			Sleep(20);
		}
	}
	// Moves build array data onto simulation array
	void build_finalise() {
		for (int n = 0; n < y; n++) // Takes data from array_cB and transfers it over to array_c for simulation
		{
			for (int m = 0; m < x; m++)
			{
				if (array_cB[m][n] == EMPTY) { array_c[m][n] = DEAD; }									// If cell is empty, make it dead
				if ((array_cB[m][n] == LIVE) || (array_cB[m][n] == OVERLAP)) { array_c[m][n] = LIVE; }	// if cell is live, make it live
			}
		}
	}
	// Keys which initialise or end program
	void build_confimkeys()
	{
		if (GetKeyState(VK_PRIOR) & 0x8000) {	// File Exporting
			file_output();
			system("CLS");
			build_gridout();
		}
		if (GetKeyState(VK_NEXT) & 0x8000) {	 // File importing
			file_input();
			system("CLS");
			build_gridout();
		}

		if (GetKeyState(VK_INSERT) & 0x8000) {	 // Begin the simulation
			build_finalise();
			building = 0;
			simulating = 1;
			system("CLS");
		}
		if (GetKeyState(VK_HOME) & 0x8000) {	// Allows user to imput a seed for random generation
			build_random();
			system("CLS");
			build_gridout();
		}
	}
};

int main() {
	// initialise classes
	ConwayGrid a;
	ConwayInput b;

	a.grid_in(); // input grid dimensions
	b.build_init(); // initialise build mode

	// build mode, user can select which cells live or die in the initial state
	b.build_gridout();
	while (building) {
		b.build_selection();
		b.build_confimkeys();
		end();
	}


	// simulation mode
	while (simulating)
	{
		a.grid_compute();
		a.grid_update();
		
		cout << "Hold 'esc' to end the program...";
		end(); // tests for ESC key to end the program
		Sleep(update);
		
	}
}