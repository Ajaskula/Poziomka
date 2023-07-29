# Poziomka (Strawberry)
Introduction
Strawberry is a two-player combinatorial game played on a rectangular board divided into rows and columns.

The game is parameterized by three positive integers:

POLA: the number of fields occupied by a player in one move.
WIERSZE: the number of rows on the board.
KOLUMNY: the number of columns on the board.
For POLA equal to 2, the game is known as Domineering, and for POLA equal to 3, it is called Triomineering.

The players, referred to as Left and Right, sit at adjacent sides of the board, not facing each other. The constants WIERSZE and KOLUMNY determine the size of the board from Right's perspective. Columns are labeled with uppercase letters, starting from 'A', and rows are labeled with lowercase letters, starting from 'a'.

The players take turns making moves, starting with Left. Left can pass the right to make the first move to Right.

A player's move consists of placing a block on the board, occupying a connected set of free squares. The block has a width of POLA, a height of 1, and is horizontal from the perspective of the player who places it and vertical from the perspective of the opponent. When playing on paper, the players draw a horizontal line through a specific number of free squares.

A player who cannot make a move when it is their turn or chooses not to continue the game surrenders. The opponent of a player who surrenders wins, even if they themselves cannot make a move.

Board Evaluation
During the game, we may want to determine the current score to find the winner. We call this the board evaluation.

The board evaluation from the perspective of a player is the difference between the number of blocks they could currently place on the board and the number of blocks their opponent could currently place on the board.

For example, on a board with POLA equal to 3, WIERSZE equal to 7, and KOLUMNY equal to 11:

r
Copy code
  A B C D E F G H I J K|
a . . . # . . # . . . .|
b . . . # . . # . . . .|
c # # # # . # # # # # .|
d . . . . . # . . . . .|
e . . # . . # . . # # #|
f . . # . . . # # # . .|
g . . # . . . . . . . .|
-----------------------+
where the occupied squares are marked with the '#' symbol, and the empty squares are marked with the '.' symbol, the Left player, viewing the board from the left side, can place 6 blocks, and the Right player, viewing the board from the bottom, can place 9 blocks. The evaluation for the Right player is thus 9 - 6 = 3.

Command
Write a program that plays as the Right player in the Strawberry game with the parameters POLA, WIERSZE, and KOLUMNY.

The program starts with an optional right to make the first move, given by Left to Right. After that, the program reads the moves made by the Left player and responds to them as the Right player, writing its moves. Right surrenders when they cannot make any moves. The program ends when one of the players surrenders.

Among all possible moves, the program chooses the move that maximizes the board evaluation for the Right player. If there are multiple such moves, it chooses one of them according to the value of the constant WYBOR.

The values of POLA, WIERSZE, KOLUMNY, and WYBOR are defined using symbolic constants defined as the -D option of the compiler.

The code contains default values for these constants:

POLA has a value of 5,
WIERSZE has a value of 26,
KOLUMNY has a value of 26,
WYBOR has a value of 1000.
Input Data Format
The beginning of the input data can optionally contain a row with just the '-' character. It indicates that the first move right has been passed from Left to Right.

The subsequent lines of data represent the moves made by the Left player, one move per line. A move is represented by a capital letter followed by a lowercase letter, indicating the column and row, respectively, where the block should be placed.

A line containing only the '.' character signals that Left has surrendered.

Output Format
The program writes the moves made by the Right player, one move per line. When Right surrenders, the program writes a line containing only the '.' character.

A move by the Right player is represented by a lowercase letter followed by a capital letter, indicating the row and column, respectively, where the block is placed.

There are no spaces or any other characters in the output other than those mentioned above.

Examples
The following examples are the result of running the program compiled with the command:

gcc @options -DPOLA=4 -DWIERSZE=10 -DKOLUMNY=7 -DWYBOR=234 zadanie2.c -o zadanie2
Input data files with sample moves are provided as .in files, and the expected output for each example is provided as .out files.

For the input data in the file przyklad1.in, the correct output is in przyklad1.out.
For the input data in the file przyklad2.in, the correct output is in przyklad2.out.
For the input data in the file przyklad3.in, the correct output is in przyklad3.out.
