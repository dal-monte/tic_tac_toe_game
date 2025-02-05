#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

/*
�Ֆʂ�\���N���X�̒�`
*/
class Board
{
private:
	const int boardSize;                                                // �{�[�h�̍s���܂��͗�(boardSize = �s = ��)
	std::vector<std::vector<int>> board;                                // �{�[�h��2�����x�N�^�[�ŊǗ�
	void showLowCells(std::map <std::string, int> marks);               // �{�[�h���̐����̍ő�l��10�ɖ����Ȃ��ꍇ�̔Ֆʕ\���֐�
	void showHighCells(std::map <std::string, int> marks);              // �{�[�h���̐����̍ő�l���P�O�ȏ�̏ꍇ�̔Ֆʕ\���֐�
	void setPlayerMark(std::map<std::string, int> marks, int boardNum); // �{�[�h�̎w��̘g�Ƀv���C���[�̋L���̔ԍ����Z�b�g����Ă��邩�m�F�i�Ֆʕ\���֐��̒��Ŏg�p�j 
public:
	std::vector<std::vector<int>> &getBoard();             // �Ֆʂ�2�����x�N�^�[�̃A�h���X��n��
	void setCell(Player *player);                          // �g�ɋL������������
	void show(std::map <std::string,int> marks);           // �Ֆʂ�\������
	Board(int boardSize);                            // �R���X�g���N�^(�Ֆʂ�����������j
};


#endif _BOARD_H_