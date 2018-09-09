#include<stdio.h>
#include<stdlib.h>

int is_suitable(int** board, int row, int col, int val) {
	for (int i=0; i<9; i++) {
		if(board[i][col] == val)
			return 0;
	}
	for (int j=0; j<9; j++) {
		if(board[row][j] == val)
			return 0;
	}
	for (int i=(row/3)*3; i<(row/3+1)*3; i++) {
		for (int j=(col/3)*3; j<(col/3+1)*3; j++) {
			if(board[i][j] == val)
				return 0;
		}
	}
	return 1;
}

int least_suitable_for_cell(int** board, int row, int col, int minval) {
	int i;
	for (i=minval+1; i<=9; i++) {
		if (is_suitable(board, row, col, i))
			break;
	}
	return i;
}

int prev_free (int** board, int** start, int tmp) {
	tmp--;
	while (tmp > -1 && start[tmp/9][tmp%9])
		tmp--; 
	return tmp;
}

int next_free (int** board, int** start, int tmp) {
	tmp++;
	while (tmp < 81 && start[tmp/9][tmp%9])
		tmp++; 
	return tmp; 
}

int sudoku_fill (int** board, int** start) {
	int row = 0;
	int col = 0;
	int tmp = 0;
	int flag = 1;
	while (start[tmp/9][tmp%9])
		tmp++;
	while (tmp < 81) {
		row = tmp/9;
		col = tmp%9;
		int val = board[row][col];
		int newval = least_suitable_for_cell(board, row, col, val);
		if (newval == 10) {
			board[row][col] = 0;
			tmp = prev_free (board, start, tmp);
			if (tmp == -1) {
				flag = 0;
				break;
			}
		} else {
			board[row][col] = newval;
			tmp = next_free (board, start, tmp);
		}
	}
	return flag;
}

void sudoku_read (int** board, int** start) {
	printf("Enter your sudoku, 0 for free cells:\n");
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			scanf("%d", &board[i][j]);
			if (board[i][j])
				start[i][j] = 1;
			else
				start[i][j] = 0;
		}
	}
}

void sudoku_print (int** board) {
	printf("\n");
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) 
			printf("%d ", board[i][j]);
		printf("\n");
	}
}
	

int main() {
	int **board = (int**)malloc(9*sizeof(int*));
	for (int i=0; i<9; i++)
         board[i] = (int*)malloc(9*sizeof(int));
	int **start = (int**)malloc(9*sizeof(int*));
	for (int i=0; i<9; i++)
         start[i] = (int*)malloc(9*sizeof(int));
	sudoku_read (board, start);
	if (!sudoku_fill(board, start)) {
		printf("The sudoku cannot be filled!\n");
		exit(1);
	}
	sudoku_print(board);
	return 0;
}
		  
