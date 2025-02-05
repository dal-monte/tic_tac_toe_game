#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"

/*
�R���s���[�^��\���N���X�̒�`�i�h���N���X�j
���z�̔Ֆʂ��쐬���āA���ꂼ��̗��ɏ����ւ̊��Ғl������
*/
class Computer : public Player
{
private:
    std::vector<std::vector<int>> virtualBoard;                            // ���z�Ֆ�
    std::pair<int, int> findBestMove();                                    // �œK�Ȏ��I�ԁi���Ғl�v�Z�j
    void markBoard(std::pair<int, int> selectMove, int player);            // ���z�{�[�h�ő���̎w��������Č�����
    std::pair<int, int> exchangeSelectNum(int recentNum);                  // �������{�[�h���̍��W�ɕϊ����ĕԂ�
    int exchangeSelectMove(std::pair<int, int> recentNum);                 // �{�[�h���̍��W�𐔎��ɕϊ����ĕԂ�
    void evaluatePosition(int v, int h, int player);                       // ���z�{�[�h�z��̗v�f�ɑ΂��āA4�����i�c�E���E�΂߁j�̓��̍ő�X�R�A�𓱂�
    int evaluateDirections(int v, int h, int player, int dir);             // ���z�{�[�h�z��̗v�f�ɑ΂��āA�w��̕����̃X�R�A���Z�o����

public:
	int select(std::vector<int>& able_nums);                                                    // ���I��
    Computer(const int boardSize)                                                               // �R���X�g���N�^(�R���s���[�^�p�̃}�[�N�́ux�v��player�N���X�֓n��)
        : Player(boardSize, "x"), virtualBoard(boardSize, std::vector<int>(boardSize, 0)) {};
};

#endif _COMPUTER_H_