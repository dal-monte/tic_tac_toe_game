#include "tic_tac_toe_game.h"

/*
C++�̗��K�ō쐬�����Z�~�Q�[���ł��B
�m��ŃR���s���[�^(�~�}�[�N)����s�ł����A��Փx�͈Ղ����ł��B
�{�[�h�̃T�C�Y(3�`9�܂ł̐��̐���)�Ə���������ݒ肵�Ă�������  ���ǂ���������ȊO�̓N���b�V�����܂�
*/
int main() {
	int boardSize     = 3;          // �{�[�h�̍s���܂��͗�(boardSize = �s = ��) 2�悵�āu100�v�ȏ�ɂȂ鐔���ƃG���[
	int requiredToWin = 3;          // �����ɕ��ׂΏ����Ȃ̂���ݒ�

	Tic_Tac_Toe_Game game(boardSize, requiredToWin);

	game.game();
	return 0;
}