#ifndef _TIC_TAC_TOE_GAME_H_
#define _TIC_TAC_TOE_GAME_H_

#include <vector>
#include <map>
#include <string>
#include "judge.h"
#include "player.h"
#include "user.h"
#include "computer.h"
#include "board.h"

/*
�ܖڕ��׃v���O�����̃��C���֐����`
*/
class Tic_Tac_Toe_Game
{
private:
	int boardSize;                // �{�[�h�̍s���܂��͗�(boardSize = �s = ��)
	int requiredToWin;            // �����ɕ��ׂΏ����Ȃ̂���ݒ�
	std::vector<int> able_nums;   // �I���ł���{�[�h���̐������𔻒肷�邽�߂̔z��@�������l���u0�v�ŁA�I������Ă��鐔���Ɂuturncount�v������z��
	int turncount;                // ���[�U�[�܂��̓R���s���[�^�̂��ꂼ�ꂪ����w���������J�E���g����
public:
	Tic_Tac_Toe_Game(int size, int winConditions) : able_nums((size * size) + 1, 0),   // �R���X�g���N�^
		boardSize(size), requiredToWin(winConditions), turncount(0) {}
	void game();                                                                       // ���C���֐�
};

#endif _TIC_TAC_TOE_GAME_H_