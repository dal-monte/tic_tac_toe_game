#include "board.h"

// �R���X�g���N�^(�Ֆʂ�����������j
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

// �Ֆʂ�2�����x�N�^�[�̃A�h���X��n��
std::vector<std::vector<int>>& Board::getBoard() {
	return board;
}

// �g�ɋL������������
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

// �Ֆʂ�\������
void Board::show(std::map <std::string,int> marks) {
	if ((boardSize * boardSize) < 10) {
		// �{�[�h���̐����̍ő�l��10�ɖ����Ȃ��ꍇ�̔Ֆʕ\���֐�
		showLowCells(marks);
	}
	else {
		// �{�[�h���̐����̍ő�l���P�O�ȏ�̏ꍇ�̔Ֆʕ\���֐�
		showHighCells(marks);
	}
}

// �{�[�h���̐����̍ő�l��10�ɖ����Ȃ��ꍇ�̔Ֆʕ\���֐�
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

// �{�[�h���̐����̍ő�l���P�O�ȏ�̏ꍇ�̔Ֆʕ\���֐�
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
				// �{�[�h�̎w��̘g�Ƀv���C���[�̋L���̔ԍ����Z�b�g����Ă��邩�m�F
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

// �{�[�h�̎w��̘g�Ƀv���C���[�̋L���̔ԍ����Z�b�g����Ă��邩�m�F�i�Ֆʕ\���֐��̒��Ŏg�p�j 
void Board::setPlayerMark(std::map<std::string, int> marks, int boardNum) {
	for (std::pair<std::string, int> mark : marks) {
		if (mark.second == boardNum) {
			std::cout << "| " << mark.first;
		}
	}
}