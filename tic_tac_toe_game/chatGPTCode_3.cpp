#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

class GomokuNPC {
private:
    std::vector<std::vector<int>> board;  // 盤面
    int boardSize;  // 盤面のサイズ
    int currentDepth;  // 現在の深さ
    const int MAX_DEPTH = 6;  // 最大深さ（ゲーム進行に応じて動的に変更）
    const int WIN_SCORE = 1000000;
    const int MID_GAME_DEPTH = 4;
    const int EARLY_GAME_DEPTH = 3; // コンストラクタでcurrentDepthの値の初期化をしている数値

public:
    GomokuNPC(int size = 15)
        : boardSize(size), currentDepth(3) {
        board.resize(boardSize, std::vector<int>(boardSize, 0));  // 0で初期化
    }

    // 盤面の状態を表示
    void printBoard() {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << (board[i][j] == 0 ? '.' : (board[i][j] == 1 ? 'X' : 'O')) << " ";
            }
            std::cout << std::endl;
        }
    }

    // 手を置く
    void placeMove(int x, int y, int player) {
        board[x][y] = player;
    }

    // 評価関数（局所的な評価と連続数の加重スコア）
    int evaluatePosition(int x, int y, int player) {
        int score = 0;     // 最終的に判断するときに使用するスコアを初期化
        int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };  // 縦、横、左斜め、右斜めのそれぞれ方向に進むための座標の増分

        // ゲームの進行状況に応じて評価基準を変更
        if (currentDepth <= EARLY_GAME_DEPTH) {
            // 序盤では盤面中央や広がりを重視
            score += (boardSize / 2 - std::abs(x - boardSize / 2)) + (boardSize / 2 - std::abs(y - boardSize / 2));
        }

        // 縦、横、左斜め、右斜めのそれぞれに評価処理を行う
        for (int dir = 0; dir < 4; dir++) {
            int count = 1;  // 自分の駒の数
            bool openEnds = false;  // 両端が開いているか

            // 前方方向のスキャン
            for (int step = 1; step < 5; step++) {
                int nx = x + step * directions[dir][0];
                int ny = y + step * directions[dir][1];
                if (nx < 0 || ny < 0 || nx >= boardSize || ny >= boardSize) break;
                if (board[nx][ny] == player) {
                    count++;
                }
                else if (board[nx][ny] == 0) {
                    openEnds = true;
                    break;
                }
                else {
                    break;
                }
            }

            // 後方方向のスキャン
            for (int step = 1; step < 5; step++) {
                int nx = x - step * directions[dir][0];
                int ny = y - step * directions[dir][1];
                if (nx < 0 || ny < 0 || nx >= boardSize || ny >= boardSize) break;
                if (board[nx][ny] == player) {
                    count++;
                }
                else if (board[nx][ny] == 0) {
                    openEnds = true;
                    break;
                }
                else {
                    break;
                }
            }

            /*
            * 自分の駒が連続して並んでいる数に応じてスコアを加算。
            * 例えば、連続した駒が4つの場合、その両端に空いている場所があれば、
            * 次に駒を置くことでさらに連続を伸ばせる可能性が高いため、高得点を与える。
            */
            if (count == 4) {
                score += openEnds ? 1000 : 10000;
            }
            else if (count == 3) {
                score += openEnds ? 100 : 500;
            }
            else if (count == 2) {
                score += openEnds ? 10 : 50;
            }
        }

        return score;
    }

    // ミニマックス法とアルファベータ法
    int minimax(int depth, bool isMaximizingPlayer, int alpha, int beta) {
        if (depth == 0) {
            return 0;  // 評価関数を呼び出し
        }

        int bestScore = isMaximizingPlayer ? INT_MIN : INT_MAX;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == 0) {  // 空いている場所
                    board[i][j] = isMaximizingPlayer ? -1 : 1;  // NPCまたはプレイヤーの手
                    int score = minimax(depth - 1, !isMaximizingPlayer, alpha, beta);
                    board[i][j] = 0;  // 戻す

                    if (isMaximizingPlayer) {
                        bestScore = std::max(bestScore, score);
                        alpha = std::max(alpha, score);
                    }
                    else {
                        bestScore = std::min(bestScore, score);
                        beta = std::min(beta, score);
                    }

                    // α-β剪定
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return bestScore;
    }

    // 最適な手を選ぶ（ミニマックス法 + α-β剪定）
    std::pair<int, int> findBestMove() {
        int bestScore = INT_MIN;
        std::pair<int, int> bestMove = { -1, -1 };

        // ゲームの進行に応じて探索の深さを動的に調整
        if (currentDepth <= EARLY_GAME_DEPTH) {
            currentDepth = EARLY_GAME_DEPTH;  // 序盤は浅い深さ
        }
        else if (currentDepth <= MID_GAME_DEPTH) {
            currentDepth = MID_GAME_DEPTH;  // 中盤は中程度の深さ
        }
        else {
            currentDepth = MAX_DEPTH;  // 終盤は深く探索
        }

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == 0) {  // 空いている場所
                    placeMove(i, j, -1);  // NPCの手
                    int score = minimax(currentDepth, false, INT_MIN, INT_MAX);  // プレイヤー（1）との対決
                    placeMove(i, j, 0);  // 戻す

                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = { i, j };
                    }
                }
            }
        }
        return bestMove;
    }

    // 現在の手を動的に調整する
    void updateGameProgress(int turnCount) {
        if (turnCount <= 20) {
            currentDepth = EARLY_GAME_DEPTH;  // 序盤
        }
        else if (turnCount <= 40) {
            currentDepth = MID_GAME_DEPTH;  // 中盤
        }
        else {
            currentDepth = MAX_DEPTH;  // 終盤
        }
    }
};

int main() {
    GomokuNPC npc;

    // ゲームの流れ
    npc.printBoard();

    int turnCount = 0;

    // プレイヤー（1）とNPC（-1）の手を交互に置く
    npc.placeMove(7, 7, 1);  // プレイヤーの手
    turnCount++;
    npc.placeMove(7, 8, -1); // NPCの手
    turnCount++;
    npc.updateGameProgress(turnCount);  // ゲーム進行に応じて深さ調整

    // NPCが次に打つ最適な手を決める
    auto bestMove = npc.findBestMove();
    std::cout << "NPC's best move is at (" << bestMove.first << ", " << bestMove.second << ")\n";

    // 最適な手を盤面に反映
    npc.placeMove(bestMove.first, bestMove.second, -1);
    turnCount++;

    // 盤面を再表示
    npc.printBoard();

    return 0;
}
