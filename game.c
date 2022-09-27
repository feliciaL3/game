//15 game
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// colors
#define ANSI_RESET_ALL          "\x1b[0m"
#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_WHITE        "\x1b[37m"

#define START 1
#define EXIT 2
#define RESUME 3
#define NONE -999
#define SELECT 1
#define UNABLE_MOVE 2
#define WON 3

// CONTROL 
#define ENTER ' '
#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68
//positions
/* 00  01  02  03 
   10  11  12  13
   20  21  22  23
   30  31  32  33   */

 int board[4][4] = {
	{1,   2,   3,   4},
	{5,   6,   7,   8},
	{9,  10,  11,  12},
	{13, 14,  15,  16} };

int inputKey = ' ', mode = 1;
int xi = 0; //coordinates of X
int xj = 0;  // coordinates of X
int nMoves = 0;
int inputMode = -999; 
 int choosenNumberI = 0; 
 int choosenNumberJ = 0; 
 int numI = 0; //coordinates of number that will be chosen
 int numJ = 0; //coordinates of number that will be chosen

int elementNotInList(int element, int* list, int n) {
	for (int i = 0; i < n; i++)  if (list[i] == element) 
	return 0;
	return 1;
}

int menu(void) {
	int menuOptionsLen = 3;
	int  menuOptions[] = {1, 2, 3};
	int c = -999;

	while(elementNotInList(c, menuOptions, menuOptionsLen)) {
		system("clear");
	

    printf("=> " ANSI_COLOR_YELLOW  "MENU!"  ANSI_RESET_ALL "\n");
	printf("1.START\n");
	printf("2.EXIT\n");
	printf("3.RESUME\n");;
    printf("=> " ANSI_COLOR_YELLOW  "\t\t\t Select an Option!"  ANSI_RESET_ALL "\n");	
		c = (int)(getc(stdin) - '0');
	}

return c;
}

void won() {
	int winMatrix[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	for (int i = 0; i < 4; i++)
		for (int j = 1; j < 4; j++)
			if (board[i][j] != winMatrix[i][j])
				return;

	mode = 3;
}

void shuffleBoard() {
	int flag;
	int row = rand() % 4, column = rand() % 4;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			flag = board[i][j];
			board[i][j] = board[row][column];
			board[row][column] = flag;
		}
}
// display a single board no
// 16  null. 
void displayNumber(int n, char* color, int padding) {	
	if (n == 16)
		printf("%s%*c%s", color, padding, 'X', "\x1B[0m");
	else
		printf("%s%*d%s", color, padding, n, "\x1B[0m");
}

void displayBoard() {
    printf("=> " ANSI_COLOR_RED     "LET'S PLAY!"     ANSI_RESET_ALL "\n");    
    printf("=> " ANSI_COLOR_RED     "SUCCES!"     ANSI_RESET_ALL "\n");    
	printf("\n\t\t\t\t");

	for (int i = 0; i < 6; i++) {
		if (i == 0 || i == 5)
			for (int j = 0; j < 5; j++)
					printf(ANSI_COLOR_GREEN  "⁑⁑⁑⁑"ANSI_RESET_ALL);					
		else
			for (int j = 0; j < 6; j++) {
				if (j == 0 || j == 5) 
					printf(ANSI_COLOR_GREEN "⁑⁑"ANSI_RESET_ALL);
				else {
					if (numI == i - 1 && numJ == j - 1)
						displayNumber(board[i - 1][j - 1], "\x1b[5m", 4);
					else
						displayNumber(board[i-1][j-1] , "\x1B[0m", 4);
				}
			}
		
		printf("\n\t\t\t\t");
	}

	printf("\n\n");
}

void displayProgress() {
    
		printf("No. of moves: %d\n", nMoves);
	printf("Now (%d, %d)\n", numI, numJ);
	printf("X tile (%d, %d)\n\n", xi, xj);
}

