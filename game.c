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

#define SELECT 1
#define UNABLE_MOVE 2
#define WON 3
#define START 1
#define EXIT 2
#define RESUME 3
#define NONE -9999


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
	{13, 14,  15,  16} 
	};

int inputKey = ' ', mode = SELECT;
int xi = 0; //coordinates of X
int xj = 0;  // coordinates of X
int nMoves = 0;
int inputMode = -9999; 
 int selectedNumberI = 0; 
 int selectedNumberJ = 0; 
 int numI = 0; //coordinates of number that will be selected
 int numJ = 0; //coordinates of number that will be selected
 int moves,length;
char *moveHistory;
char *sep;

//it checks to see if an element is not present in a list
//for the parameters, element is what you're checking for, 
//int* list is the list itself, int n is the length of the list
int elemNotInList(int element, int* list, int n) {
	for (int i = 0; i < n; i++)  if (list[i] == element) 
	return 0;  
	return 1; //if you cant find that element in the list
}

int menu(void) {
	int menuOptLen = 3;
	int  menuOpt[] = {1, 2, 3};
	int k = -9999;

	while(elemNotInList(k, menuOpt, menuOptLen)) {
		system("clear");
	

    printf("=> " ANSI_COLOR_YELLOW  "MENU!"  ANSI_RESET_ALL "\n");
	printf("1.START\n");
	printf("2.LEAVE\n");
	printf("3.RESUME\n");;
    printf("=> " ANSI_COLOR_YELLOW  "\t\t\t Select an Option!"  ANSI_RESET_ALL "\n");	
		k = (int)(getc(stdin) - '0');
	}
return k;
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
//victory() checks whether board pattern matches the winning values victoryMatrix
void victory() {
	int victoryMatrix[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};


	for (int i = 0; i < 4; i++)
		for (int j = 1; j < 4; j++)
			if (board[i][j] != victoryMatrix[i][j])
				return;

	mode = WON; 
}


// display a single board no
// 16 = X
void displayNumbers(int n, char* color, int padding) {	
	if (n == 16)
		printf("%s%*c%s", color, padding, 'X', "\x1b[37m");
	else
		printf("%s%*d%s", color, padding, n, "\x1b[37m");
}

void displayActualSituation() {
    printf(ANSI_COLOR_CYAN"     ⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧\n" ANSI_RESET_ALL);
	printf(ANSI_COLOR_MAGENTA"                          Now Coordinates   (%d, %d)\n",numI, numJ, ANSI_RESET_ALL );
	printf(ANSI_COLOR_MAGENTA"                          X tile  Coordinates   (%d, %d)\n", xi, xj, ANSI_RESET_ALL);

}
void displayBoard() {
    printf("=> " ANSI_COLOR_RED     "GENERATING GAME.."     ANSI_RESET_ALL "\n");    
    printf("=> " ANSI_COLOR_RED     "LET'S PLAY!"     ANSI_RESET_ALL "\n");  
    printf("=> " ANSI_COLOR_RED     "OPERATE WITH ARROWS!"     ANSI_RESET_ALL "\n");   
    printf("=> " ANSI_COLOR_RED     "SUCCES!"     ANSI_RESET_ALL "\n");    
	printf("\n\t\t\t\t");

	for (int i = 0; i < 6; i++) {
		if (i == 0 || i == 5)
			for (int j = 0; j < 5; j++)
					printf(ANSI_COLOR_YELLOW "⁑⁑⁑⁑"ANSI_RESET_ALL);					
		else
			for (int j = 0; j < 6; j++) {
				if (j == 0 || j == 5) 
					printf(ANSI_COLOR_YELLOW "⁑⁑"ANSI_RESET_ALL);
				else {
					if (numI == i - 1 && numJ == j - 1)
						displayNumbers(board[i - 1][j - 1], "\x1b[5m", 4);
					else
						displayNumbers(board[i-1][j-1] , "\x1B[0m", 4);
				}
			}
		
		printf("\n\t\t\t\t");
	}

	printf("\n");
}



void displayHint() {
	if (mode == -9999)
		return;

	if (mode == 1){
        printf(ANSI_COLOR_CYAN"     ⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧\n" ANSI_RESET_ALL);
	
printf( ANSI_COLOR_RED   "             \t\t\t  CONTROLS\n" ANSI_RESET_ALL);
	        printf( ANSI_COLOR_CYAN"     ⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧\n"ANSI_RESET_ALL);

    }

		else if (mode == UNABLE_MOVE)
		printf("ERROR !  Unable to move this! \n");
    printf("> "ANSI_COLOR_CYAN "  u  "ANSI_RESET_ALL "   - Undo move\n");
	printf("> "ANSI_COLOR_CYAN "  s   "ANSI_RESET_ALL "  - Save and leave \n");
	printf("> "ANSI_COLOR_CYAN "  l  "ANSI_RESET_ALL "   - Leave \n");
	printf("> " ANSI_COLOR_CYAN"  r    "   ANSI_RESET_ALL " - Reset game\n");
	printf("> "ANSI_COLOR_CYAN "Arrows "ANSI_RESET_ALL " - Pass through  tiles\n");
	printf("> "ANSI_COLOR_CYAN "Space  "ANSI_RESET_ALL " - Choose a tile to replace with the empty tile (X)\n\n");
	    printf(ANSI_COLOR_CYAN"     ⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧\n" ANSI_RESET_ALL);

    printf("!! "ANSI_COLOR_RED  "             Press Enter after arrow or space\n\n"ANSI_RESET_ALL);
    printf(ANSI_COLOR_CYAN"     ⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧⤧\n" ANSI_RESET_ALL);

}

//it iterates over a 4x4 board trying to find which value of the board equals 16
//and returns those coordinates in tot he form of the global variable xi xj
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
	//up
	if (direction == 65 && numI > 0)
		numI--;
			//down
	else if (direction == 66 && numI < 3)
		numI++;
		//right
	else if (direction == 67 && numJ < 3)
		numJ++;
    //left		
	else if (direction == 68 && numJ > 0)
		numJ--;
	

	
}
//checking if tile is near X
int canMoveTile() {
	if (abs(xi - numI) <= 1 && abs(xj - numJ) <= 1 && abs(xi - numI) + abs(xj - numJ) <= 1) {
		mode = UNABLE_MOVE;
		return 1;
	}

	return 0;
}

