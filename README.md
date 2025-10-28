Tic-Tac-Toe AI with Minimax
Features

Play Tic-Tac-Toe against an AI using the Minimax algorithm.

Supports interactive gameplay (user = X, computer = O).

Can compute the best move for O from any board state.

Detects X wins, O wins, or a draw.

Includes helper functions for board checking, drawing, and Minimax evaluation.

Example Usage

Interactive game:

./tictactoe
X: 0 0
0: 1 1
X: 0 1
0: 2 2
...


Compute best move for O from a given board:

./tictactoe X O _ _ _ _ _ _ _
o: 1 1

Core Components

board_t – 3x3 board array.

isFull – checks if the board is full.

res – checks for a win, draw, or ongoing game.

draw – prints the board.

minimax – recursively evaluates best moves.

find_best_move – picks the optimal move for a player.

Sample Output

Interactive game:

 X | _ | _
---+---+---
 _ | O | _
---+---+---
 _ | _ | _
X: 0 1
0: 2 0


Best move computation:

Input board: X O _ _ _ _ _ _ _
Best move for O: 1 1

Lessons Learned

Implemented the Minimax algorithm for optimal gameplay.

Learned recursive reasoning to simulate all future moves.

Built a turn-based interactive game with move validation.

Ensured the AI always wins or draws.

How to Run

Compile:

gcc -o tictactoe tictactoe.c


Run interactive game:

./tictactoe


Compute best move for O:

./tictactoe X O _ _ _ _ _ _ _
