#ifndef _JUDGE_H_
#define _JUDGE_H_

#include <iostream>
#include <string>
#include "tic_tac_toe_game.h"
#include "player.h"

/*
勝敗を判定するクラスの定義
*/
class Judge
{
private:
	bool checkWinner(const std::vector<std::vector<int>>& board,int requiredToWin, int playerMarkNum);    // 勝敗判定（直近に指したプレイヤーが勝利条件を満たしているかを確認）
	bool checkDrow(const std::vector<std::vector<int>>& board);                                           // 引き分け判定
	const int boardSize;                                                                                  // ボードの行数または列数(boardSize = 行 = 列)
public:
	bool judge(const std::vector<std::vector<int>>& board, int requiredToWin, Player *player);            // 勝敗判定と引き分け判定を行う
	Judge(int boardSize) : boardSize(boardSize) {};                                                       // コンストラクタ
};

#endif _JUDGE_H_