void replaceTiles() {
	if (mode != 1)
		return;

	if (inputKey == ENTER && board[numI][numJ] != 16 && canMoveTile()) {
		board[xi][xj] = board[numI][numJ];
		board[numI][numJ] = 16;

		mode = SELECT;
		nMoves++;
	}
	else if (inputKey == UP || inputKey == 66 || inputKey == 67 || inputKey == 68)
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
	mode = SELECT;

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
//it will save the order and 2nd row will show no of moves
	f = fopen("./condition.txt", "r");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			fscanf(f, "%s", buff);	
			board[i][j] = atoi(buff);
		}
	fclose(f);

	mode = SELECT;
	numI = 0;
	numJ = 0;
	getXCoords();
}

void displayWinText() {
	printf(ANSI_COLOR_RED "\n\n\tVictory!\n"ANSI_RESET_ALL );
}
void exitGame() {
	printf(ANSI_COLOR_RED "\n\n\t Leaving \n"ANSI_RESET_ALL );
    exit(0);
}
//saves the current state of the board 
void save() {
	FILE *f;

	f = fopen("./condition.txt", "w");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			fprintf(f, "%d ", board[i][j]);
	fclose(f); }


void play(int shouldResume) {
	//setup
	if (shouldResume == 1)
		resume();
	else
		initGame();
	
	 
	while(1) {
		system("clear");
		displayBoard();
//mode 3=mode win 
		if (mode == WON) {
			displayWinText();
			exit(0);
		}

		displayActualSituation();
		displayHint();

		mode = SELECT;
		getXCoords();

		inputKey = (int)getchar();

		if (inputKey == 'l')
			exitGame();
		else if (inputKey == 'r')
			initGame();
		else if (inputKey == 's') {
			save();
			exit(0);
		}

		if (mode == SELECT)
			replaceTiles();
 //game turning WON in case of winning
		victory();
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
