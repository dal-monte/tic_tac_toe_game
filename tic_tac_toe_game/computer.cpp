#include "computer.h"

// 手を選ぶ
int Computer::select(std::vector<int>& able_nums) {
	// able_numsから最後に指された手とターン数を求める（直近にユーザーが指した手）
	auto turnCountIter = std::max_element(able_nums.begin(), able_nums.end());
	int recentNum = std::distance(able_nums.begin(), turnCountIter);

    // 初回でない場合の処理（指す順番がコンピュータ先行で、初めの指し手以外の時）
    if (recentNum != 0) {
        int turnCount = *turnCountIter;

        // 仮想ボードで相手の指した手を再現する
        markBoard(exchangeSelectNum(recentNum), marks["o"]);

        // 最適な手を選ぶ（期待値計算）
        std::pair<int, int> selectMove = findBestMove();

        // 指す手を仮想ボードに加える
        markBoard(selectMove, marks["x"]);

        // ボード内の座標を数字に変換して返す
        selectNum = exchangeSelectMove(selectMove);

        return selectNum;
    }

	// 始めの指し手の時はランダムに手を決める
	int rand_num;
	while (1) {
		rand_num = rand() % (boardSize * boardSize) + 1;
        // ランダムで取得した数字の座標が空白であればそこに指し、そうでないときはもう一度ランダムに数字を取得
		if (able_nums[rand_num] == 0) {
            // 仮想ボードで自分の指した手を再現する
            markBoard(exchangeSelectNum(rand_num), marks["o"]);
			selectNum = rand_num;
			return rand_num;
		}
		else {
			continue;
		}
	}
}

// 指す手を仮想ボードに加える
void Computer::markBoard(std::pair<int, int> selectMove, int player) {
    virtualBoard[selectMove.first][selectMove.second] = player;
}

// 数字をボード内の座標に変換して返す
std::pair<int, int> Computer::exchangeSelectNum(int recentNum) {
    int v = (recentNum - 1) / boardSize;
    int h = (recentNum - 1) % boardSize;
    return std::pair<int, int> {v, h};
}

// ボード内の座標を数字に変換して返す
int Computer::exchangeSelectMove(std::pair<int, int> recentNum) {
    return (((recentNum.first) * boardSize) + ((recentNum.second + 1)));
}

// 仮想ボード配列の要素に対して、指定の方向のスコアを算出する
int Computer::evaluateDirections(int v, int h, int player, int dir) {
    int score = 0;
    int count = 1;
    int enemyCount = 0;
    bool openEnds = false;  // 両端が開いているかチェック
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };  // 縦、横、斜め

    // 前方方向のスキャン
    for (int step = 1; step < 5; step++) {
        int nv = v + step * directions[dir][0];
        int nh = h + step * directions[dir][1];
        // ボードの範囲外に出たらループ終了
        if (nv < 0 || nh < 0 || nv >= boardSize || nh >= boardSize) {
            // 壁際のスコアが高くなりすぎないように調整
            count -= 5 - step;
            break;
        }
        // 手の隣が空いているか判定（カウントが少ないときに重要な要素）
        if (step == 1 && virtualBoard[nv][nh] == 0) {
            openEnds = true;
        }
        // コンピュータの手が前方にあれば加点（起点から近いほど高得点）
        if (virtualBoard[nv][nh] == marks["x"]) {
            count += 5 - step;
        }
        // 相手の手が前方にあれば減点（起点から近いほど減点）
        if (virtualBoard[nv][nh] == marks["o"]) {
            count -= 5 - step;
            // 相手の連続している手があれば別でカウントする（起点から近いほど高得点）
            enemyCount += 5 - step;
        }
    }
    // 後方方向のスキャン
    for (int step = 1; step < 5; step++) {
        int nv = v - step * directions[dir][0];
        int nh = h - step * directions[dir][1];
        // ボードの範囲外に出たらループ終了
        if (nv < 0 || nh < 0 || nv >= boardSize || nh >= boardSize) {
            // 範囲外ギリギリは忌避する
            count -= 5 - step;
            break;
        }

        // 手の隣が空いているか判定（カウントが少ないときに重要な要素）
        if (step == 1 && virtualBoard[nv][nh] == 0) {
            openEnds = true;
        }

        // コンピュータの手が前方にあれば加点（起点から近いほど高得点）
        if (virtualBoard[nv][nh] == player) {
            count += 5 - step;
        }

        // 相手の手が前方にあれば減点（起点から近いほど減点）
        if (virtualBoard[nv][nh] == -1) {
            count -= 5 - step;
            // 相手の連続している手があれば別でカウントする（起点から近いほど高得点）
            enemyCount += 5 - step;
        }
    }

    // ループ結果をもとにその手を評価する
    if (count >= 8) {
        score = count;  // 勝利する確率が高いため最優先
    }
    else if (enemyCount >= 8) {
        score = enemyCount;  // 敵にとられると負ける可能性が高いため優先
    }
    else if (count >= 5 && openEnds) {
        score = count + 2;  // 隣が空いていて評価が高いため優先
    }
    else if (count <= 0) {
        score = 1;   // 評価がゼロ以下になると評価システムが機能しなくなるため初期値を入れる
    }
    else {
        score = count;
    }

    return score;
}

// 仮想ボード配列の要素に対して、4方向（縦・横・斜め）の内の最大スコアを導く
void Computer::evaluatePosition(int v, int h, int player) {
    int score[4];

    // ４方向それぞれの一つ隣の座標へ移動するときの座標数値増加分を指定　[0]縦、[1]横、[2]左斜め、[3]右斜め
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (int dir = 0; dir < 4; dir++) {
        score[dir] = evaluateDirections(v, h, player, dir);
    }

    // 縦・横・斜めのそれぞれの向きの判定結果のスコアから最も高い値を取得し仮想ボードに反映
    virtualBoard[v][h] = *std::max_element(std::begin(score), std::end(score));
}

// 最適な手を選ぶ
std::pair<int, int> Computer::findBestMove() {
    std::pair<int, int> bestMove = { -1, -1 };

    // 空いている場所に対して最適な手を評価
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (virtualBoard[i][j] >= 0) {  // 空いている場所
                evaluatePosition(i, j, marks["x"]);
            }
        }
    }

    // 最大値を探すための変数
    int max_value = virtualBoard[0][0];
    int max_row = 0, max_col = 0;

    // 2次元ベクターを順番に走査して最大値を探す
    for (int i = 0; i < virtualBoard.size(); ++i) {
        auto max_iter = std::max_element(virtualBoard[i].begin(), virtualBoard[i].end());
        if (*max_iter > max_value) {
            max_value = *max_iter;
            max_row = i;
            max_col = std::distance(virtualBoard[i].begin(), max_iter);
        }
    }

    bestMove = { max_row,max_col };

    return bestMove;
}