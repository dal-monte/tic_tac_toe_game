#ifndef _JUDGE_H_
#define _JUDGE_H_

#include <iostream>
#include <string>
#include "tic_tac_toe_game.h"
#include "player.h"

/*
���s�𔻒肷��N���X�̒�`
*/
class Judge
{
private:
	bool checkWinner(const std::vector<std::vector<int>>& board,int requiredToWin, int playerMarkNum);    // ���s����i���߂Ɏw�����v���C���[�����������𖞂����Ă��邩���m�F�j
	bool checkDrow(const std::vector<std::vector<int>>& board);                                           // ������������
	const int boardSize;                                                                                  // �{�[�h�̍s���܂��͗�(boardSize = �s = ��)
public:
	bool judge(const std::vector<std::vector<int>>& board, int requiredToWin, Player *player);            // ���s����ƈ�������������s��
	Judge(int boardSize) : boardSize(boardSize) {};                                                       // �R���X�g���N�^
};

#endif _JUDGE_H_