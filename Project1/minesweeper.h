#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cassert>

using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::setfill;
using std::string;
using std::ostream;

const int SIZE = 8;

void minesweeper( string input, string output );

void initBoard( char board[][SIZE], string file );
/******************************************************************************
 * This method will read the file that is loaded and store the locations of the
 * bombs as well as figure out the values for the numbers on the board.
 * 
 * board[][] - this is the 2d array that is the board.
 * file - the name of the file that contains the locations of the bombs
 * 
 * 이 방법은 적재된 파일을 읽고 폭탄의 위치를 저장하며 보드에 있는 숫자에 대한 값을 알아냅니다.
 * board[][] - 보드의 2d 배열입니다.
 * file - 폭탄의 위치를 포함하는 파일의 이름입니다.
 ******************************************************************************/ 

void displayBoard( ostream& out, char board[][SIZE], bool touchedBoard[][SIZE], bool gameOver = false );
/******************************************************************************
 * This function will read a board from the given file
 *
 * out - the ostream to display the board on. 
 * board[][] - the board that is to be displayed
 * touchedBoard[][] - this is a board of bools that indicates if the game board
 * has been touched at a given spot.
 * gameOver - use this to indicate whether to reveal the hidden bombs
 * 
 * 이 기능은 지정된 파일에서 보드를 읽습니다.
 * out - 보드를 표시할 ostream입니다.
 * board[][] - 표시할 보드입니다.
 * touchedBoard[] - 게임 보드가 지정된 위치에서 터치되었는지 여부를 나타내는 bools의 보드입니다.
 * gameOver - 숨겨진 폭탄을 공개할지 여부를 표시하기 위해 사용합니다.
 ******************************************************************************/ 

void initTouched( bool touchedBoard[][SIZE] );
/******************************************************************************
 * This function will initialize a board to have a false value for every element
 *
 * touchedBoard[][] - this is a board of bools that indicates if the game board
 * has been touched at a given spot.
 * 
 * 이 함수는 모든 요소에 대해 false 값을 가지도록 보드를 초기화합니다.
 *touchedBoard[] - 게임 보드가 지정된 위치에서 터치되었는지 여부를 나타내는 볼의 보드입니다.
 ******************************************************************************/ 

void touchBoard( bool board[][SIZE], int x, int y );
/******************************************************************************
 * This will go to the given board and indicate that it's been touched at the
 * given location.
 * The board that is given is not the board with the bombs and numbers but
 * rather a bool board that indicates if the spots been touched or not and 
 * it is needed for the displaying
 * board - this is the boolean touched board
 * x - this is the x coordinate in 1 based terms.  Must be checked for 
 * validity and decremented.  If invalid nothing is touched
 * y - this is the y coordinate in 1 based terms.  Must be checked for 
 * validity and decremented.  If invalid nothing is touched
 * 
 * 지정된 보드로 이동하여 지정된 위치에서 터치되었음을 나타냅니다.
 * 주어진 보드는 폭탄과 숫자가 있는 보드가 아니라 점들이 닿았는지 안 닿았는지 그리고 그것은 전시를 위해 필요합니다.
 * 보드 - boolean 터치 보드입니다.
 * x - 이것은 1을 기준으로 한 x 좌표입니다. 유효성을 검사하고 감산해야 합니다. 잘못된 경우 아무것도 건드리지 않습니다.
 * y - 이것은 1을 기준으로 한 y 좌표입니다. 유효성을 검사하고 감산해야 합니다. 잘못된 경우 아무것도 건드리지 않습니다.
 ******************************************************************************/ 
