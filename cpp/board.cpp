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

bool Npuzzle::Board::operator==(const Board &right)const {

	for (int i = 0; i < this->puzzle.size(); ++i)
	{
		for (int j = 0; j < this->puzzle[i].size(); ++j)
		{
			if (this->puzzle[i][j] != right.puzzle[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

void Npuzzle::Board::countLinesAndColumns(string fileName, int* sizeArr){

	ifstream input_file;
	int spaces = 0, lines = 0, columns = 0;
	char c;
	input_file.open(fileName);

	while(input_file.get(c))
	{
		if (c == ' ')
			spaces++;

		if (c == '\n')
			lines++;
	}
	++lines;
	columns = (spaces / lines) +1;
	sizeArr[0] = lines;
	sizeArr[1] = columns;
	input_file.close();
}

void Npuzzle::Board::readFromFile(const char** argFile){

	string gap = "bb", fileName;
	ifstream in_file;
	int i = 0 , j = 0, lines , columns , sizeArr[2];

	if (argFile[1] != NULL && !calledBefore) // It checks if a txt file given as command line options and if this functions called before.
	{
		countLinesAndColumns(argFile[1],sizeArr);
		fileName = argFile[1];
		lines = sizeArr[0];
		columns = sizeArr[1];	
		calledBefore = 1;	
	}

	else
	{	
		cout << "Enter a file name to load puzzle: ";
		cin >> fileName;
		countLinesAndColumns(fileName,sizeArr);
		lines = sizeArr[0];
		columns = sizeArr[1];
	}

	int space = lines * columns;
	puzzle.resize(lines);
	for (int i = 0; i < lines; ++i)
	{
		puzzle[i].resize(columns);
	}
	string c = to_string(space);
	string temp[columns];
	in_file.open(fileName);

	while(in_file.good())
	{	
		in_file >> temp[j];

		if (temp[j] == gap)
			temp[j] = c;

		puzzle[i][j] = stoi(temp[j]);
		j++;

		if (j == columns)
		{
			j = 0;
			i++;
		}
	}

	in_file.close();
}

void Npuzzle::Board::writeToFile(string fileName){

	ofstream out_file;
	out_file.open(fileName);
	int lines = puzzle.size(), columns = puzzle[0].size();

	for (int i = 0; i < lines; ++i)
	{	
		for (int j = 0; j < columns; ++j)
		{	
			if (puzzle[i][j] == lines*columns)
			{
				if (i == lines -1 && j == columns -1)
					out_file << "bb";

				else if (j == columns -1)
					out_file << "bb";					

				else	
					out_file << "bb ";
			}

			else if (puzzle[i][j] >= 0 && puzzle[i][j] < 10)
			{	
				if (i == lines -1 && j == columns -1)
					out_file << '0' << puzzle[i][j];

				else if (j == columns -1)
					out_file << '0' << puzzle[i][j];

				else
					out_file << '0' << puzzle[i][j] << ' ';
 			}	

			else
			{	
				if (i == lines -1 && j == columns -1)
					out_file << puzzle[i][j];

				else if (j == columns -1)
					out_file << puzzle[i][j];

				else
					out_file << puzzle[i][j] << ' ';
			}
		}

		if (i != lines -1)
			out_file << endl;
	}
	
	out_file.close();
}

void Npuzzle::Board::reset(){

	int temp, size = 0, k = 0;

	for (int i = 0; i < puzzle.size(); ++i) //Counts nonzero elements.
	{
		for (int j = 0; j < puzzle[i].size(); ++j)
		{
			if (puzzle[i][j] != 0)
				size++;
		}
	}
	int temp_arr[size];

	for (int i = 0; i < puzzle.size(); ++i) //Fills temp array with nonzero elements.
	{
		for (int j = 0; j < puzzle[i].size(); ++j)
		{		
			if (puzzle[i][j] > 0)
			{
				temp_arr[k] = puzzle[i][j];
				k++;
			}
		}
	}
	k = 0;

	for (int i = 0; i < size; ++i) // Sorts the array that does not have 0s by bubble sort.
	{
		for (int j = 0; j < size-i-1; ++j)
		{
			if(temp_arr[j] > temp_arr[j + 1])
			{
              	temp = temp_arr[j];
              	temp_arr[j] = temp_arr[j + 1];
              	temp_arr[j + 1] = temp;
            }  
		}	
	}

	for (int i = 0; i < puzzle.size(); ++i) // Makes ordered array with 0s.
	{
		for (int j = 0; j < puzzle[i].size(); ++j)
		{
			if (puzzle[i][j] > 0)
			{
				puzzle[i][j] = temp_arr[k];
				k++;
			}
		}
	}
}

void Npuzzle::Board::setSize(const int &line_val, const int &column_val){

	puzzle.resize(line_val);

	for (int i = 0; i < puzzle.size(); ++i)
	{
		puzzle[i].resize(column_val);
	}

	reset();
}

void Npuzzle::Board::makeOrderedVec(vector<vector<int>> &vect){

	int temp, size = 0, k = 0;

	for (int i = 0; i < vect.size(); ++i) //Counts nonzero elements.
	{
		for (int j = 0; j < vect[i].size(); ++j)
		{
			if (vect[i][j] != 0)
				size++;
		}
	}
	int temp_arr[size];

	for (int i = 0; i < vect.size(); ++i) //Fills temp array with nonzero elements.
	{
		for (int j = 0; j < vect[i].size(); ++j)
		{		
			if (vect[i][j] > 0)
			{
				temp_arr[k] = vect[i][j];
				k++;
			}
		}
	}
	k = 0;

	for (int i = 0; i < size; ++i) // Sorts the array that does not have 0s by bubble sort.
	{
		for (int j = 0; j < size-i-1; ++j)
		{
			if(temp_arr[j] > temp_arr[j + 1])
			{
              	temp = temp_arr[j];
              	temp_arr[j] = temp_arr[j + 1];
              	temp_arr[j + 1] = temp;
            }  
		}	
	}

	for (int i = 0; i < vect.size(); ++i) // Makes ordered array with 0s.
	{
		for (int j = 0; j < vect[i].size(); ++j)
		{
			if (vect[i][j] > 0)
			{
				vect[i][j] = temp_arr[k];
				k++;
			}
		}
	}
}

void Npuzzle::Board::copyPuzzletoVec(vector<vector<int>> &vect){

	for (int i = 0; i < puzzle.size(); ++i)
	{
		for (int j = 0; j < puzzle[i].size(); ++j)
		{
			vect[i][j] = puzzle[i][j];
		}
	}
}

bool Npuzzle::Board::isSolved(){

	vector<vector<int>> tempVec (puzzle.size(), vector<int> (puzzle[0].size()));
	copyPuzzletoVec(tempVec);
	makeOrderedVec(tempVec);

	for (int i = 0; i < puzzle.size(); ++i)
	{
		for (int j = 0; j < puzzle[i].size(); ++j)
		{
			if (puzzle[i][j] != tempVec[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

void Npuzzle::Board::actionL(const int &x, const int &y){

	int temp;
	temp = puzzle[x][y-1];
	puzzle[x][y-1] = puzzle[x][y];
	puzzle[x][y] = temp;
	last_move = 'L';
}

void Npuzzle::Board::actionR(const int &x, const int &y){

	int temp;
	temp = puzzle[x][y+1];
	puzzle[x][y+1] = puzzle[x][y];
	puzzle[x][y] = temp;
	last_move = 'R';	
}

void Npuzzle::Board::actionU(const int &x, const int &y){

	int temp;
	temp = puzzle[x-1][y];
	puzzle[x-1][y] = puzzle[x][y];
	puzzle[x][y] = temp;
	last_move = 'U';
}

void Npuzzle::Board::actionD(const int &x, const int &y){

	int temp;
	temp = puzzle[x+1][y];
	puzzle[x+1][y] = puzzle[x][y];
	puzzle[x][y] = temp;
	last_move = 'D';
}

void Npuzzle::Board::moveRandom(){

	int counter = 0, random, x, y, lines = puzzle.size(), columns = puzzle[0].size();

	for (int i = 0; i < lines; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			if (puzzle[i][j] == lines*columns)
			{
				x = i;
				y = j;
			}
		}
	}

	while(counter != 1){

		random = rand() % 4;

		if (random == 0 && y != 0 && puzzle[x][y-1] != 0)
		{
			actionL(x,y);
			counter++;
		}

		else if (random == 1 && y != columns-1 && puzzle[x][y+1] != 0)
		{
			actionR(x,y);
			counter++;
		}

		else if (random == 2 && x != 0 && puzzle[x-1][y] != 0)
		{
			actionU(x,y);
			counter++;
		}

		else if (random == 3 && x != lines-1 && puzzle[x+1][y] != 0)
		{
			actionD(x,y);
			counter++;
		}
	}
}

void Npuzzle::Board::shuffle(){

	for (int i = 0; i < puzzle.size()*puzzle[0].size(); ++i)
		moveRandom();

	counterOfMoves = 0;
	last_move = 'S';
}

void Npuzzle::Board::printReport(){

	cout << counterOfMoves << " moves have been done and solution has not been found yet!" << endl;
}

bool Npuzzle::Board::move(char userMove){

	int x,y,temp, lines = puzzle.size(), columns = puzzle[0].size();

	for (int i = 0; i < lines; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			if (puzzle[i][j] == lines*columns)
			{
				x = i;
				y = j;
			}
		}
	}

	switch(userMove){

		case 'L':
		case 'l':
			if (y != 0 && puzzle[x][y-1] != 0){
				actionL(x,y);
		    	counterOfMoves++;
		    	last_move = 'L';
		    	return true;
			}
			else
				return false;

			break;

		case 'R':	
		case 'r':
			if (y != columns-1 && puzzle[x][y+1] != 0){
				actionR(x,y);
				counterOfMoves++;
				last_move = 'R';
				return true;
			}	
			else
				return false;

			break;
		
		case 'U':	
		case 'u':
			if (x != 0 && puzzle[x-1][y] != 0){
				actionU(x,y);
				counterOfMoves++;
				last_move = 'U';
				return true;
			}
			else
				return false;

			break;

		case 'D':	
		case 'd':
			if (x != lines-1 && puzzle[x+1][y] != 0){
				actionD(x,y);
				counterOfMoves++;
				last_move = 'D';
				return true;
			}
			else
				return false;

			break;																			
	}
}

void Npuzzle::Board::makePuzzleBoard(const int&lines, const int &columns){

	int element = 0;
	puzzle.resize(lines);

	for (int i = 0; i < lines; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{	
			element++;
			puzzle[i].push_back(element);
		}
	}

	setSize(lines,columns);
	shuffle();
}