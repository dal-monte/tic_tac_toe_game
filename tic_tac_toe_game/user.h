#ifndef _USER_H_
#define _USER_H_

#include "player.h"
#include <iostream>

/*
ユーザーを表すクラスの定義（派生クラス）
*/
class User : public Player
{
public:
	int select(std::vector<int> &able_nums);              // 手を選ぶ
	User(const int boardSize) : Player(boardSize, "o") {} // コンストラクタ(ユーザー用のマークの「o」をplayerクラスへ渡す)
};

#endif _USER_H_