#include "tic_tac_toe_game.h"

/*
C++の練習で作成した〇×ゲームです。
確定でコンピュータ(×マーク)が先行ですが、難易度は易しいです。
ボードのサイズ(3～9までの正の整数)と勝利条件を設定してください  ※どちらも数字以外はクラッシュします
*/
int main() {
	int boardSize     = 3;          // ボードの行数または列数(boardSize = 行 = 列) 2乗して「100」以上になる数だとエラー
	int requiredToWin = 3;          // 何個一列に並べば勝利なのかを設定

	Tic_Tac_Toe_Game game(boardSize, requiredToWin);

	game.game();
	return 0;
}