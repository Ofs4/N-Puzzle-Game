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

void Npuzzle::print(){

	cout << myBoard;
}

bool Npuzzle::isSolved(const int &n){

	return myBoard[n].isSolved();
}

void Npuzzle::readFromFile(const char** argFile){

	myBoard[0].readFromFile(argFile);
	myBoard.resize(1);
	print();
}	

void Npuzzle::writeToFile(){

	string file_name;
	cout << "Enter a file name for saving the current board: ";
	cin >> file_name;
	myBoard[0].writeToFile(file_name);
	cout << "Puzzle saved to " << file_name << endl;
}

void Npuzzle::reset(){

	myBoard[0].reset();
}

void Npuzzle::setSize(const int &line_val, const int &column_val){

	myBoard[0].setSize(line_val,column_val);
}

void Npuzzle::shuffle(){

	reset();
	myBoard[0].shuffle();
	myBoard.resize(1);
}

void Npuzzle::printReport(){

	myBoard[0].printReport();
}

void Npuzzle::move(const char &userMove, const char **argFile){

	switch(userMove){

		case 'L':
			if (!myBoard[0].move('l'))
				cout << "You can't go left" << endl;
			else
				print();
			break;

		case 'l':
			if (!myBoard[0].move('l'))
				cout << "You can't go left" << endl;
			else
				print();
			break;

		case 'r':
			if (!myBoard[0].move('r'))
				cout << "You can't go right" << endl;
			else
				print();
			break;
			
		case 'R':
			if (!myBoard[0].move('r'))
				cout << "You can't go right" << endl;
			else
				print();
			break;
			
		case 'u':
			if(!myBoard[0].move('u'))
				cout << "You can't go up" << endl;
			else
				print();
			break;
			
		case 'U':
			if(!myBoard[0].move('u'))
				cout << "You can't go up" << endl;
			else
				print();
			break;
			
		case 'd':
			if(!myBoard[0].move('d'))
				cout << "You can't go down" << endl;
			else
				print();
			break;
			
		case 'D':
			if(!myBoard[0].move('d'))
				cout << "You can't go down" << endl;
			else
				print();
			break;

		case 's':
			shuffle();
			print();
			break;

		case 'S':
			shuffle();
			print();
			break;
			
		case 'o':
			readFromFile(argFile);
			break;

		case 'O':
			readFromFile(argFile);
			break;
			
		case 'e':
			writeToFile();
			print();
			break;

		case 'E':
			writeToFile();
			print();
			break;

		case 'v':
			solvePuzzle();
			break;

		case 'V':
			solvePuzzle();
			break;

		case 't':
			printReport();
			break;

		case 'T':		
			printReport();
			break;

		default:
			cout << "Invalid Input!" << endl;
			break;			    											
	}
}

bool Npuzzle::checkRepeat(int index){

	for (int i = 0; i < index; ++i)
	{
		if (myBoard[i] == myBoard[index])
		{
			return false;
		}
	}

	return true;
}

void Npuzzle::solvePuzzle(){

	int created = 0 ,index = 0 ,lastIndex = 0, i = 0, j;
	string moves;
	bool exit = true;

	cout << "Solving ..." << endl;

	while(exit && !isSolved(index))
	{
		for (i = lastIndex; i <= myBoard.size() ; ++i)
		{
			myBoard.push_back(myBoard[i]);
			++index;

			if(myBoard[index].move('l'))
			{	
				if (checkRepeat(index))
				{	
					if (isSolved(index))
					{
						exit = false;
						break;
					}
				}

				else
				{
					myBoard.pop_back();
					--index;
				}	
			}

			else
			{
				myBoard.pop_back();
				--index;
			}
			
			myBoard.push_back(myBoard[i]);
			++index;

			if(myBoard[index].move('r'))
			{	
				if (checkRepeat(index))
				{	
					if (isSolved(index))
					{
						exit = false;
						break;
					}
				}

				else
				{
					myBoard.pop_back();
					--index;
				}	
			}

			else
			{
				myBoard.pop_back();
				--index;
			}
			
			myBoard.push_back(myBoard[i]);
			++index;

			if(myBoard[index].move('u'))
			{	
				if (checkRepeat(index))
				{	
					if (isSolved(index))
					{
						exit = false;
						break;
					}
				}

				else
				{
					myBoard.pop_back();
					--index;
				}	
			}

			else
			{
				myBoard.pop_back();
				--index;
			}

			myBoard.push_back(myBoard[i]);
			++index;

			if(myBoard[index].move('d'))
			{	
				if (checkRepeat(index))
				{	
					if (isSolved(index))
					{
						exit = false;
						break;
					}
				}

				else
				{
					myBoard.pop_back();
					--index;
				}	
			}

			else
			{
				myBoard.pop_back();
				--index;
			}
		}

		created = index - created ;
		lastIndex = index - created + 1;
	}

	while(index != 0)
	{
		j = 0;
		moves.append(1,myBoard[index].lastMove());
		
		if (myBoard[index].lastMove() == 'L')
				myBoard[index].move('r');

		else if (myBoard[index].lastMove() == 'R')
				myBoard[index].move('l');

		else if (myBoard[index].lastMove() == 'U')
				myBoard[index].move('d');

		else
				myBoard[index].move('u');

		while(1)
		{	
			if (myBoard[index] == myBoard[j])
				break;
			
			j++;
		}

		index = j;					
	}

	for (int k = moves.size()-1; k >= 0 ; --k)
	{
		myBoard[0].move(moves[k]);
		usleep(2000000);
		print();
		cout << "Computer moved: " << moves[k] << endl;
	}
}

void Npuzzle::makePuzzleBoard(const int&lines, const int &columns){

	myBoard[0].makePuzzleBoard(lines,columns);
}

int Npuzzle::getNumberOfMoves(){

	return myBoard[0].getNumberOfMoves();
}