void displayInputHelp() {
	if (mode == -999)
		return;

	if (mode == 1){
        printf(ANSI_COLOR_CYAN"     ⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧\n" ANSI_RESET_ALL);
	
printf( ANSI_COLOR_BLUE   "           Select number to move operating with arrows\n" ANSI_RESET_ALL);
	        printf( ANSI_COLOR_CYAN"     ⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧\n"ANSI_RESET_ALL);

    }
		else if (mode == 2)
		printf("ERROR !  Unable to move this! \n");

//green
//
    printf("=> " ANSI_COLOR_RED     "CONTROLS!"     ANSI_RESET_ALL "\n");   
	printf(ANSI_COLOR_CYAN" r "   ANSI_RESET_ALL "- Reset game\n");
	printf(ANSI_COLOR_CYAN "Arrows "ANSI_RESET_ALL " - Pass through  tiles\n");
	printf(ANSI_COLOR_CYAN "Space  "ANSI_RESET_ALL " - Choose a tile to replace with the empty tile (X)\n");
	printf(ANSI_COLOR_CYAN "  u  "ANSI_RESET_ALL "   - Undo move\n");
	printf(ANSI_COLOR_CYAN "  s   "ANSI_RESET_ALL "  - Save and quit \n");
	printf(ANSI_COLOR_CYAN "  q  "ANSI_RESET_ALL "   - Quit \n\n");
    printf(ANSI_COLOR_RED  "  !!  -Press Enter after arrow or space\n\n"ANSI_RESET_ALL);
}

void getXCoords() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (board[i][j] == 16) {
				xi = i;
				xj = j;

				return;
			}
}

void move(int direction) {
	if (direction == 65 && numI > 0)
		numI--;
	else if (direction == 66 && numI < 3)
		numI++;
	else if (direction == 67 && numJ < 3)
		numJ++;
	else if (direction == 68 && numJ > 0)
		numJ--;
}
//checking if tile is near X
int canMoveTile() {
	if (abs(xi - numI) <= 1 && abs(xj - numJ) <= 1 && abs(xi - numI) + abs(xj - numJ) <= 1) {
		mode = 2;

		return 1;
	}

	return 0;
}

void swapTiles() {
	if (mode != 1)
		return;

	if (inputKey == ' ' && board[numI][numJ] != 16 && canMoveTile()) {
		board[xi][xj] = board[numI][numJ];
		board[numI][numJ] = 16;

		mode = 1;
		nMoves++;
	}
	else if (inputKey == 65 || inputKey == 66 || inputKey == 67 || inputKey == 68)
		move(inputKey);
}
//1 solvable
//0 nonsolvable
int isSolvable() {
	int arr[16];
	int k = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			arr[k] = board[i][j];
			k++;
		}

	int inversions = 0;

	for (int i = 0; i < 15; i++)
		if (arr[i] > arr[i + 1] && arr[i] != 16 && arr[i + 1] != 16)
			inversions++;

	if ((inversions % 2 == 0 && (4 - xi) % 2 != 0) || (inversions % 2 != 0 && (4 - xi) % 2 == 0))
		return 1;

	return 0;
}
//Initializes the game's board 
void initGame() {
	nMoves = 0;
	mode = 1;

	shuffleBoard();
	while (isSolvable() == 0)
		shuffleBoard();

	getXCoords();
	numI = 0;
	numJ = 0;
}

void resume() {
	FILE *f;
	char buff[3];

	f = fopen("./condition.txt", "r");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			fscanf(f, "%s", buff);	

			board[i][j] = atoi(buff);
		}

	fscanf(f, "\n%s", buff);
	nMoves = atoi(buff);

	fclose(f);

	mode = 1;
	numI = 0;
	numJ = 0;
	getXCoords();
}

void displayWinText() {
	printf(ANSI_COLOR_RED "\n\n\tVictory!\n"ANSI_RESET_ALL );
}
void exitGame() {
	printf(ANSI_COLOR_RED "\n\n\t Quiting \n"ANSI_RESET_ALL );

	exit(0);
}
//saves the current state of the board 
void save() {
	FILE *f;

	f = fopen("./condition.txt", "w");

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			fprintf(f, "%d ", board[i][j]);
//saves the current state of the game
	fprintf(f, "\n%d", nMoves);

	fclose(f);
}

void play(int shouldResume) {
	
	if (shouldResume == 1)
		resume();
	else
		initGame();
	
	 
	while(1) {
		system("clear");
		displayBoard();

		if (mode == 3) {
			displayWinText();
			exit(0);
		}


		displayProgress();
		displayInputHelp();

		mode = 1;
		getXCoords();

		inputKey = (int)getchar();

		if (inputKey == 'q')
			exitGame();
		else if (inputKey == 'r')
			initGame();
		else if (inputKey == 's') {
			save();
			exit(0);
		}

		if (mode == 1)
			swapTiles();

		won();
	}
}

int main(void) {
	switch(menu()) {
		case 1: play(0); break;
		case 2: return 0;
		case 3: play(1); break;
		default: break;
	}

	return 0;
}