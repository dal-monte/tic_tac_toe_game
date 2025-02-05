#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <map>
#include <string>

/*
プレイヤーを表すクラスの定義（基本クラス）
*/
class Player
{
protected:
	std::map<std::string, int> marks = { {"o", -1},  {"x", -2}};			  // プレイヤーの記号の配列
	std::string mark;                                                         // プレイヤーの記号
	int markNum;                                                              // プレイヤーの記号に対応する番号
	int selectNum;	                                                          // 選んだ手（数字）
	const int boardSize;                                                      // ボードの行数または列数(boardSize = 行 = 列)

public:
	virtual int select(std::vector<int>& able_nums) = 0;                                      // 手を選ぶ（純粋仮想関数）
	std::string getPlayerMark() { return mark;  };                                            // プレイヤーの記号を返す
	int getPlayerMarkNum() { return markNum; };												  // プレイヤーの記号に対応する番号を返す
	int getSelectNum() { return selectNum; };                                                 // 手を返す
	std::map<std::string, int> getMarks() { return marks; };                                  // プレイヤーの記号の配列を返す
	Player(int boardSize, std::string mark)                                                   // コンストラクタ
		: boardSize(boardSize), selectNum(0), markNum(this->marks.at(mark)), mark(mark) {}    
};

#endif _PLAYER_H_