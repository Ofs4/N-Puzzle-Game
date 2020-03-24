/*<N-Puzzle Game>

    Copyright (C) <2020>  <Ofs4>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "npuzzle.h"
using namespace std;

void printMenu(){

	cout << endl << "V : Solves the problem" << endl;
	cout << "T : Prints how many moves have been done" << endl;
	cout << "E : Asks a txt file name and saves the board" << endl;
	cout << "O : Asks a file name and loads the board configuration" << endl;
	cout << "L : Moves left" << endl;
	cout << "R : Moves right" << endl;
	cout << "U : Moves up" << endl;
	cout << "D : Moves down" << endl;
	cout << "S : Shuffles the board" << endl; 
}

int main(int argc, char const *argv[]){
	srand(time(NULL));
	Npuzzle myPuzzle;
	bool check = false, exit = true;
	int problemSize;
	char input, puzzleSize;
	cout << "Welcome the N-Puzzle Game" << endl << endl;

	if (argc > 1)
		myPuzzle.readFromFile(argv);

	else
	{
		do{	
			cout << "Please enter the problem size: " << endl;
			cin >> puzzleSize;
			cin.ignore(256,'\n');
			problemSize = puzzleSize - 48;

			if (problemSize <= 9 && problemSize >= 3)
				check = true;

			else
				cerr << "Invalid input, try again!" << endl;

		}while(!check);
 		
 		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Your initial random board is: " << endl;
		myPuzzle.makePuzzleBoard(problemSize,problemSize);
		myPuzzle.print();
	}
	
	while(exit)
	{	
		printMenu();
		cout << endl << "Enter action: ";
		cin >> input;
		cin.ignore(256,'\n');
		myPuzzle.move(input,argv);
		exit = !myPuzzle.isSolved(0);
		if (exit == false)
		{
			cout << endl << "Problem Solved!" << endl;
			cout << "Total number of moves: " << myPuzzle.getNumberOfMoves() << endl;
		}

		cout << endl;
	}

	cout << "Exit..." << endl;

	return 0;
}