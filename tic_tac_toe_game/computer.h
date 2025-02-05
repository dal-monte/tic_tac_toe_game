#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"

/*
コンピュータを表すクラスの定義（派生クラス）
仮想の盤面を作成して、それぞれの欄に勝利への期待値を入れる
*/
class Computer : public Player
{
private:
    std::vector<std::vector<int>> virtualBoard;                            // 仮想盤面
    std::pair<int, int> findBestMove();                                    // 最適な手を選ぶ（期待値計算）
    void markBoard(std::pair<int, int> selectMove, int player);            // 仮想ボードで相手の指した手を再現する
    std::pair<int, int> exchangeSelectNum(int recentNum);                  // 数字をボード内の座標に変換して返す
    int exchangeSelectMove(std::pair<int, int> recentNum);                 // ボード内の座標を数字に変換して返す
    void evaluatePosition(int v, int h, int player);                       // 仮想ボード配列の要素に対して、4方向（縦・横・斜め）の内の最大スコアを導く
    int evaluateDirections(int v, int h, int player, int dir);             // 仮想ボード配列の要素に対して、指定の方向のスコアを算出する

public:
	int select(std::vector<int>& able_nums);                                                    // 手を選ぶ
    Computer(const int boardSize)                                                               // コンストラクタ(コンピュータ用のマークの「x」をplayerクラスへ渡す)
        : Player(boardSize, "x"), virtualBoard(boardSize, std::vector<int>(boardSize, 0)) {};
};

#endif _COMPUTER_H_