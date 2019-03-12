#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sudoku.h"

FILE *boardFile;

int main(int argc, char *argv[]) {
    time_t start_t, end_t;
    double diff_t;
    BoardNode *board = NULL;
    int solved = 0;
    getBoard(&board);
    time(&start_t);
    if (solvedBoard(&board)) {
        time(&end_t);
        printf("Solved:\n");
        printBoard(&board);
        diff_t = difftime(end_t, start_t);
        printf("Took %.2lf seconds to solve", diff_t);
    }
    else
        printf("No solution");
    return 0;
}

void getBoard(BoardNode **board) {
    BoardNode *pNew = NULL;
    int i, hasBoard = 0, choice = -12, j;
    char ans[3];
    char *filenames[11] = {filename0,
                        filename1,
                        filename2,
                        filename3,
                        filename4,
                        filename5,
                        filename6,
                        filename7,
                        filename8,
                        filename9,
                        userfile
                        };
    while (!hasBoard) {
        printf("Use User Board? (yes/no): ");
        do {    
            scanf("%s", ans);
        } while (!(strstr(ans, "yes") || strstr(ans, "no")));
        if (strstr(ans, "yes")) {
            choice = 10;
        }
        else {
            printf("Choose a Board: (easiest to hardest):\n");
            for (i = 0; i < 10; i++) {
                if (i == 9) {
                    char name[4];
                    sscanf(filenames[i],"boards/%s.txt", name);
                    for (j = strlen(name); j > 0; j--) {
                        if (name[j] == '.') {
                            name[j] = '\0';
                        }
                    }
                    printf("%d - %s\n", i + 1, name);
                }
                else {
                    char name[4];
                    sscanf(filenames[i],"boards/%s.txt", name);
                    for (j = strlen(name); j > 0; j--) {
                        if (name[j] == '.') {
                            name[j] = '\0';
                        }
                    }
                    printf("%d  - %s\n", i + 1, name);
                }
            }
            printf("Choose a board (1 - 10): ");
            do { 
                scanf("%d", &choice);
                choice--;
            } while (choice < 0 || choice > 9);
        }
        printf("You have chosen board: %s\n", filenames[choice]);
        pNew = printChoice(filenames[choice], board);
        printf("Use this board? (yes/no): ");
        do {    
            scanf("%s", ans);
        } while (!(strstr(ans, "yes") || strstr(ans, "no")));
        if (strstr(ans,"yes")) {
            insertList(board, pNew);
            hasBoard = 1;
        }
    }
}

BoardNode *allocateNode(char choice[]) {
    BoardNode *pNew = (BoardNode *)malloc(sizeof(BoardNode));
    pNew -> nextBoard = NULL;
    char IB[100];
    int j, i;
    strcpy(pNew->filename, choice);
    while(fgets(IB, 100, boardFile) != NULL) {
        if (IB == NULL) {
            continue;
        }
        sscanf(IB, "%d %d %d %d %d %d %d %d %d", &pNew->board[j][0], &pNew->board[j][1], &pNew->board[j][2],
                                                    &pNew->board[j][3], &pNew->board[j][4], &pNew->board[j][5], 
                                                    &pNew->board[j][6] , &pNew->board[j][7], &pNew->board[j][8]);
        
        
        j++;
    }
    return pNew;
}

BoardNode *printChoice(char choice[], BoardNode **board) {
    boardFile = fopen(choice, "r");
    BoardNode *pNew = allocateNode(choice);
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", pNew->board[i][j]);
        }
        printf("\n");
    }
    fclose(boardFile);
    return pNew;
}

void insertList(BoardNode **board, BoardNode *pNew) {
    BoardNode *p = NULL;
    if (*board == NULL) {
        *board = pNew;
        return;
    }
    for (p = *board; p->nextBoard != NULL; p = p->nextBoard) {}
    p -> nextBoard = pNew;
}

void printBoard(BoardNode **board) {
    BoardNode *p = NULL;
    int i, j;
    for (p = *board; p != NULL; p = p->nextBoard) {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                printf("%d ", p->board[i][j]);
            }
            printf("\n");
        }
    }
}

int solvedBoard(BoardNode **board) {
    int row, col, num;
    BoardNode *p = *board;
    if (!isEmpty(*board, &row, &col)) {
        return 1;
    }
        for (num = 1; num <= 9; num++) {
            if (isSafe(p, row, col, num)) {
                p->board[row][col] = num;
                if (solvedBoard(&p)) {
                    return 1;
                }
                p->board[row][col] = 0;
            }
        }

    return 0;
}

int isSafe(BoardNode *board, int row, int col, int num) {
    return safeCol(board, col, num) && safeRow(board, row, num) && safeBox(board,row - row % 3 ,col - col % 3 ,num) && board->board[row][col] == 0;
}

int safeBox(BoardNode *board, int rowStart, int colStart, int num) {
    int row, col;
    for (row = 0; row < 3; row++) {
        for (col = 0; col <3; col++) {
            if (board->board[row+rowStart][col+colStart] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int safeRow(BoardNode *board, int row, int num) {
    int col;
    for (col = 0; col < 9; col++) {
        if (board->board[row][col] == num) {
            return 0;
        }
    }
    return 1;
}

int safeCol(BoardNode *board, int col, int num) {
    int row;
    for (row = 0; row < 9; row++) {
        if (board->board[row][col] == num) {
            return 0;
        }
    }
    return 1;
}

int isEmpty(BoardNode *board, int *row, int *col) {
    int r, c;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            if (board->board[r][c] == 0) {
                *row = r;
                *col = c;
                return 1;
            }
        }
    }
    return 0;
}