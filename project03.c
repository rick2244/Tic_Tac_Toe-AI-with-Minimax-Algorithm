#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char board_t[3][3];
/*This is the function that I'm going to use to check the occurence of a draw in my res function. It
checks to make sure that all parts of the board are filled with either x or o. */
int isFull(board_t b){
	int r = 0;
	int c = 0;
	int cnt = 0;
	int truth  = 0;
	for(r = 0; r < 3; r++){
		for(c = 0; c < 3; c++){
			if(b[r][c] == 'X' || b[r][c] == 'O'){
				cnt++;
			}
		}
	}
	if(cnt == 9){
		truth = 1;
	}
	return truth;
}
/* This function is used to check the possible results of each game, a win for either x,o or a draw. */
int res(board_t b, char player){
	int win = 1;
	int nothing = -1;
	int tie = 0;
	int r = 0;
	int c = 0;
	for(r = 0; r < 3; r++){
		if(b[r][0] == player && b[r][0] == b[r][1] && b[r][0] == b[r][2]){
			return win;
		}
	}
	for(c = 0; c < 3; c++){
		if(b[0][c] == player && b[0][c] == b[1][c] && b[0][c] == b[2][c]){
			return win;
		}

	}
	if(b[0][0] == player && b[0][0] == b[1][1] && b[0][0] == b[2][2]){
		return win;
	}
	if(b[2][0] == player && b[2][0] == b[1][1] && b[2][0] == b[0][2]){
		return win;
	}
	if(isFull(b) == 1){
		return tie;
	}
	return nothing; 
}
/* This prints out the board and the values in each place everytime it is called.*/
void draw(board_t b){
	printf(" %c | %c | %c\n", b[0][0], b[0][1], b[0][2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n", b[1][0], b[1][1], b[1][2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n", b[2][0], b[2][1], b[2][2]);
}
//My own max function to return the max value between two values
int Max(int best, int score){
	if(score > best){
		return score;
	}
	return best;
}
//My own min function to return to min value between two values
int Min(int best, int score){
	if(score < best){
		return score;
	}
	return best;
}
/*My minimax function to recusively find the best move option for O in response to x*/
int minimax(board_t b ,char player,int depth){
	int score;
	int r;
	int c;
	int bestScore;
	if(res(b, 'X') == 1){
		return 10 - depth;
	}
	if(res(b, 'O') == 1){
		return -10 + depth;
	}
	if(res(b, 'X') == 0){
		return 0;
	}
	if(player == 'X'){
		bestScore = -1000000000;
		for(r = 0; r < 3; r++ ){
			for(c = 0; c < 3; c++){
				if(b[r][c] == '_'){
					b[r][c] = player;
					score = minimax(b, 'O' , depth + 1);
					bestScore = Max(bestScore, score);
					b[r][c] = '_';
				}
			}
		}
	}
	else{
		bestScore = 1000000000;
		for(r = 0; r < 3; r++ ){
			for(c = 0; c < 3; c++){
				if(b[r][c] == '_'){
					b[r][c] = player;
					score = minimax(b, 'X', depth + 1);
					bestScore = Min(bestScore, score);
					b[r][c] = '_';
				}
			}
		}
	}
	return bestScore;
}
/*This function is used to find the best move. I struggled with this for a while
unknownly because I didn't take into account the switch between an x player and o player and 
have if conditions to handle that properlu*/
void find_best_move(board_t b ,char player, int *pr, int *pc){
	int r;
	int c;
	char oplayer;
	int best;
	int score;
	if(player == 'X'){
		best = -1000000000;
		oplayer = 'O';
	}else if(player == 'O'){
		best = 1000000000;
		oplayer = 'X';
	}
	for(r = 0; r < 3; r++){
		for(c = 0; c < 3; c++){
			if(b[r][c] != 'X' && b[r][c] != 'O'){
				b[r][c] = player;
				score = minimax(b, oplayer , 0);
				b[r][c] = '_';
				if(player == 'X' && score > best ){
					best = score;
					*pr = r;
					*pc = c;
				}
				else if(player == 'O' && score < best){
					best = score;
					*pr = r;
					*pc = c;
				}			
			}
			
		}
	}
}
/*Main funciton is used to run to two seperate purposes of the program, either to ourput the best move
or to have a properly running interactive game in which the computer either wins or draws
with the user at all times*/

int main(int argc, char **argv){
	int r;
	int c;
	board_t b;
	if(argc == 1){
		for(int r = 0; r < 3; r++){
			for(int c = 0; c < 3; c++){
				b[r][c] = '_';
			}
		}
		for(int i = 0; i < 9; i++){
			printf("X: ");
			fscanf(stdin, "%d %d", &r, &c);
			if(b[r][c] != 'X' && b[r][c] != 'O'){
				b[r][c] = 'X';
				if(res(b, 'X') == 1){
					draw(b);
					printf("X wins\n");
					break;
				}
				if(res(b,'X') == 0){
					draw(b);
					printf("draw\n");
					break;
				}
				find_best_move(b, 'O', &r, &c);
				b[r][c] = 'O';
				printf("0: %d %d\n", r, c);
				if(res(b, 'O') == 1){
					draw(b);
					printf("O wins\n");
					break;
				}
				draw(b);
			}
			else{
				printf("illegal move\n");
			}
		}
	}else{
		int i = 1;
		for(int r = 0; r < 3; r++){
			for(int c = 0; c < 3; c++){
				b[r][c] = argv[i][0];
				i++;
			}
		}
		draw(b);
		find_best_move(b, 'O', &r, &c);
		printf("o: %d %d\n", r, c);
	}
}
