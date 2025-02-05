#include "board.h"

// コンストラクタ(盤面を初期化する）
Board::Board(int boardSize) : board(boardSize, std::vector<int>(boardSize, 0)), boardSize(boardSize) 
{
	int count = 1;
	for (int v = 0; v < boardSize; v++) {
		for (int h = 0; h < boardSize; h++) {
			board[v][h] = count;
			count++;
		}
	}
}

// 盤面の2次元ベクターのアドレスを渡す
std::vector<std::vector<int>>& Board::getBoard() {
	return board;
}

// 枠に記号を書き込む
void Board::setCell(Player* player) {
	std::string playerMark = player->getPlayerMark();
	int playerMarkNum = player->getPlayerMarkNum();

	int select_num = player->getSelectNum();
	int v = (select_num - 1) / boardSize;
	int h = (select_num - 1) % boardSize;

	if (board[v][h] > 0) {
		board[v][h] = playerMarkNum;
		return;
	}
}

// 盤面を表示する
void Board::show(std::map <std::string,int> marks) {
	if ((boardSize * boardSize) < 10) {
		// ボード内の数字の最大値が10に満たない場合の盤面表示関数
		showLowCells(marks);
	}
	else {
		// ボード内の数字の最大値が１０以上の場合の盤面表示関数
		showHighCells(marks);
	}
}

// ボード内の数字の最大値が10に満たない場合の盤面表示関数
void Board::showLowCells(std::map <std::string, int> marks) {
	for (int v = 0; v < boardSize; v++) {
		std::cout << "\n*";
		for (int i = 0; i < boardSize; i++) {
			std::cout << "-*";
		}
		std::cout << "\n";
		for (int h = 0; h < boardSize; h++) {
			if (board[v][h] > 0 && board[v][h] <= (boardSize * boardSize)) {
				std::cout << "|" << board[v][h];
			}
			else {
				for (std::pair<std::string, int> mark : marks) {
					if (mark.second == board[v][h]) {
						std::cout << "|" << mark.first;
					}
				}
			}
		}
		std::cout << "|\n";
	}
	std::cout << "*";
	for (int i = 0; i < boardSize; i++) {
		std::cout << "-*";
	}
	std::cout << "\n\n";
}

// ボード内の数字の最大値が１０以上の場合の盤面表示関数
void Board::showHighCells(std::map <std::string, int> marks) {
	for (int v = 0; v < boardSize; v++) {
		std::cout << "\n*";
		for (int i = 0; i < boardSize; i++) {
			std::cout << "--*";
		}
		std::cout << "\n";
		for (int h = 0; h < boardSize; h++) {
			if (board[v][h] < 10 && board[v][h] > 0) {
				std::cout << "| " << board[v][h];
			}
			else if (board[v][h] >= 10 && board[v][h] <= (boardSize * boardSize)) {
				std::cout << "|" << board[v][h];
			}
			else {
				// ボードの指定の枠にプレイヤーの記号の番号がセットされているか確認
				setPlayerMark(marks, board[v][h]);
			}
		}
		std::cout << "|\n";
	}
	std::cout << "*";
	for (int i = 0; i < boardSize; i++) {
		std::cout << "- *";
	}
	std::cout << "\n\n";
}

// ボードの指定の枠にプレイヤーの記号の番号がセットされているか確認（盤面表示関数の中で使用） 
void Board::setPlayerMark(std::map<std::string, int> marks, int boardNum) {
	for (std::pair<std::string, int> mark : marks) {
		if (mark.second == boardNum) {
			std::cout << "| " << mark.first;
		}
	}
}