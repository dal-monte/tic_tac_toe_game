#include "judge.h"

// ������������
bool Judge::checkDrow(const std::vector<std::vector<int>>& board) {
	// �������̃`�F�b�N
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] > 0) {
				// �z����ɐ����������ꂽ�}�X������΂܂��h���[�ł͂Ȃ��i���v���C���[�̎w�����ꏊ�������L�����}�C�i�X��int�^�ł��邱�Ƃ��O��)
				return false;
			}
		}
	}
	return true;
}

// ���s����i���߂Ɏw�����v���C���[�����������𖞂����Ă��邩���m�F�j
bool Judge::checkWinner(const std::vector<std::vector<int>>& board, int requiredToWin, int playerMarkNum) {
	// �������̃`�F�b�N
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

	// �c�����̃`�F�b�N
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

	// �΂ߕ����̃`�F�b�N�i�E�ォ�獶���j
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

	// �΂ߕ����̃`�F�b�N�i���ォ��E���j
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
		std::cout << "���������ł��B" << std::endl;
		return true;
	}
	else if(checkWinner(board, requiredToWin, playerMarkNum)) {
			std::cout << playerMark << "�̏����ł�" << std::endl;
		return true;
	}
	else {
		return false;
	}
}