#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <map>
#include <string>

/*
�v���C���[��\���N���X�̒�`�i��{�N���X�j
*/
class Player
{
protected:
	std::map<std::string, int> marks = { {"o", -1},  {"x", -2}};			  // �v���C���[�̋L���̔z��
	std::string mark;                                                         // �v���C���[�̋L��
	int markNum;                                                              // �v���C���[�̋L���ɑΉ�����ԍ�
	int selectNum;	                                                          // �I�񂾎�i�����j
	const int boardSize;                                                      // �{�[�h�̍s���܂��͗�(boardSize = �s = ��)

public:
	virtual int select(std::vector<int>& able_nums) = 0;                                      // ���I�ԁi�������z�֐��j
	std::string getPlayerMark() { return mark;  };                                            // �v���C���[�̋L����Ԃ�
	int getPlayerMarkNum() { return markNum; };												  // �v���C���[�̋L���ɑΉ�����ԍ���Ԃ�
	int getSelectNum() { return selectNum; };                                                 // ���Ԃ�
	std::map<std::string, int> getMarks() { return marks; };                                  // �v���C���[�̋L���̔z���Ԃ�
	Player(int boardSize, std::string mark)                                                   // �R���X�g���N�^
		: boardSize(boardSize), selectNum(0), markNum(this->marks.at(mark)), mark(mark) {}    
};

#endif _PLAYER_H_