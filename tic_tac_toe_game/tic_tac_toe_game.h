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
五目並べプログラムのメイン関数を定義
*/
class Tic_Tac_Toe_Game
{
private:
	int boardSize;                // ボードの行数または列数(boardSize = 行 = 列)
	int requiredToWin;            // 何個一列に並べば勝利なのかを設定
	std::vector<int> able_nums;   // 選択できるボード内の数字かを判定するための配列　※初期値が「0」で、選択されている数字に「turncount」を入れる配列
	int turncount;                // ユーザーまたはコンピュータのそれぞれが手を指した数をカウントする
public:
	Tic_Tac_Toe_Game(int size, int winConditions) : able_nums((size * size) + 1, 0),   // コンストラクタ
		boardSize(size), requiredToWin(winConditions), turncount(0) {}
	void game();                                                                       // メイン関数
};

#endif _TIC_TAC_TOE_GAME_H_