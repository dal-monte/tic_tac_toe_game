#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

/*
盤面を表すクラスの定義
*/
class Board
{
private:
	const int boardSize;                                                // ボードの行数または列数(boardSize = 行 = 列)
	std::vector<std::vector<int>> board;                                // ボードを2次元ベクターで管理
	void showLowCells(std::map <std::string, int> marks);               // ボード内の数字の最大値が10に満たない場合の盤面表示関数
	void showHighCells(std::map <std::string, int> marks);              // ボード内の数字の最大値が１０以上の場合の盤面表示関数
	void setPlayerMark(std::map<std::string, int> marks, int boardNum); // ボードの指定の枠にプレイヤーの記号の番号がセットされているか確認（盤面表示関数の中で使用） 
public:
	std::vector<std::vector<int>> &getBoard();             // 盤面の2次元ベクターのアドレスを渡す
	void setCell(Player *player);                          // 枠に記号を書き込む
	void show(std::map <std::string,int> marks);           // 盤面を表示する
	Board(int boardSize);                            // コンストラクタ(盤面を初期化する）
};


#endif _BOARD_H_