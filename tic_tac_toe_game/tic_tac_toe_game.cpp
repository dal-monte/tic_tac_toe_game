#include "tic_tac_toe_game.h"


void Tic_Tac_Toe_Game::game()
{
	if ((boardSize * boardSize) >= 100) {
		std::cout << "�{�[�h�T�C�Y�̒l���傫�����邽�ߕ\���ł��܂���B\n��悵�āu100�v�ȏ�ɂȂ�Ȃ��l�ɂ��Ă��������B\n";
		return;
	}
	else if (boardSize < 3) {
		std::cout << "�{�[�h�T�C�Y�̒l�����������邽�ߕ\���ł��܂���B\n�u3�v�ȏ�̒l�ɂ��Ă��������B\n";
		return;
	}

	if (requiredToWin > boardSize || requiredToWin < 3) {
		std::cout << "�����������s���ł��B\nrequiredToWin�̓{�[�h�T�C�Y�ȉ���3�ȏ�̐��̐����ɂ��Ă��������B";
		return;
	}
	
	Player *player[2];            // ��l�̃v���C���[�i��{�N���X�̔z��j
	User user(boardSize);         // ���[�U�[�i�L���́Z�j
	Computer computer(boardSize); // �R���s���[�^�[�i�L���́~�j
	player[0] = &computer;        // ���̃v���C���[�i�R���s���[�^�[�j
	player[1] = &user;            // ���̃v���C���[�i���[�U�[�j
	Board board(boardSize);       // �Ֆ�
	Judge judge(boardSize);       // ���s�̔���
	int turn = 0;                 // ���ԁi0��1�Ō��݂ɐ؂�ւ���j

	// �v���C���[�̋L���̔z���ϐ�marks�ɓ����
	std::map<std::string,int> marks = player[0]->getMarks();  

	// ����������������
	srand((unsigned)time(NULL));

	// ���s�����܂�܂ŌJ��Ԃ�
	while (true) {
		// ���݂̃^�[�������J�E���g����
		turncount++;

		// �Ֆʂ�\������
		board.show(marks);

		// �v���C���[�����I��
		int select_num = player[turn]->select(able_nums);
		able_nums[select_num] = turncount;
		board.setCell(player[turn]);  // �I�񂾐����i��j���{�[�h�ɉ�����
		
		std::vector<std::vector<int>> &now_board = board.getBoard();
		// ���s�𔻒肷��
		if (judge.judge(now_board, requiredToWin, player[turn])) {
			// ���s���m�肵����Q�[�����I������
			break;
		}

		// �v���C���[�����݂ɐ؂�ւ���
		if (turn == 0) {
			turn = 1;
		}
		else {
			turn = 0;
		}

	}
	// �Ֆʂ�\������
	board.show(marks);
}