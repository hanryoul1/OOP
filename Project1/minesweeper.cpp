#include "minesweeper.h.cpp"

void minesweeper(string input, string output) {
	ofstream ofs;
	ofs.open(output);
	ifstream ifs;
	ifs.open(input);

	char board[SIZE][SIZE];
	bool touchedBoard[SIZE][SIZE];
	bool gameOver = false;


	string boardname;
	string load_command;
	ifs >> load_command;
	getline(ifs, boardname);

	if (load_command == "load") {
		boardname = boardname.substr(1);

		initBoard(board, boardname);
		initTouched(touchedBoard);
	}

	ofs << "Command: load " << boardname << endl;



	int x = 0, y = 0;
	string command;

	for (int command_count = 0; command_count < 54; command_count++) {
		if (!ifs) {
			break;
		}
		else {
			ifs >> command;
			ifs >> x;
			ifs >> y;
			if (command == "touch") {


				touchBoard(touchedBoard, x, y);
				ofs << "Command: touch " << x << " " << y << endl;
				if (board[x - 1][y - 1] == '*') {
					gameOver = true;
					break;
				}
			}
			else if (command == "display") {
				ofs << "Command: " << command << endl;

			}
		}

	}



	displayBoard(ofs, board, touchedBoard, gameOver);

	ifs.close();
	ofs.close();
}

void initBoard(char board[][SIZE], string file) {
	ifstream board_file;
	board_file.open(file);

	char borad_line;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board_file >> borad_line;
			board[i][j] = borad_line;
		}
	}
}

void displayBoard(ostream& out, char board[][SIZE], bool touchedBoard[][SIZE], bool gameOver) {

	int finalBoard[SIZE][SIZE];
	int touch_count = 0;
	int count = 0;

	for (int i = 0; i < SIZE; i++) {
		for (int a = 0; a < SIZE; a++) {
			finalBoard[i][a] = 0;
			if (touchedBoard[i][a] == true) {
				touch_count++;
			}
		}
	}

	if (gameOver == true) {
		if (touch_count > 0) {
			out << "Game Over\n~~~~~~~~~\nFinal Board" << endl;

			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (touchedBoard[i][j] == false && board[i][j] == '*') {
						out << "@";
					}
					else if (touchedBoard[i][j] == true && board[i][j] == '*') {
						out << '*';
					}
					else if (touchedBoard[i][j] == false && board[i][j] == '.') {
						out << '.';
					}
					else if (touchedBoard[i][j] == true && board[i][j] == '.') {
						for (int q = i - 1; q <= i + 1; q++) {
							for (int k = j - 1; k <= j + 1; k++) {
								if (q < 0 || q >= 8 || k < 0 || k >= 8) {
									continue;
								}
								if (board[q][k] == '*') {
									count++;
								}
							}
						}
						out << count;
						count = 0;
					}
				}
				out << endl;
			}
		}
	}

	else {
		if (touch_count == 0) {
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					out << '.';
				}
				out << endl;
			}
			out << endl << "Game Over\n~~~~~~~~~\nFinal Board" << endl;

			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (board[i][j] == '.') {
						out << '.';
					}
					else if (board[i][j] == '*') {
						out << '@';
					}
				}
				out << endl;
			}
		}
		else {
			out << "Game Over\n~~~~~~~~~\nFinal Board" << endl;

			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (touchedBoard[i][j] == false && board[i][j] == '*') {
						out << '@';
					}
					else if (touchedBoard[i][j] == true && board[i][j] == '*') {
						out << '*';
					}
					else if (touchedBoard[i][j] == false && board[i][j] == '.') {
						out << '.';
					}
					if (touchedBoard[i][j] == true && board[i][j] == '.') {
						int count = 0;
						for (int q = i - 1; q <= i + 1; q++) {
							for (int k = j - 1; k <= j + 1; k++) {
								if (q + 1 == 0 || q - 8 == 0 || k + 1 == 0 || k - 8 == 0) {
									continue;
								}
								if (board[q][k] == '*') {
									count++;
								}
							}
						}
						out << count;
						count = 0;
					}
				}
				out << endl;
			}
		}
	}
	out << endl;
	out << "Spaces touched: " << touch_count << endl;
}

void initTouched(bool touchedBoard[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			touchedBoard[i][j] = false;
		}
	}
}

void touchBoard(bool touchedBoard[][SIZE], int x, int y) {
	touchedBoard[x - 1][y - 1] = true;
}

int main() {
	minesweeper("test9commands.txt", "output.txt");

	return 0;
}
