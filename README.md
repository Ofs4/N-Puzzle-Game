# N-Puzzle-Game-and-Solver
GTU CSE 241 HW: N-Puzzle game with brute force solving algorithm in C++.

## Compiling and Running
You can use make command for compiling;
```
make
./nPuzzle
```
Or
```
g++ main.cpp npuzzle.cpp board.cpp -o nPuzzle
./nPuzzle
```
Also you can give a loadable file as argument.
```
./nPuzzle puzzle.txt
```

## Game Play

<p>If you did not enter a file name as argument game will ask for board size, it could be between 3 (for 3x3) and 9 (for 9x9) , after you enter the size, initial board is created.</p>

Inputs|Actions
-----|------
V|Solves the problem from the current configuration using the brute-force algorithm.
T|Prints a report about how many moves have been done and if the solution is found.
E|Asks a file name and saves the current board configuration as a loadable* shape file.
O|Asks a file name and loads the current board configuration from the shape file.
L|Moves the empty cell left if there is room.
R|Moves the empty cell right if there is room.
U|Moves the empty cell up if there is room.
D|Moves the empty cell down if there is room.
S|Makes size*size random moves to shuffle the board.

## Loadable file format(.txt)
<p>This shape contains the possible positions of the tiles with tile numbers and impossible positions
with ‘00’s. The blank tile is marked with ‘bb’. The following is a sample file. Note that your
board does not have to be square.There are 40 possible positions for the following
board, which means tiles are numbered from 01 to 39. The solution always places the empty
tile at the lower right corner.Note that max number could be 99, code does not support more than 2 digit.</p>

```
00 00 00 00 01 02 04 05 00
00 00 00 06 08 09 10 12 13
00 00 00 17 19 14 15 18 07
00 00 37 20 21 23 25 24 29
22 26 28 35 34 31 33 38 39
00 30 27 bb 32 36 03 11 16
```
