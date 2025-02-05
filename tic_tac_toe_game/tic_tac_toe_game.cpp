#include "tic_tac_toe_game.h"


void Tic_Tac_Toe_Game::game()
{
	if ((boardSize * boardSize) >= 100) {
		std::cout << "ボードサイズの値が大きすぎるため表示できません。\n二乗して「100」以上にならない値にしてください。\n";
		return;
	}
	else if (boardSize < 3) {
		std::cout << "ボードサイズの値が小さすぎるため表示できません。\n「3」以上の値にしてください。\n";
		return;
	}

	if (requiredToWin > boardSize || requiredToWin < 3) {
		std::cout << "勝利条件が不正です。\nrequiredToWinはボードサイズ以下で3以上の正の整数にしてください。";
		return;
	}
	
	Player *player[2];            // 二人のプレイヤー（基本クラスの配列）
	User user(boardSize);         // ユーザー（記号は〇）
	Computer computer(boardSize); // コンピューター（記号は×）
	player[0] = &computer;        // 先手のプレイヤー（コンピューター）
	player[1] = &user;            // 後手のプレイヤー（ユーザー）
	Board board(boardSize);       // 盤面
	Judge judge(boardSize);       // 勝敗の判定
	int turn = 0;                 // 順番（0と1で交互に切り替える）

	// プレイヤーの記号の配列を変数marksに入れる
	std::map<std::string,int> marks = player[0]->getMarks();  

	// 乱数を初期化する
	srand((unsigned)time(NULL));

	// 勝敗が決まるまで繰り返す
	while (true) {
		// 現在のターン数をカウントする
		turncount++;

		// 盤面を表示する
		board.show(marks);

		// プレイヤーが手を選ぶ
		int select_num = player[turn]->select(able_nums);
		able_nums[select_num] = turncount;
		board.setCell(player[turn]);  // 選んだ数字（手）をボードに加える
		
		std::vector<std::vector<int>> &now_board = board.getBoard();
		// 勝敗を判定する
		if (judge.judge(now_board, requiredToWin, player[turn])) {
			// 勝敗が確定したらゲームを終了する
			break;
		}

		// プレイヤーを交互に切り替える
		if (turn == 0) {
			turn = 1;
		}
		else {
			turn = 0;
		}

	}
	// 盤面を表示する
	board.show(marks);
}