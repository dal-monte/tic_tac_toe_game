#include "judge.h"

// 引き分け判定
bool Judge::checkDrow(const std::vector<std::vector<int>>& board) {
	// 横方向のチェック
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] > 0) {
				// 配列内に数字が書かれたマスがあればまだドローではない（※プレイヤーの指した場所を示す記号がマイナスのint型であることが前提)
				return false;
			}
		}
	}
	return true;
}

// 勝敗判定（直近に指したプレイヤーが勝利条件を満たしているかを確認）
bool Judge::checkWinner(const std::vector<std::vector<int>>& board, int requiredToWin, int playerMarkNum) {
	// 横方向のチェック
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j <= boardSize - requiredToWin; j++) {
			int count = 0;
			for (int k = 0; k < requiredToWin; k++) {
				if (board[i][j + k] == playerMarkNum) {
					count++;
				}
			}
			if (count == requiredToWin) return true;
		}
	}

	// 縦方向のチェック
	for (int i = 0; i <= boardSize - requiredToWin; i++) {
		for (int j = 0; j < boardSize; j++) {
			int count = 0;
			for (int k = 0; k < requiredToWin; k++) {
				if (board[i + k][j] == playerMarkNum) {
					count++;
				}
			}
			if (count == requiredToWin) return true;
		}
	}

	// 斜め方向のチェック（右上から左下）
	for (int i = 0; i <= boardSize - requiredToWin; i++) {
		for (int j = 0; j <=  boardSize - requiredToWin; j++) {
			int count = 0;
			for (int k = 0; k < requiredToWin; k++) {
				if (board[i + k][j + k] == playerMarkNum) {
					count++;
				}
			}
			if (count == requiredToWin) return true;
		}
	}

	// 斜め方向のチェック（左上から右下）
	for (int i = 0; i <= boardSize - requiredToWin; i++) {
		for (int j = requiredToWin - 1; j < boardSize; j++) {
			int count = 0;
			for (int k = 0; k < requiredToWin; k++) {
				if (board[i + k][j - k] == playerMarkNum) {
					count++;
				}
			}
			if (count == requiredToWin) return true;
		}
	}

	return false;
}

bool Judge::judge(const std::vector<std::vector<int>>& board, int requiredToWin, Player *player) {
	std::string playerMark = player->getPlayerMark();
	int playerMarkNum = player->getPlayerMarkNum();

	if (checkDrow(board)) {
		std::cout << "引き分けです。" << std::endl;
		return true;
	}
	else if(checkWinner(board, requiredToWin, playerMarkNum)) {
			std::cout << playerMark << "の勝利です" << std::endl;
		return true;
	}
	else {
		return false;
	}
}