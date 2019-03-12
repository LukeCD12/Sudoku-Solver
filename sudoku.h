#ifndef sudoku
#define sudoku
#define filename0 "boards/s01a.txt"
#define filename1 "boards/s01b.txt"
#define filename2 "boards/s01c.txt"
#define filename3 "boards/s05a.txt"
#define filename4 "boards/s05b.txt"
#define filename5 "boards/s06a.txt"
#define filename6 "boards/s06b.txt"
#define filename7 "boards/s06c.txt"
#define filename8 "boards/s12a.txt"
#define filename9 "boards/s16.txt"
#define userfile "boards/user.txt"

typedef struct BoardNode{
    char filename[20];
    int board[9][9];
    struct BoardNode *nextBoard;
}BoardNode;

void printBoard(BoardNode **board);
void getBoard(BoardNode **board);
BoardNode *printChoice(char choice[], BoardNode **board);
BoardNode *allocateNode(char choice[]);
void insertList(BoardNode **board, BoardNode *pNew);
void solveBoard(BoardNode **board);
int isSafe(BoardNode *board, int row, int col, int num);
int safeBox(BoardNode *board, int rowStart, int colStart, int num);
int safeRow(BoardNode *board, int row, int num);
int safeCol(BoardNode *board, int col, int num);
int isEmpty(BoardNode *board, int *col, int *row);

#endif