#ifndef _USER_H_
#define _USER_H_

#include "player.h"
#include <iostream>

/*
���[�U�[��\���N���X�̒�`�i�h���N���X�j
*/
class User : public Player
{
public:
	int select(std::vector<int> &able_nums);              // ���I��
	User(const int boardSize) : Player(boardSize, "o") {} // �R���X�g���N�^(���[�U�[�p�̃}�[�N�́uo�v��player�N���X�֓n��)
};

#endif _USER_H_