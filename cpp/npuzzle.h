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

#ifndef NPUZZLE_H
#define NPUZZLE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>	
using namespace std;

class Npuzzle
{
private:	
	
	class Board{

	private:
		vector<vector<int>> puzzle;
		int calledBefore;
		int counterOfMoves;
		char last_move;

	public:
		void readFromFile(const char**);
		void countLinesAndColumns(string, int*);
		void writeToFile(string);
		void reset();
		void setSize(const int&, const int&);
		void actionL(const int&, const int&);
		void actionR(const int&, const int&);
		void actionU(const int&, const int&);
		void actionD(const int&, const int&);
		void shuffle();
		void moveRandom();
		bool move(char);
		void printReport();
		bool isSolved();
		void copyPuzzletoVec(vector<vector<int>>&);
		void makeOrderedVec(vector<vector<int>>&);
		int numberOfBoards();
		char lastMove(){return last_move;}
		int numberOfMoves(){return counterOfMoves;}
		bool operator==(const Board &right)const;
		void makePuzzleBoard(const int&, const int&);
		int getNumberOfMoves(){return counterOfMoves;}
		vector<vector<int>> getPuzzle(){return puzzle;}
		Board():calledBefore{0},counterOfMoves{0},last_move{'S'}{}
	};

	vector<Board> myBoard;

public:
	void print();
	void readFromFile(const char**);
	void writeToFile();
	void reset();
	void setSize(const int&, const int&);
	void move(const char&, const char**);
	void shuffle();
	bool isSolved(const int& );
	void printReport();
	void solvePuzzle();
	bool checkRepeat(int index);
	void makePuzzleBoard(const int&, const int&);
	int getNumberOfMoves();
	friend ostream& operator <<(ostream &out,vector<Board> &myBoard){

		for (int i = 0; i < myBoard[0].getPuzzle().size(); ++i)
		{
			out << endl;

			for (int j = 0; j < myBoard[0].getPuzzle()[i].size() ; ++j)
			{
				if (myBoard[0].getPuzzle()[i][j] == myBoard[0].getPuzzle().size() * myBoard[0].getPuzzle()[i].size())
					out << "  \t";
				
				else if(myBoard[0].getPuzzle()[i][j] >= 0 && myBoard[0].getPuzzle()[i][j] < 10)
					out << '0' << myBoard[0].getPuzzle()[i][j] << '\t';

				else
					out << myBoard[0].getPuzzle()[i][j] << '\t';
			}		
		}
		out << endl;
		return out;
	}

	Npuzzle(){
		myBoard.resize(1);
	}
};

#endif
